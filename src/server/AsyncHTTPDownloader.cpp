#include "server/AsyncHTTPDownloader.h"
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/SharedPtr.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/HTTPSStreamFactory.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/StreamCopier.h>
#include <Poco/Exception.h>

std::string AsyncHTTPDownloader::download(const std::string &urlstr) {
    std::string data;
    try {
        Poco::Net::HTTPStreamFactory::registerFactory();
        Poco::Net::HTTPSStreamFactory::registerFactory();
        Poco::Net::initializeSSL();
        Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler(new Poco::Net::AcceptCertificateHandler(false));
        Poco::Net::Context::Ptr ptrContext(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, ""));
        Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
        Poco::URI uri(urlstr);
        std::unique_ptr<std::istream> pStr(Poco::URIStreamOpener::defaultOpener().open(uri));
        Poco::StreamCopier::copyStream(*pStr.get(), std::cout);
    } catch (Poco::Exception &exc) {
        std::cerr << "Error downloading from " << urlstr << ": " << exc.displayText() << std::endl;
        exit(3);
    }
    return data;
}

