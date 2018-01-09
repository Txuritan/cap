#include "HandlerWebSocket.h"

#include <cstring>

bool HandlerWebSocket::handleConnection(CivetServer *server, const struct mg_connection *conn) {
    printf("WS connected\n");
    return true;
}

void HandlerWebSocket::handleReadyState(CivetServer *server, struct mg_connection *conn) {
    printf("WS ready\n");

    const char *text = "Hello from the websocket ready handler";
    mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, text, strlen(text));
}

bool HandlerWebSocket::handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len) {
    printf("WS got %lu bytes: ", (long unsigned) data_len);
    fwrite(data, 1, data_len, stdout);
    printf("\n");

    mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, data, data_len);
    return (data_len < 4);
}

void HandlerWebSocket::handleClose(CivetServer *server, const struct mg_connection *conn) {
    printf("WS closed\n");
}