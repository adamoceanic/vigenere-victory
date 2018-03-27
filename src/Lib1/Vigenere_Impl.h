#pragma once

#include <memory>
#include <string>
#include <vector>

using std::unique_ptr;
using std::string;
using std::vector;

class Input;
class VigenereDecipherer;

class Vigenere_Impl {
private:
    unique_ptr<Input> input_manager_;
    unique_ptr<VigenereDecipherer> vigenere_decipherer_;

    vector<string> welcome_message_ = {" VIGENERE-VICTORY V.1 MARCH 2018",
                                      " -------------------------------",
                                      " The ciphertext must (currently) be ALL CAPS, and have",
                                      " no whitespace, numbers, or punctuation.",
                                      " You can experiment with some test ciphers from the",
                                      " file 'test_ciphers.txt' inside the 'doc' directory.",
                                      " Paste in an encrypted text (800+ characters) and press enter:"};

public:
    void Start(string flag);

    Vigenere_Impl();
    ~Vigenere_Impl();
    // ctors and assign optors housekeeping (std and move)
    Vigenere_Impl(const Vigenere_Impl&) = delete;
    Vigenere_Impl& operator=(const Vigenere_Impl&) = delete;
    Vigenere_Impl(Vigenere_Impl&&) = delete;
    Vigenere_Impl& operator=(Vigenere_Impl&&) = delete;
};
