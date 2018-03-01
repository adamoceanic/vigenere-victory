#include "catch.h"

#include "src/Lib1/VigenereDecipherer.h"

TEST_CASE("VigenereDecipher class basics", "[vigenere-decipherer]") {
    // ========================================
    // Setup
    auto vig_dec = new VigenereDecipherer();

    // setup for getAllNgramsWithLength()
    um_str_vec_t all_ngrams;
    string test_ciphertext = "NIGFMNGCGFBHISSMVWTL";

    // setup for removeNgramsBelowOccurrenceThreshold()
    um_str_vec_t remove_ngrams;
    int threshold = 3;
    vector<int> count = {1,2,3};
    vector<int> count2 = {1,2};
    vector<int> count3 = {1,2,3,4};
    remove_ngrams.insert({"TEST", count});
    remove_ngrams.insert({"TEST2", count2});
    remove_ngrams.insert({"TEST3", count3});

    // setup for searchForRecurringNgramsWithLength()
    um_str_vec_t search_ngrams;
    string test_ciphertext_long = "NIGFMNGCGFBHISSMVWTLNIGFMNGCGFBHISSMVWTLNIGFMNGCGFBHISSMVWTL";


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

        um_str_vec_t::iterator it = remove_ngrams.begin();
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

    delete(vig_dec);
}



