#ifndef SRC_SERVER_ASYNCHTTPDOWNLOADER_H_
#define SRC_SERVER_ASYNCHTTPDOWNLOADER_H_

#include <future>
#include <string>

class AsyncHTTPDownloader {
    public:
        static bool initSSL();
        std::future<std::string> download(const std::string &url, bool verbose);
    private:
        std::string async_download(const std::string &url, bool verbose);
};

#endif /* SRC_SERVER_ASYNCHTTPDOWNLOADER_H_ */
