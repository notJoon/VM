#include <sstream>

/**
 * @file Logger.h
 * @brief Logger and error reporter. 
 */
#ifndef Logger_h
#define Logger_h

class ErrorLoggerMessage : public std::basic_ostringstream<char> {
    public:
        ~ErrorLoggerMessage() {
            fprintf(stderr, "Fatal Error: %s\n", str().c_str());
            exit(EXIT_FAILURE);
        }
};

#define DIE ErrorLoggerMessage()

#define log(value) std::cout << #value << " = " << (value) << "\n";

#endif