#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include <iostream>
#include <sstream>
#include <future>
#include <chrono>
#include <any>

#include "path/waypoint.h"
#include "path/path.h"
#include "path/pathbuilder.h"
#include "purepursuit/abstractdrivetrain.h"
#include "purepursuit/simulateddrivetrain.h"
#include "purepursuit/purepursuit.h"

using server_t = websocketpp::server<websocketpp::config::asio>;

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

// pull out the type of messages sent by our config
using message_ptr = server_t::message_ptr;

server_t server;

std::thread simulationThread;

// if true, the client wants the simulation to stop. the thread
// will reset back to true and send a message when it registers the stop.
std::atomic_bool shouldStop = false;

// if true, a thread is currently active simulating the robot path.
std::atomic_bool simulating = false;

bool pathCreated = false;
Path currPath({}, true);

void handleUpdatePath(std::stringstream &ss, server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
{
  // cannot update the path while simulating on a generated path!
  if (simulating)
    return;

  bool forward;
  double maxVel, maxAccel, k;
  ss >> forward >> maxVel >> maxAccel >> k;

  int N;
  ss >> N;

  PathBuilder builder(forward, maxVel, maxAccel, k);

  double x, y;
  for (int i = 0; i < N; ++i)
  {
    ss >> x >> y;
    builder.addPoint({x, y});
  }

  pathCreated = true;
  currPath = builder.build();

  std::stringstream output;
  output << "updated-path " << currPath.path.size() << '\n';

  for (const Waypoint &pt : currPath.path)
    output << pt << '\n';

  s->send(hdl, output.str(), msg->get_opcode());
}

void handleSimulateRobot(std::stringstream &ss, server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
{
  // cannot simulate again while simulating
  if (!pathCreated || simulating)
    return;

  // join the thread so it doesn't go out of scope before "finishing"
  if (simulationThread.joinable())
    simulationThread.join();

  simulationThread = std::thread([&](server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
                                 {
    using namespace std::this_thread;
    using namespace std::chrono;

    simulating = true;

    SimulatedDriveTrain driveTrain({0, 0, -0.8204330463490498});
    PurePursuit pursuit(driveTrain, 20);

    for (int i = 0;; ++i)
    {
      if (shouldStop)
        break;
      
      const auto data = pursuit.tick(currPath);
      if (data.ended)
        break;

      s->send(hdl, 
          "simulation-part " + std::to_string(i) + "\n" + 
          driveTrain.getState().toString() + "\n" +
          data.toString() + "\n", 
      msg->get_opcode());

      driveTrain.tick(0.005);

      std::cout << "ticked " << i << '\n';
      sleep_for(milliseconds(10));
    } 
    
    s->send(hdl, "simulation-end", msg->get_opcode());

    simulating = false;
    shouldStop = false;

    std::cout << "thread ended!\n"; },
                                 s, hdl, msg);
}

// Define a callback to handle incoming messages
void on_message(server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
{
  std::cout << "on_message called with hdl: " << hdl.lock().get()
            << " and message: " << msg->get_payload()
            << std::endl;

  std::stringstream ss(msg->get_payload());

  std::string messageType;
  ss >> messageType;

  if (messageType == "stop-listening")
  {
    s->stop_listening();
    return;
  }

  try
  {
    if (messageType == "update-path")
      handleUpdatePath(ss, s, hdl, msg);
    else if (messageType == "start-simulation")
      handleSimulateRobot(ss, s, hdl, msg);
    else if (messageType == "cancel-simulation")
    {
      shouldStop = true; // thread will automatically gracefully exit
      std::cout << "thread has been requested to cancel\n";
    }
    else
      std::cerr << "ERROR: Did not recognize message type \"" << messageType << "\". Full message: \"" << msg->get_payload() << "\".";
  }
  catch (websocketpp::exception const &e)
  {
    std::cout << "Request failed because: "
              << "(" << e.what() << ")" << std::endl;
  }
}

void cleanExit()
{
  server.stop_listening();
}

int main()
{
  std::atexit(cleanExit);

  try
  {
    server.set_reuse_addr(true);

    // Set logging settings
    server.set_access_channels(websocketpp::log::alevel::all);
    server.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    server.init_asio();

    // Register our message handler
    server.set_message_handler(bind(&on_message, &server, ::_1, ::_2));

    // Listen on port 9002
    server.listen(9002);

    std::cout << "starting server!\n";

    // Start the server accept loop
    server.start_accept();

    // Start the ASIO io_service run loop
    server.run();
  }
  catch (websocketpp::exception const &e)
  {
    std::cout << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "other exception" << std::endl;
  }
}