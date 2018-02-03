#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <array>

using std::string;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::array;




class VigenereDecipherer {
private:
    // pass key lengths by cin or something eventually
    unordered_map<string, int> searchForRepeatingSubstrings(string cipher_text, int key_lengths);

public:
    using results_info_pair_t = pair<string, unordered_map<string,int>>;

    results_info_pair_t Decipher(string ciphertext);


    VigenereDecipherer() {}
    ~VigenereDecipherer() {

    }


    // ctors and assign optors housekeeping (std and move)
    VigenereDecipherer(const VigenereDecipherer&) = delete;
    VigenereDecipherer& operator=(const VigenereDecipherer&) = delete;
    VigenereDecipherer(VigenereDecipherer&&) = delete;
    VigenereDecipherer& operator=(VigenereDecipherer&&) = delete;
};