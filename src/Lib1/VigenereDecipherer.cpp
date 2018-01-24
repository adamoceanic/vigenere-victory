#include "src/Lib1/VigenereDecipherer.h"

VigenereDecipherer::results_info_pair_t VigenereDecipherer::Decipher(string ciphertext) {

    string plain_text;
    unordered_map<string, int> info;

    auto result = make_pair(plain_text,info);

    return result;
}
