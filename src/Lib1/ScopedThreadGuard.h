#pragma once
/*
 * Manages the lifetime of the thread and ensures it is joined
 */

class ScopedThreadGuard {
    std::thread t_;
public:
    explicit ScopedThreadGuard(std::thread t) : t_(std::move(t)) {

        if (!t_.joinable()) {
            throw std::logic_error("No thread");
        }
    }
    ~ScopedThreadGuard() {
        t_.join();
        std::cout << "Scoped guard destroyed and thread joined" << std::endl;
    }
    ScopedThreadGuard(const ScopedThreadGuard& )= delete;
    ScopedThreadGuard& operator=(const ScopedThreadGuard&)= delete;
    ScopedThreadGuard(const ScopedThreadGuard&& )= delete;
    ScopedThreadGuard& operator=(const ScopedThreadGuard&&)= delete;
};