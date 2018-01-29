#include "src/Lib1/Input.h"

#include "matlab_api.h"
//#include "ScopedThreadGuard.h"

using std::thread;
using std::lock_guard;

/*
 * Could probably use atomic<bool> instead of these heavy mutexs
 */

// ===================================================
// PRIVATE MEMBER FUNCS

void Input::StopListening_Matlab() {
    lock_guard<mutex> lg{this->m_l_f_mux_};
    matlab_listening_flag_ = false;
}

void Input::StartListening_Matlab() {
    lock_guard<mutex> lg{this->m_l_f_mux_};
    matlab_listening_flag_ = true;
}

// ===================================================

// ===================================================
// PUBLIC MEMBER FUNCS

bool Input::HasCiphertext() const {
    lock_guard<mutex> lg{this->h_c_mux_};
    return has_ciphertext_;
}

void Input::SetHasCiphertext(bool t_f) {
    lock_guard<mutex> lg{this->h_c_mux_};
    has_ciphertext_ = t_f;
    if (!t_f) {
        StartListening_Matlab();
    }
}

string Input::GetCiphertext() const {
    lock_guard<mutex> lg{this->m_c_mux_};
    return matlab_ciphertext_;
}

void Input::SetCiphertext(string&& c_text) {
    lock_guard<mutex> lg{this->m_c_mux_};
    matlab_ciphertext_ = std::move(c_text);

    StopListening_Matlab();
}

void Input::Start() {

    MatlabAPI m_api(*this);
    //auto matlab_thread = make_unique<ScopedThreadGuard>(
            //thread();
    thread matlab_thread(std::move(m_api));
    matlab_thread.detach();
}

bool Input::GetListeningStatus_Matlab() const {
    lock_guard<mutex> lg{this->m_l_f_mux_};
    return matlab_listening_flag_;
}

// ===================================================

// ===================================================
// CTORS DTORS OPTORS

Input::Input() : has_ciphertext_{false}, matlab_listening_flag_{true} {
    matlab_ciphertext_ = "";
}

Input::~Input() = default;
