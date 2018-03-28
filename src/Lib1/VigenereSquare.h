#pragma once

#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <cassert>

using std::string;
using std::vector;
using std::array;

class VigenereSquare {

private:
    VigenereSquare() = default;
    ~VigenereSquare() = default;

    static string genKeyString(string cipher_text, string key) {

        string key_string;
        key_string.reserve(cipher_text.length());
        int quotient = cipher_text.length() / key.length();
        int remainder = cipher_text.length() % key.length();
        int counter = 0;
        while (counter < quotient) {
            key_string += key;
            counter++;
        }
        for (int i = 0; i < remainder; ++i) {
            key_string += key[i];
        }
        return key_string;
    }

    static int pythonStyleMod(int a, int b) {
        assert(b > 0);
        int ret = a % b;
        if constexpr  (std::is_unsigned_v<int>)
        {
            return ret;
        } else {
            return (ret >= 0) ? (ret) : (ret + b);
        }
    }

    static constexpr array<char, 26> eng_alphabet_ = {'A','B','C','D', 'E', 'F','G','H','I','J','K','L','M',
                                                      'N', 'O','P','Q','R','S','T','U','V','W','X','Y','Z'};


    /* This structure is completely unnecessary but fun to have */
    static constexpr array<array<char, 26>, 26> tabula_recta_ =
            {{ {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
             {'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A'},
             {'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B'},
             {'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C'},
             {'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D'},
             {'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E'},
             {'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F'},
             {'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G'},
             {'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H'},
             {'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I'},
             {'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J'},
             {'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K'},
             {'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L'},
             {'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M'},
             {'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N'},
             {'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'},
             {'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'},
             {'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'},
             {'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R'},
             {'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'},
             {'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'},
             {'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'},
             {'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'},
             {'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W'},
             {'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'},
             {'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y'} }};

public:

    static string decrypt(string cipher_text, string key) {
        string plain_text;
        string key_string = VigenereSquare::genKeyString(cipher_text, key);
        for (int i = 0; i < cipher_text.length(); ++i) {

            plain_text += eng_alphabet_[pythonStyleMod(((cipher_text[i] - 65) - (key_string[i] - 65)), 26)];
        }
        return plain_text;
    }
};