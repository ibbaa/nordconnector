#include "args/CommandLineParser.h"
#include "server/AsyncHTTPDownloader.h"
#include <iostream>
#include <string>
#include <Poco/Timestamp.h>
#include <Poco/Timezone.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>

int main(int argc, char *argv[]) {
    Poco::Timestamp now;
    Poco::DateTimeFormatter formatter;
    std::string nowstr = formatter.format(now, Poco::DateTimeFormat::SORTABLE_FORMAT, Poco::Timezone::tzd());
    std::cout << "Hello World! on " << nowstr << std::endl;
    CommandLineParser parser;
    const NVPNOptions &options = parser.parse(argc, argv);
    AsyncHTTPDownloader downloader;
    std::future<std::string> result = downloader.download(options.get_stat());
    const std::string &data = result.get();
    std::cout << data << std::endl;
    return 0;
}
