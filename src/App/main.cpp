#include <memory>

#include "include/Lib1/Vigenere.h"

using std::make_unique;

int main() {

    auto vig_entry = make_unique<Vigenere>();
    vig_entry->Start();

    return 0;
}