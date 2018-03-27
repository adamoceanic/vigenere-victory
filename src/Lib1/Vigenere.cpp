#include "include/Lib1/Vigenere.h"
#include "Vigenere_Impl.h"

void Vigenere::Start(string flag) {
    pImpl->Start(flag);
}

Vigenere::Vigenere() : pImpl{ make_unique<Vigenere_Impl>() } {

}

Vigenere::~Vigenere() { }



