#include "src/Lib1/VigenereDecipherer.h"

#include <thread>
#include <future>
#include <array>
#include <vector>


VigenereDecipherer::results_info_pair_t VigenereDecipherer::Decipher(string cipher_text) {

    string plain_text;
    unordered_map<string, int> info;
    std::array<int,4> key_lengths = { 3, 4, 5, 6};

    std::vector<std::future<unordered_map<string, int>>> futures;
    for (auto& kl : key_lengths) {

        futures.emplace_back(std::async(searchForRepeatingSubstrings, cipher_text, kl));
    }
    for (auto& fut : futures) {
        fut.get();
    }


    auto result = make_pair(plain_text,info);

    return result;
}

unordered_map<string, int> VigenereDecipherer::searchForRepeatingSubstrings(string cipher_text, int key_length) {


}
