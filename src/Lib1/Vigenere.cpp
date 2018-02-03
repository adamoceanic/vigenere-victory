#include "include/Lib1/Vigenere.h"
#include "Vigenere_Impl.h"

void Vigenere::Start() {
    pImpl->Start();
}

Vigenere::Vigenere() : pImpl{ make_unique<Vigenere_Impl>() } {

}

Vigenere::~Vigenere() { }



