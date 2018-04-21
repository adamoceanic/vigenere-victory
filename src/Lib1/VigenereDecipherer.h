#pragma once

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <utility>
using std::pair;
using std::make_pair;

#include <array>
using std::array;

#include <vector>
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

    // relative frequencies of A - Z letters in english language normalized to 0 < x < 1
    static constexpr array<double, 26> english_frequencies_ =
            {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094,
             0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
             0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
             0.01974, 0.00074};

    static constexpr array<char, 26> eng_alphabet_ = {'A','B','C','D', 'E', 'F','G','H','I','J','K','L','M',
                                                      'N', 'O','P','Q','R','S','T','U','V','W','X','Y','Z'};


public:
    using um_str_vec_t = unordered_map<string, vector<int>>;
    using results_info_pair_t = pair<string, unordered_map<string,int>>;

    um_str_vec_t searchForRecurringNgramsWithLength(const string& cipher_text, int ngram_length);
    um_str_vec_t getAllNgramsWithLength(const string& cipher_text, int key_lengths);
    void removeNgramsBelowOccurrenceThreshold(um_str_vec_t& all_ngrams, int threshold);
    int getKeyLength(vector<vector<int>>& all_ngram_occurrences);
    vector<int> getGCDs(const vector<vector<int>>& occurrences,
                                    int begin, int end);

    vector<vector<char>> columniseCipherText(const string& cipher_text, int num_cols);
    vector<double> getColumnCharRelativeFreqs(const vector<char>& column);
    vector<vector<double>> getAllCharRelativeFreqs(const vector<vector<char>>& columns);
    double calcRSS (const array<double, 26>& eng_freqs, vector<double>& relative_freqs);
    double calcRMSE (double rss, double value_count);
    char findKeyChar(const array<double, 26>& eng_freqs, vector<double>& relative_freqs);
    string getKey(vector<vector<double>> all_relative_frequencies);

    pair<string, int> Decipher(const string& ciphertext);

    VigenereDecipherer() = default;
    ~VigenereDecipherer() = default;

    // ctors and assign optors housekeeping (std and move)
    VigenereDecipherer(const VigenereDecipherer&) = delete;
    VigenereDecipherer& operator=(const VigenereDecipherer&) = delete;
    VigenereDecipherer(VigenereDecipherer&&) = delete;
    VigenereDecipherer& operator=(VigenereDecipherer&&) = delete;
};