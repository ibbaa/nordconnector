#include "util/Output.h"
#include <iostream>
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/File.h"
#include "Poco/Exception.h"

void Output::output(const std::string &message, bool verbose) {
    if (verbose) {
        std::cout << message;
    }
}

void Output::err_output(const std::string &message) {
    std::cerr << message;
}

std::string Output::timestamp() {
    Poco::LocalDateTime now;
    return Poco::DateTimeFormatter::format(now, "%Y-%m-%d_%H:%M:%S_%i");
}

Poco::Path Output::create_tmp_dir() {
    Poco::Path tmpdir_path = Poco::Path(Poco::Path::temp()).append(NORDCONNECTOR_DIR);
    Poco::File tmp_dir(tmpdir_path);
    tmp_dir.createDirectories();
    return tmpdir_path;
}

void Output::delete_file(const std::string &filename) {
    try {
        Poco::File file(filename);
        if (file.exists()) {
            file.remove();
        }
    } catch (Poco::Exception &exc) {
        Output::err_output("Error deleting file: " + filename + " " + exc.displayText() + "\n");
    } catch (...) {
        Output::err_output("Error deleting file: " + filename + "\n");
    }
}
