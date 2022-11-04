/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
#include "uWebSockets/App.h"
#include "libusockets.h"

/* This is a simple WebSocket echo server example.
 * You may compile it with "WITH_OPENSSL=1 make" or with "make" */

int main()
{
  /* ws->getUserData returns one of these */
  struct PerSocketData
  {
    /* Fill with user data */
  };

  /* Keep in mind that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support.
   * You may swap to using uWS:App() if you don't need SSL */
  uWS::App().ws<PerSocketData>("/*", {/* Settings */
                                .compression = uWS::CompressOptions(uWS::DEDICATED_COMPRESSOR_4KB | uWS::DEDICATED_DECOMPRESSOR),
                                .maxPayloadLength = 100 * 1024 * 1024,
                                .idleTimeout = 16,
                                .maxBackpressure = 100 * 1024 * 1024,
                                .closeOnBackpressureLimit = false,
                                .resetIdleTimeoutOnSend = false,
                                .sendPingsAutomatically = true,
                                /* Handlers */
                                .upgrade = nullptr,
                                .open = [](auto * /*ws*/)
                                {
                                  /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
                                  std::cout << "opened" << '\n'; },
                                .message = [](auto *ws, std::string_view message, uWS::OpCode opCode)
                                { ws->send(message, opCode, true); },
                                .drain = [](auto * /*ws*/)
                                {
            /* Check ws->getBufferedAmount() here */ },
                                .ping = [](auto * /*ws*/, std::string_view)
                                {
            /* Not implemented yet */ },
                                .pong = [](auto * /*ws*/, std::string_view)
                                {
            /* Not implemented yet */ },
                                .close = [](auto * /*ws*/, int /*code*/, std::string_view /*message*/)
                                {
            /* You may access ws->getUserData() here */ }})
      .listen(3000, [](auto *listen_socket)
              {
        if (listen_socket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        } })
      .run();
}
