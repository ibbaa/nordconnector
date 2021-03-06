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

bool AsyncHTTPDownloader::initSSL() {
    try {
        Poco::Net::HTTPStreamFactory::registerFactory();
        Poco::Net::HTTPSStreamFactory::registerFactory();
        Poco::Net::initializeSSL();
        return true;
    } catch (Poco::Exception &exc) {
        std::cerr << "Error initializing SSL " << exc.displayText() << std::endl;
    }
    return false;
}

std::future<std::string> AsyncHTTPDownloader::download(const std::string &urlstr, bool verbose) {
    return std::async(std::launch::async, &AsyncHTTPDownloader::async_download, *this, urlstr, verbose);
}

std::string AsyncHTTPDownloader::async_download(const std::string &urlstr, bool verbose) {
    std::string data;
    try {
        if (verbose) {
            std::cout << "Starting download from " << urlstr << std::endl;
        }
        Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler(new Poco::Net::AcceptCertificateHandler(false));
        Poco::Net::Context::Ptr ptrContext(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, ""));
        Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
        Poco::URI uri(urlstr);
        std::unique_ptr<std::istream> pStr(Poco::URIStreamOpener::defaultOpener().open(uri));
        Poco::StreamCopier::copyToString(*pStr.get(), data);
        if (verbose) {
            std::cout << "Download from " << urlstr << " finished" << std::endl;
        }
    } catch (Poco::Exception &exc) {
        std::cerr << "Error downloading from " << urlstr << ": " << exc.displayText() << std::endl;
    }
    return data;
}
