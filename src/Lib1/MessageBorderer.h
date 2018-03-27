#pragma once

#include <iomanip>

struct MessageBorderer {

    static const int message_width_ = 64;
    static const char fill_char_top_ = '=';
    static const char fill_char_edges_ = '*';

    MessageBorderer() = default;
    ~MessageBorderer() = default;

    static void print(std::vector<string> message) {
        std::cout << std::setfill(fill_char_top_) << std::setw(message_width_) << fill_char_top_ << '\n';
        for (auto& line : message) {
            std::cout << fill_char_edges_ << std::left << std::setfill(' ')
                 << std::setw(message_width_ - 2) << line << fill_char_edges_<< '\n';
        }
        std::cout << std::setfill(fill_char_top_) << std::setw(message_width_) << fill_char_top_ << '\n';
    }
};