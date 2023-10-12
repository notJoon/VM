#include <iostream>

#include "src/vm/VM.h"

/**
 * @brief VM main executable.
 */
int main(int argc, char const *argv[]) {
    VM vm;
    auto result = vm.execute(R"(42)");

    log(AS_CPPSTRING(result));

    std::cout << "All done!\n";
    return 0;
}