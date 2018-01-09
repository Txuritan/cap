/*
 * MIT License
 *
 * Copyright (c) 2018 Ian Cronkright
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HTML_HPP
#define HTML_HPP

#include <string>
#include <vector>
#include <fstream>

#define HH_VERSION_MAJOR 0
#define HH_VERSION_MINOR 1
#define HH_VERSION_PATCH 0

#define HH_VERSION "0.1.0"

#ifndef HH_INDENT
#define HH_INDENT 4
#endif

#ifndef HH_STARTING_INDENT
#define HH_STARTING_INDENT 2
#endif

#ifdef HH_NAMESPACE
namespace h {
#endif

enum class hDoctype {
    html5,
};

enum class hType {
    document,
    element,
};

enum class hOut {
    oneline,
    multiline,
};

struct nAttribute {
    std::string key;
    std::string value;
};

class h {
private:
    hType nType;

    std::string nName;
    std::string nContent;

    bool nClose = true;

    std::vector<h> nChildren;
    std::vector<nAttribute> nAttributes;

public:
    h() = default;

    explicit h(const std::string &name) {
        this->setType(hType::element);
        this->setName(name);
    }

    h(const std::string &name, const nAttribute &attribute) {
        this->setType(hType::element);
        this->setName(name);
        this->setAttributes(std::vector<nAttribute> {attribute});
    }

    h(const std::string &name, const nAttribute &attribute, const std::string &content) {
        this->setType(hType::element);
        this->setName(name);
        this->setAttributes(std::vector<nAttribute> {attribute});
        this->setContent(content);
    }

    h(const std::string &name, const nAttribute &attribute, const std::vector<h> &children) {
        this->setType(hType::element);
        this->setName(name);
        this->setAttributes(std::vector<nAttribute> {attribute});
        this->setChildren(children);
    }

    h(const std::string &name, const std::vector<nAttribute> &attributes, const std::vector<h> &children) {
        this->setType(hType::element);
        this->setName(name);
        this->setAttributes(attributes);
        this->setChildren(children);
    }

    h(const std::string &name, const std::vector<nAttribute> &attributes) {
        this->setType(hType::element);
        this->setName(name);
        this->setAttributes(attributes);
    }

    h(const std::string &name, const hType &type) {
        this->setType(type);
        this->setName(name);
    }

    h(const std::string &name, const hType &type, const std::vector<h> &children) {
        this->setType(type);
        this->setName(name);
        this->setChildren(children);
    }

    h(const std::string &name, const std::string &content) {
        this->setType(hType::element);
        this->setName(name);
        this->setContent(content);
    }

    h(const std::string &name, const std::vector<h> &children) {
        this->setType(hType::element);
        this->setName(name);
        this->setChildren(children);
    }

    std::vector<nAttribute> getAttributes() {
        return this->nAttributes;
    }

    h &setAttributes(const std::vector<nAttribute> &attributes) {
        this->nAttributes = attributes;
        return *this;
    }

    h &appendAttributes(const std::vector<nAttribute> &attributes) {
        if (this->nChildren.empty()) {
            this->setAttributes(attributes);
        } else {
            this->nAttributes.insert(this->nAttributes.end(), attributes.begin(), attributes.end());
        }
        return *this;
    }

    std::vector<h> getChildren() {
        return this->nChildren;
    }

    h &setChildren(const std::vector<h> &children) {
        this->nChildren = children;
        return *this;
    }

    h &appendChildren(const std::vector<h> &children) {
        if (this->nChildren.empty()) {
            this->setChildren(children);
        } else {
            this->nChildren.insert(this->nChildren.end(), children.begin(), children.end());
        }
        return *this;
    }

    std::string getContent() {
        if (this->nContent.empty()) {
            return "";
        } else {
            return this->nContent;
        }
    }

    h &setContent(const std::string &content) {
        this->nContent = content;
        return *this;
    }

    std::string getName() {
        return this->nName;
    }

    h &setName(const std::string &name) {
        this->nName = name;
        return *this;
    }

    hType getType() {
        return this->nType;
    }

    h &setType(const hType &type) {
        this->nType = type;
        return *this;
    }

    std::string toString(const hOut &out = hOut::multiline, const int &indentation = 1) {
        std::string element;

        std::string indent;
        std::string indentContent;

        bool multiline = (out == hOut::multiline);

        if (multiline) {
            for (int i = 0; i < indentation; i++) {
                indent = std::string((HH_INDENT * indentation), ' ');
            }

            indentContent = std::string((HH_INDENT * (indentation + 1)), ' ');
        }

        if (this->nType == hType::document) {
            element = "<!DOCTYPE " + this->nName + ">" + ((multiline) ? "\n" : "");

            for (h &child : this->nChildren) {
                element += child.toString(out, indentation - HH_STARTING_INDENT);
            }

            element += (multiline ? "\n" : "");
        } else if (this->nType == hType::element) {
            element = ((multiline) ? indent : "") + "<" + nName + "";

            for (const nAttribute &attribute : this->nAttributes) {
                element += " " + attribute.key + "=\"" + attribute.value + "\"";
            }

            if (this->nContent.empty() && this->nClose && this->nChildren.empty()) {
                if (this->nName == "head" || this->nName == "body" || this->nName == "script") {
                    element += "></" + this->nName + ">" + (multiline ? "\n" : "");
                } else {
                    element += "/>";
                    element += (multiline ? "\n" : "");
                }
            } else {
                element += ">";
                element += (multiline ? "\n" : "");

                if (!this->nContent.empty()) {
                    element += ((multiline) ? indentContent : "") + this->nContent + (multiline ? "\n" : "");
                }

                for (h &child : this->nChildren) {
                    element += child.toString(out, indentation + 1);
                }

                element += ((multiline) ? indent : "") + "</" + this->nName + ">" + (multiline ? "\n" : "");
            }
        }

        return element;
    }

    bool toFile(const std::string &path, const hOut &out = hOut::multiline) {
        std::ofstream file(path.c_str());

        if (file.is_open()) {
            file << this->toString(out);
            file.close();
            return true;
        }

        return false;
    }
};

class hb {
private:
    h hHtml = h("html");

    h hHead = h("head");
    h hBody = h("body");

    hDoctype doctype;

    std::vector<nAttribute> headAttributes;
    std::vector<nAttribute> bodyAttributes;

    std::vector<h> headChildren;
    std::vector<h> bodyChildren;

    h constructDoctype() {
        switch (this->doctype) {
            case hDoctype::html5:
                return h("html", hType::document);
        }
    }

    h construct() {
        h document = this->constructDoctype().setChildren(std::vector<h> {
                this->hHtml.setChildren(std::vector<h> {
                        this->hHead.setChildren(this->headChildren),
                        this->hBody.setChildren(this->bodyChildren),
                })
        });

        return document;
    }

public:
    hb() = default;

    explicit hb(const hDoctype &doctype) {
        this->setDoctype(doctype);
    }

    hb(const std::vector<h> &head, const std::vector<h> &body) {
        this->setHeadChildren(head);
        this->setBodyChildren(body);
    }

    hb(const hDoctype &doctype, const std::vector<h> &head, const std::vector<h> &body) {
        this->setDoctype(doctype);
        this->setHeadChildren(head);
        this->setBodyChildren(body);
    }

    h getHtml() {
        return this->hHtml;
    }

    hb &setHtml(const h &html) {
        this->hHtml = html;
        return *this;
    }


    h getHead() {
        return this->hHead;
    }

    hb &setHead(const h &head) {
        this->hHead = head;
        return *this;
    }

    hb &setHeadAttributes(const std::vector<nAttribute> &headAttributes) {
        this->headAttributes = headAttributes;
        return *this;
    }

    hb &appendHeadAttributes(const std::vector<nAttribute> &headAttributes) {
        if (this->headAttributes.empty()) {
            this->setHeadAttributes(headAttributes);
        } else {
            this->headAttributes.insert(this->headAttributes.end(), headAttributes.begin(), headAttributes.end());
        }
        return *this;
    }

    hb &setHeadChildren(const std::vector<h> &headChildren) {
        this->headChildren = headChildren;
        return *this;
    }

    hb &appendHeadChildren(const std::vector<h> &headChildren) {
        if (this->headChildren.empty()) {
            this->setHeadChildren(headChildren);
        } else {
            this->headChildren.insert(this->headChildren.end(), headChildren.begin(), headChildren.end());
        }
        return *this;
    }

    h getBody() {
        return this->hBody;
    }

    hb &setBody(const h &body) {
        this->hBody = body;
        return *this;
    }

    hb &setBodyAttributes(const std::vector<nAttribute> &bodyAttributes) {
        this->bodyAttributes = bodyAttributes;
        return *this;
    }

    hb &appendBodyAttributes(const std::vector<nAttribute> &bodyAttributes) {
        if (this->bodyAttributes.empty()) {
            this->setBodyAttributes(bodyAttributes);
        } else {
            this->bodyAttributes.insert(this->bodyAttributes.end(), bodyAttributes.begin(), bodyAttributes.end());
        }
        return *this;
    }

    hb &setBodyChildren(const std::vector<h> &body) {
        this->bodyChildren = body;
        return *this;
    }

    hb &appendBodyChildren(const std::vector<h> &body) {
        if (this->bodyChildren.empty()) {
            this->setBodyChildren(body);
        } else {
            this->bodyChildren.insert(this->bodyChildren.end(), body.begin(), body.end());
        }
        return *this;
    }

    hDoctype getDoctype() {
        return this->doctype;
    }

    hb &setDoctype(const hDoctype &doctype) {
        this->doctype = doctype;
        return *this;
    }

    std::string toString(const hOut &out = hOut::multiline, const int &indentation = 1) {
        return this->construct().toString(out, indentation);
    }

    bool toFile(const std::string &path, const hOut &out = hOut::multiline) {
        std::ofstream file(path.c_str());

        if (file.is_open()) {
            file << this->toString(out);
            file.close();
            return true;
        }

        return false;
    }
};

#ifdef HH_SHORTER
typedef std::vector<h> hV;
typedef std::vector<nAttribute> nAV;

typedef hDoctype hD;
typedef hOut hO;
typedef hType hT;
typedef nAttribute nA;
#endif

#ifdef HH_NAMESPACE
}
#endif

#endif //HTML_HPP
