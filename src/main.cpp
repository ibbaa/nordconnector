#include <iostream>
#include <string>
#include "Poco/Timestamp.h"
#include "Poco/Timezone.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

int main(int argc, char *argv[]) {
    Poco::Timestamp now;
    Poco::DateTimeFormatter formatter;
    std::string nowstr = formatter.format(now, Poco::DateTimeFormat::SORTABLE_FORMAT, Poco::Timezone::tzd());
    std::cout << "Hello World! on " << nowstr << "\n";
    return 0;
}
