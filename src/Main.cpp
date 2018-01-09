#include "Defs.h"

#include <iostream>

#include "civet/CivetServer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <cstring>
#endif

#include "handlers/HandlerIndex.h"
#include "handlers/HandlerWebSocket.h"

bool exitNow = false;

class ExitHandler : public CivetHandler {
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn) override {
        mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: " "text/plain\r\nConnection: close\r\n\r\n");
        mg_printf(conn, "Bye!\n");
        exitNow = true;
        return true;
    }
};

int main() {
    const char *options[] = {"listening_ports", PORT, nullptr};

    std::vector<std::string> cpp_options;
    for (int i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
        cpp_options.emplace_back(options[i]);
    }

    CivetServer server(cpp_options);

    HandlerIndex handlerIndex;
    server.addHandler(URL_INDEX, handlerIndex);

    HandlerWebSocket handlerWebSocket;
    server.addWebSocketHandler(URL_WEB_SOCKET, handlerWebSocket);

    printf("Running at http://localhost:%s\n", PORT);

    ExitHandler h_exit;
    server.addHandler(URL_EXIT, h_exit);

    while (!exitNow) {
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    return 0;
}