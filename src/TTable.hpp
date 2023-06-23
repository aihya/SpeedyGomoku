#include <unordered_map>
#include <utility>

class TTable {

    public:
        typedef enum s_bound{
            ERROR,
            EXACT,
            LOWER_BOUND,
            UPPER_BOUND
        }              t_bound;
        typedef struct s_TTEntry {
            int                 depth;
            std::pair<int, int> best_move;
            int64_t             value;
            t_bound             type;
        }               t_TTEntry;

        void add_entry(uint64_t zobrist, int depth, std::pair<int, int> best_move, int64_t value, t_bound type) {
            table[zobrist] = {depth, best_move, value, type};
        }

        t_TTEntry get_entry(uint64_t zobrist) {
            auto it = table.find(zobrist);
            if (it == table.end()) {
                return {-1, {-1, -1}, -1, TTable::ERROR};
            }
            return it->second;
        }
    private:
        std::unordered_map<uint64_t, s_TTEntry> table;
};