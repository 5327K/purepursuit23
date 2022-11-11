// #include "websocketpp/config/asio_no_tls.hpp"
// #include "websocketpp/server.hpp"

// #include <iostream>
// #include <sstream>

// using server_t = websocketpp::server<websocketpp::config::asio>;

// using websocketpp::lib::bind;
// using websocketpp::lib::placeholders::_1;
// using websocketpp::lib::placeholders::_2;

// // pull out the type of messages sent by our config
// using message_ptr = server_t::message_ptr;

// server_t server;

// void handleUpdatePath(std::stringstream &ss, server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
// {
//   s->send(hdl, "updated-path", msg->get_opcode());
//   std::cout << msg->get_payload() << '\n';
// }

// void handleSimulateRobot(std::stringstream &ss, server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
// {
//   s->send(hdl, "simulate-robot", msg->get_opcode());
// }

// // Define a callback to handle incoming messages
// void on_message(server_t *s, websocketpp::connection_hdl hdl, message_ptr msg)
// {
//   std::cout << "on_message called with hdl: " << hdl.lock().get()
//             << " and message: " << msg->get_payload()
//             << std::endl;

//   std::stringstream ss(msg->get_payload());

//   std::string messageType;
//   ss >> messageType;

//   if (messageType == "stop-listening")
//   {
//     s->stop_listening();
//     return;
//   }

//   try
//   {
//     if (messageType == "update-path")
//       handleUpdatePath(ss, s, hdl, msg);
//     else if (messageType == "simulate-robot")
//       handleSimulateRobot(ss, s, hdl, msg);
//     else
//       std::cerr << "ERROR: Did not recognize message type \"" << messageType << "\". Full message: \"" << msg->get_payload() << "\".";
//   }
//   catch (websocketpp::exception const &e)
//   {
//     std::cout << "Request failed because: "
//               << "(" << e.what() << ")" << std::endl;
//   }
// }

// void cleanExit()
// {
//   server.stop_listening();
// }

// int main()
// {
//   std::atexit(cleanExit);

//   try
//   {
//     server.set_reuse_addr(true);

//     // Set logging settings
//     server.set_access_channels(websocketpp::log::alevel::all);
//     server.clear_access_channels(websocketpp::log::alevel::frame_payload);

//     // Initialize Asio
//     server.init_asio();

//     // Register our message handler
//     server.set_message_handler(bind(&on_message, &server, ::_1, ::_2));

//     // Listen on port 9002
//     server.listen(9002);

//     // Start the server accept loop
//     server.start_accept();

//     // Start the ASIO io_service run loop
//     server.run();
//   }
//   catch (websocketpp::exception const &e)
//   {
//     std::cout << e.what() << std::endl;
//   }
//   catch (...)
//   {
//     std::cout << "other exception" << std::endl;
//   }
// }