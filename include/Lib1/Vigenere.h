#pragma once

#include <memory>
#include <string>

using std::make_unique;
using std::unique_ptr;
using std::string;

class Vigenere_Impl;

    class Vigenere {
    private:
        unique_ptr<Vigenere_Impl> pImpl;
    public:
        void Start(string flag = "--desktop");

        Vigenere();

        ~Vigenere();

        // ctors and assign optors housekeeping (std and move)
        Vigenere(const Vigenere &) = delete;

        Vigenere &operator=(const Vigenere &) = delete;

        Vigenere(Vigenere &&) = delete;

        Vigenere &operator=(Vigenere &&) = delete;
    };
