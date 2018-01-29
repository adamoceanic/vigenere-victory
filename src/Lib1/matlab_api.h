#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using std::ios;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;

/*
 * Until I can figure out the matlab-c++ MEX situation this class implements two methods of obtaining the
 * ciphertext from matlab. The ofstream/sstream version is no doubt better but I wanted an excuse to try
 * popen with a bash script.
 *
 */
class Input;

class MatlabAPI {
private:
    Input& input_parent_;

public:
    void operator()() {
        input_parent_.SetHasCiphertext(false);
        string res;

        while(true) {
            WaitSeconds(2);
            if (input_parent_.GetListeningStatus_Matlab()) {
                res = GetCiphertextTxt();

                if (res != "ERROR") {
                    input_parent_.SetCiphertext(std::move(res));
                    input_parent_.SetHasCiphertext(true);
                    ResetCipherText();
                }
            }
        }
    }

    void WaitSeconds(int i) {
        std::this_thread::sleep_for(std::chrono::seconds(i));
    }

    string GetCiphertextBash() {
        const char* script_path = "../matlab-script/matlab_get_string.sh\0"; // relative links suck - think of better way for travis
        FILE* pipe = popen(script_path, "r");
        if (!pipe) {
            return "ERROR";
        }
        char buffer[128];        // Make this value a variable
        string result = "";
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != nullptr) {
                result += buffer;
            }
        }
        pclose(pipe);
        return result == "X\n" ? "ERROR" : result;
    }

    string GetCiphertextTxt() {
        ifstream file;
        file.exceptions( ifstream::failbit | ifstream::badbit);
        try {
            file.open("../matlab-script/ciphertext.txt",
                          ios::in | ios::binary);

            stringstream ciphertext_buffer;
            ciphertext_buffer << file.rdbuf();
            file.close();
            return ciphertext_buffer.str();
        }
        catch (const ifstream::failure& e) {
            file.close();
            return "ERROR";
        }
    }

    void ResetCipherText() {
        ofstream file;
        file.exceptions( ifstream::failbit | ifstream::badbit);
        try {
            file.open("../matlab-script/ciphertext.txt",
                      ios::out | ios::binary);

            file << "ERROR";
            file.close();
        }
        catch (const ofstream::failure& e) {
            file.close();
        }
    }

    // ctor, move ctor, dtor
    explicit MatlabAPI(Input& i) : input_parent_{i} {};
    MatlabAPI(MatlabAPI&& rhs) noexcept : input_parent_{rhs.input_parent_} {}
    ~MatlabAPI() = default;

    // Deleted ctors/opters
    MatlabAPI(const MatlabAPI&) = delete;
    MatlabAPI& operator=(const MatlabAPI&) = delete;
    MatlabAPI& operator=(const MatlabAPI&&) = delete;
};
