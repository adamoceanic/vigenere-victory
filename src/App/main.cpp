#include <memory>

#include "include/Lib1/Vigenere.h"

using std::make_unique;

/*
ostream& operator<< (ostream& os, const MyType& value) {
    os << convert ( value );
    return os;
}
 */

int main() {

    auto vig_entry = make_unique<Vigenere>();
     vig_entry->Start();

    int land_here = 10;

    return 0;
}