#include <memory>
using std::make_unique;

#include "include/Lib1/Vigenere.h"

int main(int argc, char ** argv) {

    auto vig_entry = make_unique<Vigenere>();

    if (argv[1] == "--matlab") {
        vig_entry->Start("--matlab");
    }
    else {
        vig_entry->Start("--cmd");
    }

    return 0;
}