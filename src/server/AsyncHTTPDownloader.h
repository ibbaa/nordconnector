#ifndef SRC_SERVER_ASYNCHTTPDOWNLOADER_H_
#define SRC_SERVER_ASYNCHTTPDOWNLOADER_H_

#include <future>
#include <string>

class AsyncHTTPDownloader {
    public:
        std::future<std::string> download(const std::string &url);
    private:
        std::string async_download(const std::string &url);
};

#endif /* SRC_SERVER_ASYNCHTTPDOWNLOADER_H_ */
