#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <cstdint>
#include <array>

class ZobristTable {
public:
    ZobristTable(std::size_t size, std::size_t side_num) 
        : table(side_num, std::vector<uint64_t>(size)) {
        std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist;

        for (auto& side : table) {
            for (auto& hash : side) {
                hash = dist(rng);
            }
        }
    }

    [[nodiscard]] uint64_t get(std::size_t square, unsigned char piece) const {
        return table[square][piece];
    }

    void put(std::size_t square, unsigned char piece, uint64_t hash) {
        table[square][piece] = hash;
    }

    void copy(const ZobristTable& other) {
        table = other.table;
    }

private:
    std::vector<std::vector<uint64_t>> table;
};