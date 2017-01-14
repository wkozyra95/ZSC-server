#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>

enum ResponseVersion {
    HTTP_WELCOME_PAGE,
    HTTP_ANOTHER_PAGE,
};

class HTTPResponse {
    private:
        std::string response;
    public:
        HTTPResponse(ResponseVersion verion);
        const char* getPayload();
        void getWelcomePage();
};


#endif // HTTP_RESPONSE_H
