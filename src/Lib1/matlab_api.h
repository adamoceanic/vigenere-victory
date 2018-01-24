#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using std::ios;
using std::ifstream;
using std::string;
using std::stringstream;

/*
 * Until I can figure out the matlab-c++ MEX situation this class implements two methods of obtaining the
 * ciphertext from matlab. The ofstream/sstream version is no doubt better but I wanted an excuse to try
 * popen with a bash script.
 *
 */

class MatlabAPI {
public:
    void operator()(string& input_ciphertext, bool& has_ciphertext) {

        bool listen_flag = true;
        has_ciphertext = false;
        string res = "";

        while(listen_flag) {
            res = GetCiphertextBash();

            if (res != "ERROR") {
                listen_flag = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        input_ciphertext = res;
        has_ciphertext = true;
    }

    string GetCiphertextBash() {
        const char* script_path = "/home/sapho/portfolio-work/vigenere-victory/matlab-script/matlab_get_string.sh\0";
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
            file.open("/home/sapho/portfolio-work/vigenere-victory/matlab-script/ciphertext.txt",
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

    MatlabAPI()= default;
    ~MatlabAPI() = default;
    MatlabAPI(const MatlabAPI&) = delete;
    MatlabAPI& operator=(const MatlabAPI&) = delete;
    MatlabAPI(MatlabAPI&&) = default;
    MatlabAPI& operator=(const MatlabAPI&&) = delete;
};
