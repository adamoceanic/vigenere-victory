

#include <string>


#include "../Lib1/inc/Vigenere.h"
#include "../Lib1/inc/VigenereDecipherer.h"
#include "../Lib1/api/Matlab.cpp"

using std::string;

/*
ostream& operator<< (ostream& os, const MyType& value) {
    os << convert ( value );
    return os;
}
 */

int main() {

    string cipher_text;



    auto vd = new VigenereDecipherer();
    vd->Decipher(cipher_text);




    return 0;
}