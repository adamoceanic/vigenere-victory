#include "src/Lib1/VigenereDecipherer.h"

#include <thread>
#include <future>
#include <queue>

using std::future;
using std::async;
using std::launch;
using std::priority_queue;

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

// get GCD of 2 numbers
int VigenereDecipherer::gcd(int u, int v)
{
    if (v)  { return gcd(v, u % v); }
    else {
        return u < 0 ? -u : u;
    }
}

// get GCD of vector of numbers
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

int VigenereDecipherer::Decipher(const string& cipher_text) {

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


    return key_length;
}
