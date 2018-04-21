#include "catch.h"

#include "src/Lib1/VigenereDecipherer.h"

TEST_CASE("VigenereDecipherer class basics", "[vigenere-decipherer]") {
    // ========================================
    // Setup
    auto vig_dec = new VigenereDecipherer();

    // setup for getAllNgramsWithLength()
    VigenereDecipherer::um_str_vec_t all_ngrams;
    string test_ciphertext = "NIGFMNGCGFBHISSMVWTL";

    // setup for removeNgramsBelowOccurrenceThreshold()
    VigenereDecipherer::um_str_vec_t remove_ngrams;
    int threshold = 3;
    vector<int> count = {1,2,3};
    vector<int> count2 = {1,2};
    vector<int> count3 = {1,2,3,4};
    remove_ngrams.insert({"TEST", count});
    remove_ngrams.insert({"TEST2", count2});
    remove_ngrams.insert({"TEST3", count3});

    // setup for searchForRecurringNgramsWithLength()
    VigenereDecipherer::um_str_vec_t search_ngrams;
    string test_ciphertext_long = "NIGFMNGCGFBHISSMVWTLNIGFMNGCGFBHISSMVWTLNIGFMNGCGFBHISSMVWTL";

    // setup for column freqs methods
    vector<char> column1 = {'A', 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'B'};
    vector<char> column2 = {'C', 'C', 'C', 'C', 'C', 'D', 'D', 'D', 'D', 'D'};


    SECTION("actually gets default constructed") {
        REQUIRE(vig_dec != nullptr);
    }

    SECTION("getAllNgramsWithLength", "[vigenere-decipherer]") {

        auto n_grams3 = vig_dec->getAllNgramsWithLength(test_ciphertext, 3);
        REQUIRE(n_grams3.size() == 18); // 18 valid substrings of length 3
        auto n_grams6 = vig_dec->getAllNgramsWithLength(test_ciphertext, 6);
        REQUIRE(n_grams6.size() == 15); // 15 valid substrings of length 6
    }

    SECTION("removeNgramsBelowOccurrenceThreshold", "[vigenere-decipherer]") {

        vig_dec->removeNgramsBelowOccurrenceThreshold(remove_ngrams, threshold);

        VigenereDecipherer::um_str_vec_t::iterator it = remove_ngrams.begin();
        while (it != remove_ngrams.end())
        {
            if (it->second.size() < threshold) {
                remove_ngrams.erase(it++);
            }
            else ++it;
        }
        REQUIRE(remove_ngrams.size() == 2);
    }

    SECTION("searchForRecurringNgramsWithLength", "[vigenere-decipherer]") {

        auto search3 = vig_dec->searchForRecurringNgramsWithLength(test_ciphertext_long,3);
        REQUIRE(search3.size() == 18);
        auto search5 = vig_dec->searchForRecurringNgramsWithLength(test_ciphertext_long,5);
        REQUIRE(search5.size() == 16);
    }

    SECTION("getKeyLength", "[vigenere-decipherer]") {
        vector<int> x{33, 66, 99};     // 33
        vector<int> y{10, 15, 25, 30}; // 5
        vector<int> z{15, 20, 25, 30}; // 5
        vector<int> t{18, 30, 48, 54}; // 6
        vector<int> c{18, 30, 48, 54}; // 6
        vector<int> v{18, 30, 48, 54}; // 6
        vector<int> q{0, 49, 56, 63};  // 7

        vector<vector<int>> occurrences;
        occurrences.emplace_back(x);
        occurrences.emplace_back(y);
        occurrences.emplace_back(z);
        occurrences.emplace_back(t);
        occurrences.emplace_back(c);
        occurrences.emplace_back(v);
        occurrences.emplace_back(q);

        REQUIRE(vig_dec->getKeyLength(occurrences) == 6);
    }

    /**
     * Columnise the ciphertext into 'key_length' quantity of vectors
     * Each char in each column has been enciphered using the same key letter
     */
    SECTION("columniseCipherText", "[vigenere-decipherer]") {

        auto columnise = vig_dec->columniseCipherText(test_ciphertext_long, 6);
        REQUIRE(columnise.size() == 6);
        REQUIRE(columnise[0].size() == 10);
    }

    /**
     * Get the relative frequencies of a vector of characters
     */
    SECTION("getColumnCharRelativeFreqs", "[vigenere-decipherer]") {

        auto counts = vig_dec->getColumnCharRelativeFreqs(column1);
        REQUIRE(counts[0] == 0.5);
        REQUIRE(counts[1] == 0.5);
    }

    /**
     * Get the relative frequencies of several vectors of characters
     */
    SECTION("getAllCharRelativeFreqs", "[vigenere-decipherer]") {

        vector<vector<char>> columns{column1, column2};
        auto counts = vig_dec->getAllCharRelativeFreqs(columns);
        REQUIRE(counts[0][0] == 0.5);
        REQUIRE(counts[0][1] == 0.5);
        REQUIRE(counts[1][2] == 0.5);
        REQUIRE(counts[1][3] == 0.5);
    }



    delete(vig_dec);
}



