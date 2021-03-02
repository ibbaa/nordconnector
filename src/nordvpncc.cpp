#include "args/CommandLineParser.h"
#include <Poco/Timestamp.h>
#include <Poco/Timezone.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    Poco::Timestamp now;
    Poco::DateTimeFormatter formatter;
    std::string nowstr = formatter.format(now, Poco::DateTimeFormat::SORTABLE_FORMAT, Poco::Timezone::tzd());
    std::cout << "Hello World! on " << nowstr << "\n";
    CommandLineParser parser;
    const NVPNOptions &options = parser.parse(argc, argv);
    return 0;
}