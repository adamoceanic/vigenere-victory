#include <iostream>

#include "inc/MyClass.h"

using std::cout;
using std::endl;

/*
ostream& operator<< (ostream& os, const MyType& value) {
    os << convert ( value );
    return os;
}
 */

int main() {
    cout << "Hello, World!" << endl;
    MyClass mc;
    cout << mc.ReturnTwentyTwo() << endl;
    cout << mc.ReturnFortyFour() << endl;

    return 0;
}