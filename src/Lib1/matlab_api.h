#pragma once

#include <string>

using std::string;

class MatlabAPI {
public:
    string GetCiphertext() {
        const char* script_path = "/home/sapho/portfolio-work/vigenere-victory/matlab-script/matlab_get_string.sh\0";
        FILE* pipe = popen(script_path, "r");
        if (!pipe) {
            return "ERROR";
        }
        char buffer[128];        // Make this value a variable
        std::string result = "";
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != nullptr) {
                result += buffer;
            }
        }
        pclose(pipe);
        return result == "X\n" ? "ERROR" : result;
    }

    MatlabAPI() = default;
    ~MatlabAPI() = default;
    MatlabAPI(const MatlabAPI&) = delete;
    MatlabAPI& operator=(const MatlabAPI&) = delete;
    MatlabAPI(MatlabAPI&&) = delete;
    MatlabAPI& operator=(MatlabAPI&&) = delete;
};