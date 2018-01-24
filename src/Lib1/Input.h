#pragma once
/*
 * Manage the MATLAB api and wait for input strings
 */
#include <memory>
#include <string>

#include "src/Lib1/matlab_api.h"

using std::string;
using std::unique_ptr;
using std::make_unique;

class Input {
private:
    bool has_ciphertext;
    string matlab_ciphertext;
public:
    bool HasCiphertext();
    string GetCiphertext();
    void Start();

    Input();
    ~Input();
    Input(const Input&) = delete;
    Input&operator=(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;
};
