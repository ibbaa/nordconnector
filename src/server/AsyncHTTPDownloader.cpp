#include "server/AsyncHTTPDownloader.h"
#include "util/Output.h"
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/SharedPtr.h"
#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPSStreamFactory.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"

bool AsyncHTTPDownloader::initSSL() {
    try {
        Poco::Net::HTTPStreamFactory::registerFactory();
        Poco::Net::HTTPSStreamFactory::registerFactory();
        Poco::Net::initializeSSL();
        return true;
    } catch (Poco::Exception &exc) {
        Output::err_output("Error initializing SSL " + exc.displayText() + "\n");
    } catch (...) {
        Output::err_output("Error initializing SSL.\n");
    }
    return false;
}

std::future<std::string> AsyncHTTPDownloader::download(const std::string &urlstr, bool verbose) {
    return std::async(std::launch::async, &AsyncHTTPDownloader::async_download, this, urlstr, verbose);
}

std::string AsyncHTTPDownloader::async_download(const std::string &urlstr, bool verbose) {
    std::string data;
    try {
        Output::output("Starting download from " + urlstr + "\n", verbose);
        Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptr_handler(new Poco::Net::AcceptCertificateHandler(false));
        Poco::Net::Context::Ptr ptr_context(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, ""));
        Poco::Net::SSLManager::instance().initializeClient(0, ptr_handler, ptr_context);
        Poco::URI uri(urlstr);
        std::unique_ptr<std::istream> ptr_str(Poco::URIStreamOpener::defaultOpener().open(uri));
        Poco::StreamCopier::copyToString(*ptr_str.get(), data);
        Output::output("Download from " + urlstr + " finished\n", verbose);
    } catch (Poco::Exception &exc) {
        Output::err_output("Error downloading from " + urlstr + ": " + exc.displayText() + "\n");
    } catch (...) {
        Output::err_output("Error downloading from " + urlstr + "\n");
    }
    return data;
}
