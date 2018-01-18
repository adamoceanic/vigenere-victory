#include "../inc/Input.h"
#include "Input_Impl.h"



bool Input::HasInput() {
    return pImpl->HasInput();
}


int Input::GetTestData() {
    return pImpl->GetTestData();
}

string Input::GetInput() {
    return pImpl->GetInput();
}

Input::Input() : pImpl{make_unique<Input_Impl>()} {

}

Input::~Input() = default;
