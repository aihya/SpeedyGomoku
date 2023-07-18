
#include <vector>
#include <random>

class ZobristTable {
    public:
    
        ZobristTable(int size, int side_num) : table(side_num, std::vector<uint64_t>(size)) {
            std::random_device rend_dev;     //Get a random seed from the OS entropy device, or whatever
            std::mt19937_64 gen(rend_dev()); //Use the 64-bit Mersenne Twister 19937 generator
                                            //and seed it with entropy.

            // Define the distribution, by default it goes from 0 to MAX(unsigned long long)
            // or what have you.
            std::uniform_int_distribution<uint64_t> distr;
            for (int i = 0; i < side_num; i++)
                for (int j = 0; j < size; j++)
                    table[i][j] = distr(gen);
        }
        uint64_t get(int square, char piece) const {
            return table[square][piece];
        }
    private:
        std::vector<std::vector<uint64_t>> table;
};