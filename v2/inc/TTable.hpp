#pragma once

#include <unordered_map>
#include <utility>
#include <mutex>
#include <cstdint>

class TTable {
public:
    enum class Bound {
        ERROR,
        EXACT,
        LOWER_BOUND,
        UPPER_BOUND
    };
    typedef Bound t_bound;

    struct TTEntry {
        int depth;
        std::pair<int, int> best_move;
        int64_t score;
        Bound bound;
    };
    typedef TTEntry t_TTEntry;

    explicit TTable(size_t size = 1000000) : table(size) {}

    void add_entry(uint64_t zobrist, int depth, std::pair<int, int> best_move, int64_t value, Bound bound) {
        std::lock_guard<std::mutex> lock(mutex);
        table[zobrist] = {depth, best_move, value, bound};
    }

    [[nodiscard]] TTEntry get_entry(uint64_t zobrist) const {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = table.find(zobrist);
        if (it == table.end()) {
            return {-1, {-1, -1}, -1, Bound::ERROR};
        }
        return it->second;
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex);
        table.clear();
    }

    [[nodiscard]] size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return table.size();
    }

private:
    mutable std::mutex mutex;
    std::unordered_map<uint64_t, TTEntry> table;
};