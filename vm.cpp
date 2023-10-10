#include "src/vm/VM.h"

/**
 * @brief VM main executable.
 */
int main(int argc, char** argv) {
    VM vm;
    vm.execute(R"(42)");
    return 0;
}