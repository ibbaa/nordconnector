#ifndef SRC_UTIL_OUTPUT_H_
#define SRC_UTIL_OUTPUT_H_

#include <string>
#include "Poco/Path.h"

#define NORDVPNCC_DIR "nordvpncc"

class Output {
    public:
        static void output(const std::string &message, bool verbose);
        static void err_output(const std::string &message);
        static std::string timestamp();
        static Poco::Path create_tmp_dir();
};

#endif /* SRC_UTIL_OUTPUT_H_ */
