#ifndef CAP_HANDLERINDEX_H
#define CAP_HANDLERINDEX_H

#include "../civet/CivetServer.h"

class HandlerIndex : public CivetHandler {
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn) override;
};

#endif //CAP_HANDLERINDEX_H
