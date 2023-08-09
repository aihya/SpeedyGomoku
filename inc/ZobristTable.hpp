
#include <vector>
#include <random>

class ZobristTable {
    public:
    
        ZobristTable(int size, int side_num) : table(side_num, std::vector<uint64_t>(size)) {
            std::random_device rend_dev;
            std::mt19937_64 gen(rend_dev());

            std::uniform_int_distribution<uint64_t> distr;
            for (int i = 0; i < side_num; i++)
                for (int j = 0; j < size; j++)
                    table[i][j] = distr(gen);
        }
        uint64_t get(size_t side, size_t position) const {
            return table[side][position];
        }
    private:
        std::vector<std::vector<uint64_t>> table;
};