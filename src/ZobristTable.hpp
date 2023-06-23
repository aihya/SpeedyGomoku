
#include <vector>

class ZobristTable {
    public:
        ZobristTable(int size, int side_num) : table(side_num, std::vector<uint64_t>(size)) {
            std::srand(std::time(0));
            for (int i = 0; i < side_num; i++)
                for (int j = 0; j < size; j++)
                    table[i][j] = rand();
        }
        uint64_t get(int square, char piece) const {
            return table[square][piece];
        }
    
        void put(int square, char piece, uint64_t hash) {
            table[square][piece] = hash;
        }
        void copy(const ZobristTable& other){
            for (int i = 0; i < table.size(); i++)
                for (int j = 0; j < table[i].size(); j++)
                    table[i][j] = other.get(i, j);
        }
    
    private:
        std::vector<std::vector<uint64_t>> table;
};