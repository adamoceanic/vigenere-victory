#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <array>
#include <vector>

using std::string;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::array;
using std::vector;

using um_str_vec_t = unordered_map<string, vector<int>>;



class VigenereDecipherer {
private:

    um_str_vec_t searchForRecurringNgramsWithLength(const string& cipher_text, int ngram_length);
    um_str_vec_t getAllNgramsWithLength(const string& cipher_text, int key_lengths);
    void removeNgramsBelowOccurrenceThreshold(um_str_vec_t& all_ngrams, int threshold);

public:
    using results_info_pair_t = pair<string, unordered_map<string,int>>;

    results_info_pair_t Decipher(const string& ciphertext);

    VigenereDecipherer() = default;
    ~VigenereDecipherer() = default;

    // ctors and assign optors housekeeping (std and move)
    VigenereDecipherer(const VigenereDecipherer&) = delete;
    VigenereDecipherer& operator=(const VigenereDecipherer&) = delete;
    VigenereDecipherer(VigenereDecipherer&&) = delete;
    VigenereDecipherer& operator=(VigenereDecipherer&&) = delete;
};