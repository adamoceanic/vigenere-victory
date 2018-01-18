#pragma once

#include <string>
#include <unordered_map>
#include <utility>

using std::string;
using std::unordered_map;
using std::pair;
using std::make_pair;




class VigenereDecipherer {
private:



public:
    using results_info_pair_t = pair<string, unordered_map<string,int>>;

    results_info_pair_t Decipher(string ciphertext);






    VigenereDecipherer() {

    }
    ~VigenereDecipherer() {

    }


    // ctors and assign optors housekeeping (std and move)
    VigenereDecipherer(const VigenereDecipherer&) = delete;
    VigenereDecipherer& operator=(const VigenereDecipherer&) = delete;
    VigenereDecipherer(VigenereDecipherer&&) = delete;
    VigenereDecipherer& operator=(VigenereDecipherer&&) = delete;

    int TestTwentyTwo();
};