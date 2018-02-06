#include <memory>

#include "include/Lib1/Vigenere.h"

using std::make_unique;

/*
 * Test
 */
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <iostream>

using std::map;
using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;


static const int FROM = 3;
static const int TO = 6;

// count greatest common divisor of 2 numbers
int gcd(int u, int v)
{
    if (v) return gcd(v, u % v);
    else return u < 0 ? -u : u;
}

int multi_gcd(vector<int> & num)
{
    if      (num.size() == 0) return 0;
    else if (num.size() == 1) return num[0];
    else if (num.size() == 2) return gcd(num[0], num[1]);

    num[1] = gcd(num[0], num[1]);
    num.erase(num.begin());
    return multi_gcd(num);
}

// find all n-grams (FROM-grams ... TO-grams) in linear time (!)
void find_ngrams(string & str, map<string, vector<int> > & tgs, int from, int to)
{
    int length = str.length();
    for (int i = 0; i < length; ++i)
    {
        // from each position in str count all n-grams (if possible)
        for (int j = from; j <= to; ++j)
        {
            if (i+j > length) continue;
            string sub = str.substr(i, j);
            tgs[sub].push_back(i);
        }
    }

    // ignore those n-grams which are irrelevant due to insufficient
    // number of occurrences
    map<string, vector<int> >::iterator rem = tgs.begin();
    while (rem != tgs.end())
    {
        if (rem->second.size() < 3) tgs.erase(rem++);
        else ++rem;
    }

    for(map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
    {
        int size = it->second.size();

        // count differences between occurences
        for (int i = size - 1; i > 0; --i)
            it->second[i] -= it->second[i-1];
        it->second.erase(it->second.begin());

        // count GCD for the n-grams
        int mgcd = multi_gcd(it->second);

        // save {"n-gram": [gcd, freq]}
        it->second.clear();
        it->second.push_back(mgcd);
        it->second.push_back(size);
    }
}





int main() {


    auto vig_entry = make_unique<Vigenere>();
    vig_entry->Start();

    /*
    string ciph = "NIGFMNGCGFBHISSMVWTLPFMJFUVSMSUSQFFUIFZWYSAQDJTWFVUVSWADHCSABBRFKJFSGGSQCOKVADUAPBOOVGCFPJESFHSUVSSAOUOMDFLONHMSGPXFOQIUMOGTAGWQBLJCBPXBTWFDECTLFPKZFVHSTPJSSGFSSQVBFETCSVJGDMSZKOTLISDVJQCGFSTOAFJJQOOUPZZFYFGUSWXWBUZFQSOLVFMUZFMRFNFZCQWEHVFASCKOFBHISSMVWTLPFMDGMZSDLJCBTXPFHIWVGSPXUVSJJTHIEWOHGCQUVSMSTHEVSSHSSGGHVFUFBHVJZHVFKDWSOLJTWDJFGSBJDVWOLISIOAWSFTAUWSTOBGGIAGHWOYUCKBJEPWPDPUWDSMFSTWBFQIGOOQFDMIZBJMSJFDBBRDMUHWOYFRUFJFGSBJDVAPNFRTSGNAITWVAGUGVBWWWSGWUQMOPPJBHCSAFGKIAMSABFZZOSYFAITWVAGTMDVOTLISGNAUVGPFJOBJFTHWUMUWCOSSSGUAMZFFKQSQUWEOGSWTSOSUIQSOLFFGSWTSOSUIWGOGMCBHWSOABAODISHPGSPXNCGUEVGSVETKVJDFHVFJFWGBFPBUPAOURFTBHSBTPIHUZFDISHPGSTGGWBUWSDFFLBHWPFPTONMTSINKDCZMWDHWPFUVSSWIOGCWFBODGOGWTLFBHNATGWPFUCDSGUSQUSORDSWTSFWWBFHJXBQHTXPFTVLVFSHWOSFBLJCBTEVQVDSSSSYHFFHJKFOBEWYDSOKFWGJFWSGUWEWBQJFGSSNBHWPFFTTPJUGHPJFHOSVESQPEQCGJLJCBJFBUWOYECQVEFBHTSSHWGSDHGBJUKCSCTOBETVWZEAOUGBDMAITWVAGEATDZBQPPXFUUGHISUOFFANDCSLBBHUGBQIMLVFSBKIWGUGSWOOKUSJFFDCBOOSWHFKUCGFWUVSUZJBUJLTSZGOJHVPFFGCXFFMSTSORWOSQIPMADDZBUFGISJPIBEWEPMPLISFQWPDZFZBJWOYTCAFNFFGJGOCTUZFGONWFLDFJJSBDWDOBCWFBQISOHWOY";
    map<string, vector<int>> tgs;
    find_ngrams(ciph, tgs, 3, 7);
    */

    return 0;
}