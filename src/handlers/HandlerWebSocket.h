#ifndef CAP_HANDLERWEBSOCKET_H
#define CAP_HANDLERWEBSOCKET_H

#include "../civet/CivetServer.h"

class HandlerWebSocket : public CivetWebSocketHandler {
public:
    bool handleConnection(CivetServer *server, const struct mg_connection *conn) override;
    void handleReadyState(CivetServer *server, struct mg_connection *conn) override;
    bool handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len) override;
    void handleClose(CivetServer *server, const struct mg_connection *conn) override;
};


#endif //CAP_HANDLERWEBSOCKET_H
