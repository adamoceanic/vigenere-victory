#pragma once

#include <memory>

using std::make_unique;
using std::unique_ptr;

class Vigenere_Impl;

class Vigenere {
private:
    unique_ptr<Vigenere_Impl> pImpl;

public:
    void Start();


    Vigenere();
    ~Vigenere();


    // ctors and assign optors housekeeping (std and move)
    Vigenere(const Vigenere&) = delete;
    Vigenere& operator=(const Vigenere&) = delete;
    Vigenere(Vigenere&&) = delete;
    Vigenere& operator=(Vigenere&&) = delete;

    int TestTwentyTwo();
};