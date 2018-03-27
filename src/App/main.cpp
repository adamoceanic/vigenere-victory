#include <memory>

#include "include/Lib1/Vigenere.h"

using std::make_unique;

/*
// fun template
template <typename T>
vector<T> operator-(const vector<T>& a, const vector<T>& b)
{
    //assert(a.size() == b.size());

    vector<T> result;
    result.reserve(a.size());

    transform(a.begin(), a.end(), b.begin(),
              back_inserter(result), std::minus<T>());
    return result;
}
*/


int main(int argc, char ** argv) {

    auto vig_entry = make_unique<Vigenere>();

    if (argv[1] == "--matlab") {
        vig_entry->Start(argv[1]);
    }
    else {
        vig_entry->Start("--desktop");
    }

    return 0;
}