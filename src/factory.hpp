#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/ClassLoader.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/Util/Application.h>
#include <Poco/RegularExpression.h>

#include "ipfilter.hpp"

namespace webcppd {

    class factory : public Poco::Net::HTTPRequestHandlerFactory {
    public:
        factory();
        virtual~factory();
        Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
    private:
        Poco::Util::Application& app;
        webcppd::ipfilter ipfilter;
        Poco::AutoPtr<Poco::FileChannel> logger;
        Poco::ClassLoader<Poco::Net::HTTPRequestHandler> classLoader;
        std::vector<std::tuple<std::string, std::string, std::string>> route;
        Poco::RegularExpression hotlinkRegex;
    private:
        void initialize();
        void uninitialize();
        void config_log();
        void config_route();
        void config_mod();
        std::tuple<bool, std::vector<std::string>, std::string> get_route(const std::string& method, const std::string& path);
    };
}
#endif /* FACTORY_HPP */

