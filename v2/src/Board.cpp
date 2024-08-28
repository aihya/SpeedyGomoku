#include "Board.hpp"
#include <iostream>

const t_patterns Board::_attack_patterns = {
    {
        BLACK, {
            {0b010101010100, FIVE_SCORE},
            {0b010101010110, FIVE_SCORE},
            {0b010101010111, FIVE_SCORE},
            {0b000101010101, FIVE_SCORE},
            {0b100101010101, FIVE_SCORE},
            {0b110101010101, FIVE_SCORE},

            {0b000101010100, OPEN_FOUR_SCORE},
            {0b110101010100, FOUR_SCORE},
            {0b100101010100, FOUR_SCORE},
            {0b000101010111, FOUR_SCORE},
            {0b000101010110, FOUR_SCORE},
            {0b000101010000, OPEN_THREE_SCORE},
            {0b000101010011, OPEN_THREE_SCORE},
            {0b000101010010, OPEN_THREE_SCORE},
            {0b000101010001, OPEN_THREE_SCORE},
            {0b000001010100, OPEN_THREE_SCORE},
            {0b110001010100, OPEN_THREE_SCORE},
            {0b100001010100, OPEN_THREE_SCORE},
            {0b010001010100, OPEN_THREE_SCORE},
            {0b000100010100, OPEN_THREE_SCORE},
            {0b000101000100, OPEN_THREE_SCORE},
            {0b000001010110, THREE_SCORE},
            {0b000001010111, THREE_SCORE},
            {0b100101010000, THREE_SCORE},
            {0b110101010000, THREE_SCORE},
            {0b000101000000, OPEN_TWO_SCORE},
            {0b000101000010, OPEN_TWO_SCORE},
            {0b000101000011, OPEN_TWO_SCORE},
            {0b000001010000, OPEN_TWO_SCORE},
            {0b000001010010, OPEN_TWO_SCORE},
            {0b000001010011, OPEN_TWO_SCORE},
            {0b000001010000, OPEN_TWO_SCORE},
            {0b100001010000, OPEN_TWO_SCORE},
            {0b110001010000, OPEN_TWO_SCORE},
            {0b000000010100, OPEN_TWO_SCORE},
            {0b100000010100, OPEN_TWO_SCORE},
            {0b110000010100, OPEN_TWO_SCORE},
            {0b000000010111, TWO_SCORE},
            {0b000001000110, TWO_SCORE},
            {0b100100010000, TWO_SCORE},
            {0b110101000000, TWO_SCORE},
        }
    },
    {
        WHITE, {
            {0b101010101000, FIVE_SCORE},
            {0b101010101001, FIVE_SCORE},
            {0b101010101011, FIVE_SCORE},
            {0b001010101010, FIVE_SCORE},
            {0b011010101010, FIVE_SCORE},
            {0b111010101010, FIVE_SCORE},
            {0b001010101000, OPEN_FOUR_SCORE},
            {0b111010101000, FOUR_SCORE},
            {0b011010101000, FOUR_SCORE},
            {0b001010101011, FOUR_SCORE},
            {0b001010101001, FOUR_SCORE},
            {0b001010100000, OPEN_THREE_SCORE},
            {0b001010100011, OPEN_THREE_SCORE},
            {0b001010100001, OPEN_THREE_SCORE},
            {0b001010100010, OPEN_THREE_SCORE},
            {0b000010101000, OPEN_THREE_SCORE},
            {0b110010101000, OPEN_THREE_SCORE},
            {0b010010101000, OPEN_THREE_SCORE},
            {0b100010101000, OPEN_THREE_SCORE},
            {0b001000101000, OPEN_THREE_SCORE},
            {0b001010001000, OPEN_THREE_SCORE},
            {0b000010101001, THREE_SCORE},
            {0b000010101011, THREE_SCORE},
            {0b011010100000, THREE_SCORE},
            {0b111010100000, THREE_SCORE},
            {0b001010000000, OPEN_TWO_SCORE},
            {0b001010000001, OPEN_TWO_SCORE},
            {0b001010000011, OPEN_TWO_SCORE},
            {0b000010100000, OPEN_TWO_SCORE},
            {0b000010100001, OPEN_TWO_SCORE},
            {0b000010100011, OPEN_TWO_SCORE},
            {0b000010100000, OPEN_TWO_SCORE},
            {0b010010100000, OPEN_TWO_SCORE},
            {0b110010100000, OPEN_TWO_SCORE},
            {0b000000101000, OPEN_TWO_SCORE},
            {0b010000101000, OPEN_TWO_SCORE},
            {0b110000101000, OPEN_TWO_SCORE},
            {0b000010001001, TWO_SCORE},
            {0b000000101011, TWO_SCORE},
            {0b0110001000000, TWO_SCORE},
            {0b111010000000, TWO_SCORE},
        },
    }
};

const t_patterns _illegal_patterns
{
    {
        BLACK, {
            {0b000101010000, ILLEGAL_SCORE},
            {0b000101010011, ILLEGAL_SCORE},
            {0b000101010010, ILLEGAL_SCORE},
            {0b000101010001, ILLEGAL_SCORE},
            {0b000001010100, ILLEGAL_SCORE},
            {0b110001010100, ILLEGAL_SCORE},
            {0b100001010100, ILLEGAL_SCORE},
            {0b010001010100, ILLEGAL_SCORE},
            {0b000100010100, ILLEGAL_SCORE},
            {0b000101000100, ILLEGAL_SCORE},
            {0b100101100000, ILLEGAL_SCORE},
            {0b100101100010, ILLEGAL_SCORE},
            {0b100101100011, ILLEGAL_SCORE},
            {0b100101100001, ILLEGAL_SCORE},
            {0b100101101000, ILLEGAL_SCORE},
            {0b100101101010, ILLEGAL_SCORE},
            {0b100101101011, ILLEGAL_SCORE},
            {0b100101101001, ILLEGAL_SCORE},
            {0b100101101100, ILLEGAL_SCORE},
            {0b100101101110, ILLEGAL_SCORE},
            {0b100101101111, ILLEGAL_SCORE},
            {0b100101101101, ILLEGAL_SCORE},
            {0b100101100100, ILLEGAL_SCORE},
            {0b100101100110, ILLEGAL_SCORE},
            {0b100101100111, ILLEGAL_SCORE},
            {0b100101100101, ILLEGAL_SCORE},
            {0b000010010110, ILLEGAL_SCORE},
            {0b001010010110, ILLEGAL_SCORE},
            {0b001110010110, ILLEGAL_SCORE},
            {0b000110010110, ILLEGAL_SCORE},
            {0b100010010110, ILLEGAL_SCORE},
            {0b101010010110, ILLEGAL_SCORE},
            {0b101110010110, ILLEGAL_SCORE},
            {0b100110010110, ILLEGAL_SCORE},
            {0b110010010110, ILLEGAL_SCORE},
            {0b111010010110, ILLEGAL_SCORE},
            {0b111110010110, ILLEGAL_SCORE},
            {0b110110010110, ILLEGAL_SCORE},
            {0b010010010110, ILLEGAL_SCORE},
            {0b011010010110, ILLEGAL_SCORE},
            {0b011110010110, ILLEGAL_SCORE},
            {0b010110010110, ILLEGAL_SCORE},
        }
    },
    {
        WHITE, {
            { 0b001010100000, ILLEGAL_SCORE},
            { 0b001010100011, ILLEGAL_SCORE},
            { 0b001010100001, ILLEGAL_SCORE},
            { 0b001010100010, ILLEGAL_SCORE},
            { 0b000010101000, ILLEGAL_SCORE},
            { 0b110010101000, ILLEGAL_SCORE},
            { 0b010010101000, ILLEGAL_SCORE},
            { 0b100010101000, ILLEGAL_SCORE},
            { 0b001000101000, ILLEGAL_SCORE},
            { 0b001010001000, ILLEGAL_SCORE},
            { 0b011010010000, ILLEGAL_SCORE},
            { 0b011010010010, ILLEGAL_SCORE},
            { 0b011010010011, ILLEGAL_SCORE},
            { 0b011010010001, ILLEGAL_SCORE},
            { 0b011010011000, ILLEGAL_SCORE},
            { 0b011010011010, ILLEGAL_SCORE},
            { 0b011010011011, ILLEGAL_SCORE},
            { 0b011010011001, ILLEGAL_SCORE},
            { 0b011010011100, ILLEGAL_SCORE},
            { 0b011010011110, ILLEGAL_SCORE},
            { 0b011010011111, ILLEGAL_SCORE},
            { 0b011010011101, ILLEGAL_SCORE},
            { 0b011010010100, ILLEGAL_SCORE},
            { 0b011010010110, ILLEGAL_SCORE},
            { 0b011010010111, ILLEGAL_SCORE},
            { 0b011010010101, ILLEGAL_SCORE},
            { 0b000001101001, ILLEGAL_SCORE},
            { 0b001001101001, ILLEGAL_SCORE},
            { 0b001101101001, ILLEGAL_SCORE},
            { 0b000101101001, ILLEGAL_SCORE},
            { 0b100001101001, ILLEGAL_SCORE},
            { 0b101001101001, ILLEGAL_SCORE},
            { 0b101101101001, ILLEGAL_SCORE},
            { 0b100101101001, ILLEGAL_SCORE},
            { 0b110001101001, ILLEGAL_SCORE},
            { 0b111001101001, ILLEGAL_SCORE},
            { 0b111101101001, ILLEGAL_SCORE},
            { 0b110101101001, ILLEGAL_SCORE},
            { 0b010001101001, ILLEGAL_SCORE},
            { 0b011001101001, ILLEGAL_SCORE},
            { 0b011101101001, ILLEGAL_SCORE},
            { 0b010101101001, ILLEGAL_SCORE},
        },
    }
};

const t_patterns _capture_patterns
{
    {

        BLACK, {
            { 0b011010010000, CAPTURE_SCORE },
            { 0b011010010010, CAPTURE_SCORE },
            { 0b011010010011, CAPTURE_SCORE },
            { 0b011010010001, CAPTURE_SCORE },
            { 0b011010011000, CAPTURE_SCORE },
            { 0b011010011010, CAPTURE_SCORE },
            { 0b011010011011, CAPTURE_SCORE },
            { 0b011010011001, CAPTURE_SCORE },
            { 0b011010011100, CAPTURE_SCORE },
            { 0b011010011110, CAPTURE_SCORE },
            { 0b011010011111, CAPTURE_SCORE },
            { 0b011010011101, CAPTURE_SCORE },
            { 0b011010010100, CAPTURE_SCORE },
            { 0b011010010110, CAPTURE_SCORE },
            { 0b011010010111, CAPTURE_SCORE },
            { 0b011010010101, CAPTURE_SCORE },
            { 0b000001101001, CAPTURE_SCORE },
            { 0b001001101001, CAPTURE_SCORE },
            { 0b001101101001, CAPTURE_SCORE },
            { 0b000101101001, CAPTURE_SCORE },
            { 0b100001101001, CAPTURE_SCORE },
            { 0b101001101001, CAPTURE_SCORE },
            { 0b101101101001, CAPTURE_SCORE },
            { 0b100101101001, CAPTURE_SCORE },
            { 0b110001101001, CAPTURE_SCORE },
            { 0b111001101001, CAPTURE_SCORE },
            { 0b111101101001, CAPTURE_SCORE },
            { 0b110101101001, CAPTURE_SCORE },
            { 0b010001101001, CAPTURE_SCORE },
            { 0b011001101001, CAPTURE_SCORE },
            { 0b011101101001, CAPTURE_SCORE },
            { 0b010101101001, CAPTURE_SCORE },
        }
    },
    {
        WHITE, {
            { 0b100101100000, CAPTURE_SCORE },
            { 0b100101100010, CAPTURE_SCORE },
            { 0b100101100011, CAPTURE_SCORE },
            { 0b100101100001, CAPTURE_SCORE },
            { 0b100101101000, CAPTURE_SCORE },
            { 0b100101101010, CAPTURE_SCORE },
            { 0b100101101011, CAPTURE_SCORE },
            { 0b100101101001, CAPTURE_SCORE },
            { 0b100101101100, CAPTURE_SCORE },
            { 0b100101101110, CAPTURE_SCORE },
            { 0b100101101111, CAPTURE_SCORE },
            { 0b100101101101, CAPTURE_SCORE },
            { 0b100101100100, CAPTURE_SCORE },
            { 0b100101100110, CAPTURE_SCORE },
            { 0b100101100111, CAPTURE_SCORE },
            { 0b100101100101, CAPTURE_SCORE },
            { 0b000010010110, CAPTURE_SCORE },
            { 0b001010010110, CAPTURE_SCORE },
            { 0b001110010110, CAPTURE_SCORE },
            { 0b000110010110, CAPTURE_SCORE },
            { 0b100010010110, CAPTURE_SCORE },
            { 0b101010010110, CAPTURE_SCORE },
            { 0b101110010110, CAPTURE_SCORE },
            { 0b100110010110, CAPTURE_SCORE },
            { 0b110010010110, CAPTURE_SCORE },
            { 0b111010010110, CAPTURE_SCORE },
            { 0b111110010110, CAPTURE_SCORE },
            { 0b110110010110, CAPTURE_SCORE },
            { 0b010010010110, CAPTURE_SCORE },
            { 0b011010010110, CAPTURE_SCORE },
            { 0b011110010110, CAPTURE_SCORE },
            { 0b010110010110, CAPTURE_SCORE },
        },
    }
};


Board::Board(uint8_t size) {
    if (size > 19)
        throw std::logic_error("Boards cannot be bigger than 19");
    this->size = size;
    original = new uint64_t[size];

    std::memset(original, 0, sizeof(uint64_t) * size);
}

Board::~Board() {
    delete[] original;
}

// int Board::diagonal_position(t_coord position) const {
//     return (position.y + position.x) * size + position.x;
// }

// int Board::original_position(t_coord position) const {
//     return position.y * size + position.x;
// }

// int Board::vertical_position(t_coord position) const {
//     return position.x * size + (size - 1 - position.y);
// }

t_coord Board::diagonal_position(t_coord position) const {
    return t_coord{position.x , position.x + position.y};
}

t_coord Board::original_position(t_coord position) const {
    return t_coord{position.x, position.y};
}

t_coord Board::vertical_position(t_coord position) const {
    return t_coord{position.y, position.x};
}

void Board::validate_coord(t_coord position) {
    if (position.x < 0 || position.x >= size || position.y < 0 || position.y >= size)
        throw std::logic_error("Position out of range");
}

t_piece Board::get_piece(t_coord piece_coord, t_board_type type) {
    t_coord pos;
    uint8_t board_size = this->size;
    position_func position_func_d;

    switch (type) {
        case ORIGINAL:
            pos = original_position(piece_coord);
            break;
        case VERTICAL:
            pos = vertical_position(piece_coord);
            break;
        case DIAGONAL:
            pos = diagonal_position(piece_coord);
            // std::cout << "Diagonal: " << pos.x << " " << pos.y << std::endl;
            break;
        default:
            return ERROR;
    }
    if (pos.x < 0 || pos.x >= size || pos.y < 0 || pos.y >= board_size)
        return ERROR;
    return (t_piece)((original[pos.y] >> ((pos.x % 32) * 2)) & 3);
}

void Board::update_board(uint64_t *board, t_coord pos, t_piece piece) {
    uint64_t mask = ~(uint64_t(3) << pos.x * 2);
    board[pos.y] = (board[pos.y] & mask) | (uint64_t(piece) << (pos.x) * 2);
}

void Board::set_position(t_coord position, t_piece piece) {
    validate_coord(position);

    t_coord o_position = original_position(position);
    _evaluation_edges = {
        {std::min(o_position.x, _evaluation_edges.x.first), std::max(o_position.x, _evaluation_edges.x.second)},
        {std::min(o_position.y, _evaluation_edges.y.first), std::max(o_position.y, _evaluation_edges.y.second)}
    };
    update_board(original, o_position, piece);
}

void Board::remove_piece(t_coord position) {
    set_position(position, EMPTY);
}


int64_t Board::evaluate_position(t_coord pos, t_piece color, t_board_type type) {
    // uint16_t pattern = 0;

    uint16_t pattern = get_piece(t_coord{pos.x - 1, pos.y}, type);
    // int shift = std::min(pos.x, (int)size - 6) << 2;
    // pattern |= ((board[pos.y]) << shift) & 0xfff;
    for (int i = -1; i < 5; i++) {
        pattern = (pattern << 2);
        t_coord new_pos = {pos.x + i, pos.y};
        pattern |= get_piece(new_pos, type);
    }
    
    // std::cout << "Pattern: " << std::hex << std::bitset<12>(pattern) << std::dec << std::endl;
    auto d = _attack_patterns.at(color).find(pattern);
    if (d != _attack_patterns.at(color).end()) {
        // std::cout << "Score: " << d->second << std::endl;
        // std::cout << "Pattern: " 
        // std::cout << "Line: " << std::hex << std::bitset<64>(board[pos.y]) << std::dec << std::endl;
        return d->second;
    }
    return 0;
}

int64_t Board::evaluate_board(t_piece player_color) {
    int64_t score = 0;

    for (int y = _evaluation_edges.y.first; y < _evaluation_edges.y.second; y++) {
        if (!original[y])
            continue;
        for (int x = _evaluation_edges.x.first; x < _evaluation_edges.x.second; x +=5) {
            t_coord pos = {x, y};
            if (y < size) {
                score += evaluate_position(pos, player_color, ORIGINAL);
                score += evaluate_position(pos, player_color, VERTICAL);
                score += evaluate_position(pos, player_color, DIAGONAL);
                score -= evaluate_position(pos, GET_OPPOSITE_PIECE(player_color), ORIGINAL);
                score -= evaluate_position(pos, GET_OPPOSITE_PIECE(player_color), VERTICAL);
                score -= evaluate_position(pos, GET_OPPOSITE_PIECE(player_color), DIAGONAL);
            }
        }
    }
    return score;
}

    #include <chrono>
int main() {

    Board board(19);

    // Set the black pieces
    board.set_position({0, 0}, BLACK);
    // board.set_position({1, 0}, BLACK);
    // board.set_position({2, 0}, BLACK);
    board.set_position({1, 1}, BLACK);
    board.set_position({2, 2}, BLACK);
    board.set_position({3, 3}, BLACK);
    

    // board.set_position({3, 0}, BLACK);
    // board.set_position({4, 0}, BLACK);
    // board.set_position({5, 0}, BLACK);
    // board.set_position({0, 2}, BLACK);
    // board.set_position({1, 1}, BLACK);

    // Set the white piece
    board.set_position({0, 1}, WHITE);
    // board.set_position({2, 2}, WHITE);

    // Print the original board
    // std::cout << "Original Board:" << std::endl;
    // for (int y = 0; y < 19; y++) {
    //     for (int x = 0; x < 19; x++) {
    //         std::cout << board.get_piece({x, y}, ORIGINAL) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // // // Print the vertical board
    // std::cout << "\nVertical Board:" << std::endl;
    // for (int y = 0; y < 19; y++) {
    //     for (int x = 0; x < 19; x++) {
    //         std::cout << board.get_piece({x, y}, VERTICAL) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // // // Print the diagonal board
    // std::cout << "\nDiagonal Board:" << std::endl;
    // for (int y = 0; y < 19; y++) {
    //     for (int x = 0; x < 19; x++) {
    //         std::cout << board.get_piece({x, y}, DIAGONAL) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Evaluate the board for the black player
    auto start = std::chrono::high_resolution_clock::now();
    // std::cout << "\nBlack Score: " << board.evaluate_board(BLACK) << std::endl;

    for (int i = 0; i < 3000000; i++) {
        board.evaluate_board(BLACK);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;

    return 0;
}