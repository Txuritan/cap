#ifndef CAP_FOUNDATION_HPP
#define CAP_FOUNDATION_HPP

#include "html/HTML.hpp"

h topbar() {
    return h("nav", nAV {
            {"class",       "top-bar"},
            {"data-topbar", ""},
            {"role",        "navigation"},
    }, hV {
            h("ul", nA{"class", "title-area"}, hV {
                    h("li", nA{"class", "name"}, hV {
                            h("h1", hV {
                                    h("a", nA{"href", "/"}, "CAP")
                            }),
                    }),
                    h("li", nA{"class", "toggle-topbar menu-icon"}, hV {
                            h("a", nA{"href", "#"}, hV {
                                    h("span", " ")
                            }),
                    }),
            }),
            h("section", nA{"class", "top-bar-section"}, hV {
                    h("ul", nA{"class", "right"}, hV {
                            h("li", nA{"class", "name"}, hV {
                                    h("a", nA{"href", "/games"}, "Leave Game")
                            }),
                    }),
                    h("ul", nA{"class", "left"}, hV {
                            h("li", nA{"class", "name"}, hV {
                                    h("a", nA{"href", "/logout"}, "Logout")
                            }),
                    }),
            }),
    });
}



#endif //CAP_FOUNDATION_HPP
