#include "src/Lib1/Input.h"

#include <thread>
#include <iostream>

#include "ScopedThreadGuard.h"

using std::thread;
using std::cout;
using std::endl;
using std::cin;

bool Input::HasCiphertext() {
    return has_ciphertext;
}

string Input::GetCiphertext(){
    return matlab_ciphertext;
}

Input::Input() {

    has_ciphertext = false;
    matlab_ciphertext = "";
}

void Input::Start() {

    cout << "Input starting" << endl;

    MatlabAPI m_api;
    auto matlab_thread = make_unique<ScopedThreadGuard>(
            thread(std::move(m_api), std::ref(matlab_ciphertext), std::ref(has_ciphertext)));

    while (!has_ciphertext) {
        cout << "inside input.start() while loop" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        cout << matlab_ciphertext << endl;
    }
}

Input::~Input() = default;
