#include "include/Lib1/Input.h"

bool Input::HasCiphertext() {
    return has_ciphertext;
}

string Input::GetCiphertext(){
    return matlab_ciphertext;
}

Input::Input() : matlab_{ make_unique<MatlabAPI>() } {
}

void Input::Start() {
    /*
     * thread for querying matlab etc
     * dont forget mutex and lock_guard layout
     * matlab_.GetCiphertext
     *
     * if yes put into matlab_ciphertext
     * set has ciphertext to true
     */
}
Input::~Input() = default;
