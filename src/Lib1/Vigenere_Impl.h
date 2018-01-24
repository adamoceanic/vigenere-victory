#pragma once

#include <memory>

using std::unique_ptr;

class Input;
class VigenereDecipherer;

class Vigenere_Impl {
private:
    unique_ptr<Input> input_manager_;
    unique_ptr<VigenereDecipherer> vigenere_decipherer_;
public:
    void Start();

    Vigenere_Impl();
    ~Vigenere_Impl();
    // ctors and assign optors housekeeping (std and move)
    Vigenere_Impl(const Vigenere_Impl&) = delete;
    Vigenere_Impl& operator=(const Vigenere_Impl&) = delete;
    Vigenere_Impl(Vigenere_Impl&&) = delete;
    Vigenere_Impl& operator=(Vigenere_Impl&&) = delete;
};
