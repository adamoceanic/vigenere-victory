#include <memory>
#include <iostream>


#include "include/Lib1/Vigenere.h"


using std::make_unique;
using std::cout;
using std::endl;

/*
ostream& operator<< (ostream& os, const MyType& value) {
    os << convert ( value );
    return os;
}
 */

int main() {

    auto vig_entry = make_unique<Vigenere>();
    vig_entry->Start();

    return 0;
}