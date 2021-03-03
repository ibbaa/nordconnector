#ifndef SRC_SERVER_ASYNCHTTPDOWNLOADER_H_
#define SRC_SERVER_ASYNCHTTPDOWNLOADER_H_

#include <string>

class AsyncHTTPDownloader {
    public:
        std::string download(const std::string &url);
};

#endif /* SRC_SERVER_ASYNCHTTPDOWNLOADER_H_ */
