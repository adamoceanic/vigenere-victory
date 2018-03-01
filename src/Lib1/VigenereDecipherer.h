#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <array>
#include <vector>

using std::string;
using std::unordered_map;
using std::multimap;
using std::pair;
using std::make_pair;
using std::array;
using std::vector;

class VigenereDecipherer {
private:
    struct OccurrenceComparator {
        bool operator()(const vector<int>& a, const vector<int>& b) {
            return a.size() > b.size();
        }
    };
    struct GCDComparator {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        }
    };

    int gcd(int u, int v);
    int multiGCD(vector<int>& nums);

public:
    using um_str_vec_t = unordered_map<string, vector<int>>;
    using results_info_pair_t = pair<string, unordered_map<string,int>>;

    um_str_vec_t searchForRecurringNgramsWithLength(const string& cipher_text, int ngram_length);
    um_str_vec_t getAllNgramsWithLength(const string& cipher_text, int key_lengths);
    void removeNgramsBelowOccurrenceThreshold(um_str_vec_t& all_ngrams, int threshold);
    int getKeyLength(vector<vector<int>>& all_ngram_occurrences);
    vector<int> getGCDs(const vector<vector<int>>& occurrences,
                                    int begin, int end);

    results_info_pair_t Decipher(const string& ciphertext);

    VigenereDecipherer() = default;
    ~VigenereDecipherer() = default;

    // ctors and assign optors housekeeping (std and move)
    VigenereDecipherer(const VigenereDecipherer&) = delete;
    VigenereDecipherer& operator=(const VigenereDecipherer&) = delete;
    VigenereDecipherer(VigenereDecipherer&&) = delete;
    VigenereDecipherer& operator=(VigenereDecipherer&&) = delete;
};