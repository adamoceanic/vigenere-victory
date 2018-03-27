#include <memory>

#include "include/Lib1/Vigenere.h"

using std::make_unique;

int main(int argc, char ** argv) {

    auto vig_entry = make_unique<Vigenere>();

    if (argv[1] == "--matlab") {
        vig_entry->Start(argv[1]);
    }
    else {
        vig_entry->Start("--cmd");
    }

    return 0;
}