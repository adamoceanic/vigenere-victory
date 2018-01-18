#pragma once

#include <string>
#include <unordered_map>
#include <utility>

using std::string;
using std::unordered_map;
using std::pair;
using std::make_pair;




class Vigenere {
private:



public:
    void Start();


    Vigenere() {

    }
    ~Vigenere() {}


    // ctors and assign optors housekeeping (std and move)
    Vigenere(const Vigenere&) = delete;
    Vigenere& operator=(const Vigenere&) = delete;
    Vigenere(Vigenere&&) = delete;
    Vigenere& operator=(Vigenere&&) = delete;

    int TestTwentyTwo();
};