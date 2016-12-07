#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include <vector>
#include <map>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/ClassLoader.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/RegularExpression.h>

#include "ipfilter.hpp"

namespace webcppd {

    class factory : public Poco::Net::HTTPRequestHandlerFactory {
    public:
        factory();
        virtual~factory();
        Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
    private:
        Poco::Util::LayeredConfiguration &serverConf;
        webcppd::ipfilter ipfilter;
        Poco::AutoPtr<Poco::FileChannel> logger;
        Poco::ClassLoader<Poco::Net::HTTPRequestHandler> classLoader;
        std::vector<std::pair<std::string, std::string> > route;
        Poco::RegularExpression hotlinkRegex;
    };
}
#endif /* FACTORY_HPP */

