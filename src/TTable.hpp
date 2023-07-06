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
            int64_t             score;
            int                 piece;
            uint64_t            hash;
            t_bound             bound;
        }               t_TTEntry;

        void add_entry(uint64_t zobrist, int depth, std::pair<int, int> best_move, int64_t value, int piece, t_bound bound) {
            table[zobrist % size] = {depth, best_move, value, piece, zobrist,bound};
        }

        t_TTEntry get_entry(uint64_t zobrist) {
            return table[zobrist % size];
        }
        TTable(size_t size_in_mb) {
            size = size_in_mb * 1024 * 1024 / sizeof(s_TTEntry);
            table = new t_TTEntry[size];
            for (size_t i = 0; i < size; i++)
                table[i] = {0, {0, 0}, 0, 0, ERROR};
        }
        ~TTable() {
            delete[] table;
        }
    private:
        t_TTEntry *table;
        size_t    size;
};