#pragma once

#include <memory>
#include <string>
#include <thread>
#include <mutex>

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::mutex;

class Input {
private:
    mutable mutex m_c_mux_;
    mutable mutex m_l_f_mux_;
    mutable mutex h_c_mux_;

    bool has_ciphertext_;
    bool matlab_listening_flag_;
    string matlab_ciphertext_;

    void StopListening_Matlab();
    void StartListening_Matlab();

public:
    bool HasCiphertext() const;
    void SetHasCiphertext(bool t_f);

    string GetCiphertext() const;
    void SetCiphertext(string&& c_text);
    bool GetListeningStatus_Matlab() const;

    void Start();

    Input();
    ~Input();
    Input(const Input&) = delete;
    Input&operator=(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;
};
