#include <unordered_map>

class TTable {
    private:
        typedef struct s_TTEntry {
            int value;
            int depth;
            char type;
        }               t_TTEntry;
        std::unordered_map<uint64_t, t_TTEntry> table;

    public:
        TTable(int size) : table(size) {}

        int get(uint64_t zobrist) {
            auto it = table.find(zobrist);
            if (it == table.end()) {
                return -1;
            }
            return it->second.value;
        }

        void put(uint64_t zobrist, int value, int depth, char type) {
            table[zobrist] = {value, depth, type};
        }
};