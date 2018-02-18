#include "src/Lib1/VigenereDecipherer.h"

#include <thread>
#include <future>

using std::future;
using std::async;
using std::unordered_map;
using std::launch;

/*
 * Test
 */
#include <iostream>
#include <utility>
using std::cout;
using std::endl;
using std::pair;

/*
 * CONSIDER STD::MAP INSTEAD OF UNORDERED? HELP WITH SORTING LATER?
 *
 * CLEANUP TEST CODE AND COMMENTS
 *
 * EXCEPTION HANDLING
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

um_str_vec_t VigenereDecipherer::getAllNgramsWithLength(const string& cipher_text, int ngram_length) {

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

um_str_vec_t VigenereDecipherer::searchForRecurringNgramsWithLength(const string& cipher_text, int ngram_length) {

    cout << "ngram thread started with: " << ngram_length << '\n';

    auto ngrams = getAllNgramsWithLength(cipher_text, ngram_length);
    removeNgramsBelowOccurrenceThreshold(ngrams, 3);

    if (ngrams.empty()) {
        cout << "no useful ngrams of length: " << ngram_length << '\n';
    }
    return ngrams;
}

VigenereDecipherer::results_info_pair_t VigenereDecipherer::Decipher(const string& cipher_text) {

    // searchForRepeatingSubstrings
    // deliver a list of substrings and distances between them
    // suggest best possible key length via index counting and GCD etc

    // then start the frequency analysis shifting etc
    // how to represent freq table / results?
    // avoid massive functions - carve up sensibly


    std::array<unsigned int,5> possible_ngram_lengths = { 3, 4, 5, 6, 7};

    vector<future<um_str_vec_t>> futures;
    for (auto pnl : possible_ngram_lengths) {

        futures.emplace_back(async(
                launch::async, &VigenereDecipherer::searchForRecurringNgramsWithLength, this, std::ref(cipher_text), pnl));
    }

    um_str_vec_t all_ngrams;
    for (auto& fut : futures) {
        auto ngrams = fut.get();
        if (!ngrams.empty()) {
            for (auto &ngram : ngrams) {
                all_ngrams.insert(make_pair(ngram.first, ngram.second));
            }
        }
    }

    cout << "printing all filtered ngrams from main thread: " << endl;
    for (auto& p : all_ngrams) {

        cout << "substr: " << p.first << ", occurences: " << p.second.size() << '\n';
    }
    cout << "total ngrams: " << all_ngrams.size() << endl;

    pair<string, unordered_map<string,int>> result;

    return result;
}
