#include "HandlerIndex.h"

#include "../Defs.h"

#include "../html/HTML.hpp"
#include "../Partials.hpp"

bool HandlerIndex::handleGet(CivetServer *server, struct mg_connection *conn) {

    hb body(hD::html5, hV {
            h("title", "CAP (C++ Against People)"),
            h("link", nAV {
                    {"href", "https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.3/css/foundation.min.css"},
                    {"rel", "stylesheet"},
            }),
            h("script", nA{"src", "https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.3/js/vendor/modernizr.js"}),
    }, hV {
            topbar(),
            h("script", nA{"src", "https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.3/js/vendor/jquery.js"}),
            h("script", nA{"src", "https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.3/js/foundation.min.js"}),
            h("script", "$(document).foundation();"),
    });

    body.setHtml(body.getHtml().setAttributes(nAV {
            {"class", "no-js"},
            {"lang", "en"},
    }));

    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: " "text/html\r\nConnection: close\r\n\r\n");
    mg_printf(conn, body.toString().c_str());
    return true;
}