#include "HTTPResponse.h"

HTTPResponse::HTTPResponse(ResponseVersion version){
    if( version == HTTP_WELCOME_PAGE) {
        this->getWelcomePage();
    } else if( version == HTTP_ANOTHER_PAGE ) {
        this->getAnotherPage();
    }
}

const char* HTTPResponse::getPayload() {
    return this->response.c_str();
}

void HTTPResponse::getWelcomePage() {
    std::string content = std::string() + "<!doctype html>\r\n"+
        "<html lang=en>\r\n"+
        "<head>\r\n"+
        "</head>\r\n"+
        "<body>\r\n"+
        "<p>Welcome Page</p>\n"+
        "<a href=\":8000./index.html\">go to another page</a>\r\n"+
        "</body>\r\n"+
        "</html>\r\n   ";

    std::string header = std::string() + "HTTP/1.1 200 OK\r\n" +
              "Content-Type: text/html\r\n\r\n";
    this->response = header + content;  
}

void HTTPResponse::getAnotherPage() {
    std::string content = std::string() + "<!doctype html>\r\n"+
        "<html lang=en>\r\n"+
        "<head>\r\n"+
        "</head>\r\n"+
        "<body>\r\n"+
        "<p>Another page</p>\r\n"+
        "<a href=\":9000./index.html\">go to another page</a>\r\n"+
        "</body>\r\n"+
        "</html>\r\n   ";

    std::string header = std::string() + "HTTP/1.1 200 OK\r\n" +
              "Content-Type: text/html\r\n\r\n";
    this->response = header + content;  
}


/*
header = "HTTP/1.1 200 OK\
          Date: Sat, 14 Jan 2017 15:15:15 GMT\
          Server: Apache/2.2.31 (Unix) mod_ssl/2.2.31 OpenSSL/0.9.8zh\
          Last-Modified: Wed, 30 Nov 2016 16:17:21 GMT\
          ETag: \"6336663-c22-542870a194640\"\
          Accept-Ranges: bytes\
          Content-Length: 3106\
          Content-Type: text/html\
          X-Cache: MISS from ds14\
          X-Cache-Lookup: MISS from ds14:3120\
          Via: 1.1 ds14 (squid)\
          Connection: keep-alive\
          "
          */
