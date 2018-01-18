#pragma once
/*
 * Manage the MATLAB api and wait for input strings
 */

#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::make_unique;

class Input_Impl;

class Input {
private:
    unique_ptr<Input_Impl> pImpl;
public:
    bool HasInput();
    string GetInput();
    int GetTestData();

    Input();
    ~Input();
    Input(const Input&) = delete;
    Input&operator=(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;
};
