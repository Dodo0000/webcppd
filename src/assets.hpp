#ifndef ASSETS_HPP
#define ASSETS_HPP


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>



namespace webcpp {

    class assets : public Poco::Net::HTTPRequestHandler {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    };

}

#endif /* ASSETS_HPP */

