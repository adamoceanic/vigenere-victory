#include "src/Lib1/VigenereDecipherer.h"

#include <thread>
#include <future>
#include <queue>

#include <cmath>
#include <algorithm>

using std::future;
using std::async;
using std::launch;
using std::priority_queue;
using std::rotate;

/*
 * CLEANUP TEST CODE AND COMMENTS
 *
 * EXCEPTION HANDLING NEEDED
 */

void VigenereDecipherer::removeNgramsBelowOccurrenceThreshold(um_str_vec_t& all_ngrams, int threshold) {

    um_str_vec_t::iterator it = all_ngrams.begin();
    while (it != all_ngrams.end())
    {
        if (it->second.size() < threshold) {
            all_ngrams.erase(it++);
        }
        else ++it;
    }
}

VigenereDecipherer::um_str_vec_t
                    VigenereDecipherer::getAllNgramsWithLength(const string& cipher_text, int ngram_length) {

    int length = cipher_text.length();
    string sub;
    um_str_vec_t ngrams;
    for (int i = 0; i < length; ++i)
    {
        if (i + ngram_length > length) { break; }
        sub = cipher_text.substr(i, ngram_length);
        ngrams[sub].push_back(i);
    }

    // Will use RVO
    return ngrams;
}

VigenereDecipherer::um_str_vec_t
                    VigenereDecipherer::searchForRecurringNgramsWithLength(const string& cipher_text, int ngram_length) {

    auto ngrams = getAllNgramsWithLength(cipher_text, ngram_length);
    removeNgramsBelowOccurrenceThreshold(ngrams, 3);

    if (ngrams.empty()) {
        // THROW SOMETHING - PROBABLY
    }

    // Will use RVO
    return ngrams;
}

/**
 * Return the GCD of two integers
 *
 * @param u
 * @param v
 * @return
 */
int VigenereDecipherer::gcd(int u, int v)
{
    if (v)  { return gcd(v, u % v); }
    else {
        return u < 0 ? -u : u;
    }
}

/**
 * Return the GCD of a vector of integers
 *
 * @param nums
 * @return
 */
int VigenereDecipherer::multiGCD(vector<int>& nums)
{
    if (nums.empty()) { return 0; }
    else if (nums.size() == 1) { return nums[0]; }
    else if (nums.size() == 2) { return gcd(nums[0], nums[1]); }

    nums[1] = gcd(nums[0], nums[1]);
    nums.erase(nums.begin());
    return multiGCD(nums);
}

vector<int> VigenereDecipherer::getGCDs(const vector<vector<int>>& occurrences, int begin, int end) {

    vector<int> distances;
    vector<int> GCDs;
    int GCD = 0;
    for (int i = begin; i < end; ++i) {
        for (int j = 0; j < occurrences[i].size() - 1; ++j) {
            distances.push_back(occurrences[i][j + 1] - occurrences[i][j]);
        }
        GCD = multiGCD(distances);
        GCDs.push_back(GCD);
        distances.clear();
    }
    // RVO
    return GCDs;
}

int VigenereDecipherer::getKeyLength(vector<vector<int>>& all_ngram_occurrences) {

    unordered_map<int, int> all_GCDs;
    priority_queue<pair<int, int>, vector<pair<int,int>>, GCDComparator> all_GCDs_Sorted;
    vector<future<vector<int>>> futures;

    int batch_size = all_ngram_occurrences.size() / 6;
    auto begin = 0;
    auto end = begin + batch_size;

    while (begin < all_ngram_occurrences.size()) {
        futures.emplace_back(async(launch::async, &VigenereDecipherer::getGCDs,
                                   this, std::ref(all_ngram_occurrences), begin, end));

        begin = end;
        end = begin + batch_size;
        if (end > all_ngram_occurrences.size()) {
            end = all_ngram_occurrences.size();
        }
    }
    for (auto& fut : futures) {
        auto GCDs = fut.get();
        if (!GCDs.empty()) {
            for (auto &GCD : GCDs) {
                all_GCDs[GCD]++;
            }
        }
    }
    for (auto &GCD_pair : all_GCDs) {
        all_GCDs_Sorted.emplace(GCD_pair);
    }
    return all_GCDs_Sorted.top().first;
}

vector<vector<char>> VigenereDecipherer::columniseCipherText(const string& cipher_text, int num_cols) {

    vector<vector<char>> columns(num_cols);
    for (int i = 0; i < cipher_text.size(); ++i) {
        columns[i % num_cols].push_back(cipher_text[i]);
    }
    return columns;
}

/**
 * Returns the relative frequencies of the characters in one column of the ciphertext.
 * Remember: Each char in a column was encrypted with the same letter of the key. No. of columns = key length
 *
 * @param column
 * @return
 */
vector<double> VigenereDecipherer::getColumnCharRelativeFreqs(const vector<char>& column) {

    vector<double> char_counts;
    char_counts.reserve(26);

    double cum_count = 0;
    unordered_map<char, int> freqs;
    freqs.reserve(26);

    for (auto& letter : column) {
        freqs[letter]++;
        ++cum_count;
    }
    for (char c : eng_alphabet_) {
        auto found = freqs.find(c);
        if (found != freqs.end()) {
            char_counts.push_back((freqs[c] / cum_count));
        }
        else {
            char_counts.push_back(0);
        }
    }
    return char_counts;
}

/**
 * Returns the relative frequencies of the characters in each of the columns of the ciphertext.
 * Remember: Each char in a column was encrypted with the same letter of the key. No. of columns = key length
 *
 * @param columns
 * @return
 */
vector<vector<double>> VigenereDecipherer::getAllCharRelativeFreqs(const vector<vector<char>>& columns) {

    vector<future<vector<double>>> futures;
    for (const auto& column : columns) {
        futures.emplace_back(async(launch::async, &VigenereDecipherer::getColumnCharRelativeFreqs, this, std::ref(column)));
    }
    vector<vector<double>> all_char_counts;
    all_char_counts.reserve(columns.size());

    for (auto& fut : futures) {
        auto counts = fut.get();
        all_char_counts.push_back(std::move(counts));
    }
    return all_char_counts;
}


double VigenereDecipherer::calcRSS (const array<double, 26>& eng_freqs, vector<double>& relative_freqs) {
    double rss = 0;
    for (int i = 0; i < eng_freqs.size(); ++i) {
        rss += pow((eng_freqs[i] - relative_freqs[i]), 2);
    }
    return rss;
}


double VigenereDecipherer::calcRMSE (double rss, double value_count) {
    return sqrt((1 / value_count) * rss);
}

char VigenereDecipherer::findKeyChar(const array<double, 26>& eng_freqs, vector<double>& relative_freqs) {

    double lowest_rmse = 1000;
    int shift_num = 0;
    int shift_counter = 0;

    for (int i = 0; i < eng_freqs.size(); ++i) {
        double rss;
        double rmse;

        rss = calcRSS(eng_freqs, relative_freqs);
        rmse = calcRMSE(rss, 26);

        if (rmse < lowest_rmse) {
            lowest_rmse = rmse;
            shift_num = shift_counter;
        }
        std::rotate(relative_freqs.begin(), relative_freqs.begin() + 1, relative_freqs.end());
        ++shift_counter;
    }
    return eng_alphabet_[shift_num];
}

string VigenereDecipherer::getKey(vector<vector<double>> all_relative_frequencies) {

    string key;
    for (auto& rel_freq : all_relative_frequencies) {
        char key_char = findKeyChar(VigenereDecipherer::english_frequencies_, rel_freq);
        key += key_char;
    }
    return key;
}

pair<string, int> VigenereDecipherer::Decipher(const string& cipher_text) {

    // GET REPEATING NGRAMS AND NUMBER OF OCCURRENCES
    std::array<unsigned int,5> possible_ngram_lengths = { 3, 4, 5, 6, 7};

    vector<future<um_str_vec_t>> futures;
    for (auto pnl : possible_ngram_lengths) {

        futures.emplace_back(async(launch::async, &VigenereDecipherer::searchForRecurringNgramsWithLength,
                                   this, std::ref(cipher_text), pnl));
    }

    vector<vector<int>> all_ngram_occurrences;

    for (auto& fut : futures) {
        auto ngrams = fut.get();
        if (!ngrams.empty()) {
            for (auto &ngram : ngrams) {
                all_ngram_occurrences.emplace_back(ngram.second);
            }
        }
    }

    // GET THE LIKELY KEY LENGTH
    int key_length = getKeyLength(all_ngram_occurrences);

    // FREQUENCY ANALYSIS
    // columnise the string
    auto ciphertext_columns = columniseCipherText(cipher_text, key_length);

    // analyse the relative frequencies of each column
    auto all_relative_frequencies = getAllCharRelativeFreqs(ciphertext_columns);

    // deduce key via freq analysis and shifting
    string encryption_key = getKey(all_relative_frequencies);


    // DECODE THE MESSAGE

    return pair<string, int>(encryption_key, key_length);
}
