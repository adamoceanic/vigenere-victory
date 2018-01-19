#include "Vigenere_Impl.h"

#include <memory>

#include "include/Lib1/Input.h"
#include "include/Lib1/VigenereDecipherer.h"

using std::make_unique;

void Vigenere_Impl::Start() {
    /*
     * // Start thread listening for Matlab inputs:
     * input_manager->Start()
     *
     * while(true)
     * // Wait x amount etc
     * this_thread::sleep_for(chrono::seconds(2))
     * // check if ciphertext
     * i_m.HasCiphertext()
     *
     * x = i_m.GetCiphertext()
     *
     * // Decipher
     * x = v_d_.Decipher(x)
     *
     * // decide on further processing etc needed via return data vars
     * best_guess_dictionary.Process(x)
     *
     * // print results - later: pass back to ar unit /webcam
     *
     */

}

Vigenere_Impl::Vigenere_Impl()
        : input_manager_{ make_unique<Input>() },
          v_d_{ make_unique<VigenereDecipherer>() } {

}



Vigenere_Impl::~Vigenere_Impl() = default;