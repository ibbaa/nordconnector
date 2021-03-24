#ifndef SRC_UTIL_OUTPUT_H_
#define SRC_UTIL_OUTPUT_H_

#include <string>
#include "Poco/Path.h"

#define NORDCONNECTOR_DIR "nordc"

class Output {
    public:
        static void output(const std::string &message, bool verbose);
        static void err_output(const std::string &message);
        static std::string timestamp();
        static Poco::Path create_tmp_dir();
        static void delete_file(const std::string &filename);
};

#endif /* SRC_UTIL_OUTPUT_H_ */
