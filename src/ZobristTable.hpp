
#include <vector>

class ZobristTable {
    public:
        ZobristTable(int size, int side_num) : table(side_num, std::vector<uint64_t>(size)) {
            for (int i = 0; i < side_num; i++) {
                for (int j = 0; j < size; j++) {
                    table[i][j] = rand();
                }
            }
        }
        uint64_t get(int square, char piece) {
            return table[square][piece];
        }
    
        void put(int square, char piece, uint64_t hash) {
            table[square][piece] = hash;
        }
    
    private:
        std::vector<std::vector<uint64_t>> table;
};