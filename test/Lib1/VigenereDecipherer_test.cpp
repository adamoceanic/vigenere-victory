#include "catch.h"

#include "src/Lib1/VigenereDecipherer.h"

TEST_CASE("VigenereDecipher class basics", "[vigenere-decipherer]") {
    auto vig_dec = new VigenereDecipherer();
    um_str_vec_t all_ngrams;
    vector<int> count = {1,2,3};
    vector<int> count2 = {1,2};
    vector<int> count3 = {1,2,3,4};
    int threshold = 3;
    all_ngrams.insert({"TEST", count});
    all_ngrams.insert({"TEST2", count2});
    all_ngrams.insert({"TEST3", count3});

    SECTION("actually gets default constructed") {
        REQUIRE(vig_dec != nullptr);
    }

    SECTION("getAllNgramsWithLength", "[vigenere-decipherer]") {

    }

    SECTION("searchForRecurringNgramsWithLength", "[vigenere-decipherer]") {

    }

    SECTION("removeNgramsBelowOccurrenceThreshold", "[vigenere-decipherer]") {

        vig_dec->removeNgramsBelowOccurrenceThreshold(all_ngrams, threshold);

        um_str_vec_t::iterator it = all_ngrams.begin();
        while (it != all_ngrams.end())
        {
            if (it->second.size() < threshold) {
                all_ngrams.erase(it++);
            }
            else ++it;
        }
        REQUIRE(all_ngrams.size() == 2);
    }

    delete(vig_dec);
}



