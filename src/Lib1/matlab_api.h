#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <cstdio>

using std::ios;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::shared_ptr;
using std::array;

/*
 * Until I can figure out the matlab-c++ MEX situation this class implements two methods of obtaining the
 * ciphertext from matlab. The ofstream/sstream version is no doubt better but I wanted an excuse to try
 * popen with a bash script.
 *
 */
class Input;

namespace Matlab {

    class MatlabAPI {
    private:
        Input& input_parent_;
        string file_path_txt_ = {"../matlab-script/ciphertext.txt"};
        const char* bash_file_path = "../matlab-script/matlab_get_string.sh\0";
        int buffer_size_ = 256;

    public:
        void operator()() {
            input_parent_.SetHasCiphertext(false);
            string res;

            while (true) {
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

            array<char, 512> buffer;
            string result;
            shared_ptr<FILE> pipe(popen(bash_file_path, "r"), pclose);
            if (!pipe) { throw std::runtime_error("popen() failed!"); }
            while (!feof(pipe.get())) {
               if (fgets(buffer.data(), 512, pipe.get()) != nullptr)
                   result += buffer.data();
                }
            return result == "X\n" ? "ERROR" : result;
        }

        string GetCiphertextTxt() {

            ifstream file;
            file.exceptions(ifstream::failbit | ifstream::badbit);
            try {
                file.open(file_path_txt_, ios::in | ios::binary);
                stringstream ciphertext_buffer;
                ciphertext_buffer << file.rdbuf();
                file.close();
                return ciphertext_buffer.str();
            }
            catch (const ifstream::failure &e) {
                file.close();
                return "ERROR";
            }
        }

        void ResetCipherText() {

            ofstream file;
            file.exceptions(ifstream::failbit | ifstream::badbit);
            try {
                file.open(file_path_txt_, ios::out | ios::binary);
                file << "ERROR";
                file.close();
            }
            catch (const ofstream::failure &e) {
                file.close();
            }
        }

        // ctor, move ctor, dtor
        explicit MatlabAPI(Input &i) : input_parent_{i} {};

        MatlabAPI(MatlabAPI &&rhs) noexcept
                : input_parent_{rhs.input_parent_},
                  file_path_txt_{rhs.file_path_txt_},
                  buffer_size_{rhs.buffer_size_} {}

        ~MatlabAPI() = default;

        // Deleted ctors/opters
        MatlabAPI(const MatlabAPI &) = delete;

        MatlabAPI &operator=(const MatlabAPI &) = delete;

        MatlabAPI &operator=(const MatlabAPI &&) = delete;
    };

}
