#include <iostream>
#include <random>
#include "Board.hpp"

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
            {0b011000100000, TWO_SCORE},
            {0b111010000000, TWO_SCORE},
        },
    }
};

const t_patterns Board::_illegal_patterns
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

const t_patterns Board::_capture_patterns
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

const t_patterns Board::_defense_patterns = {
    {
        BLACK, {
            { 0b011010101011, FIVE_BLOCK_SCORE},
            { 0b011010101001, FIVE_BLOCK_SCORE},
            { 0b101001101010, FIVE_BLOCK_SCORE},
            { 0b011001101010, FIVE_BLOCK_SCORE},
            { 0b111001101010, FIVE_BLOCK_SCORE},
            { 0b001001101010, FIVE_BLOCK_SCORE},
            { 0b101010011010, FIVE_BLOCK_SCORE},
            { 0b011010011010, FIVE_BLOCK_SCORE},
            { 0b111010011010, FIVE_BLOCK_SCORE},
            { 0b001010011010, FIVE_BLOCK_SCORE},
            { 0b101010100110, FIVE_BLOCK_SCORE},
            { 0b011010100110, FIVE_BLOCK_SCORE},
            { 0b111010100110, FIVE_BLOCK_SCORE},
            { 0b001010100110, FIVE_BLOCK_SCORE},
            { 0b110110101010, FIVE_BLOCK_SCORE},
            { 0b100110101000, FIVE_BLOCK_SCORE},
            { 0b100110101011, FIVE_BLOCK_SCORE},
            { 0b100110101010, FIVE_BLOCK_SCORE},
            { 0b100110101001, FIVE_BLOCK_SCORE},
            { 0b111001101010, FIVE_BLOCK_SCORE},
            { 0b101001101000, FIVE_BLOCK_SCORE},
            { 0b101001101011, FIVE_BLOCK_SCORE},
            { 0b101001101010, FIVE_BLOCK_SCORE},
            { 0b101001101001, FIVE_BLOCK_SCORE},
            { 0b101010011000, FIVE_BLOCK_SCORE},
            { 0b101010011011, FIVE_BLOCK_SCORE},
            { 0b101010011010, FIVE_BLOCK_SCORE},
            { 0b101010011001, FIVE_BLOCK_SCORE},
            { 0b101010100100, FIVE_BLOCK_SCORE},
            { 0b101010100111, FIVE_BLOCK_SCORE},
            { 0b101010100110, FIVE_BLOCK_SCORE},
            { 0b101010100101, FIVE_BLOCK_SCORE},
            { 0b011010100000, OPEN_BLOCK_SCORE},
            { 0b001010100100, OPEN_BLOCK_SCORE},
            { 0b000010101001, OPEN_BLOCK_SCORE},
            { 0b000110101000, OPEN_BLOCK_SCORE},
            { 0b011010100011, OPEN_BLOCK_SCORE},
            { 0b011010100001, OPEN_BLOCK_SCORE},
            { 0b010010101001, OPEN_BLOCK_SCORE},
            { 0b110010101001, OPEN_BLOCK_SCORE},
            { 0b001010011000, OPEN_BLOCK_SCORE},
        }
    },
    {
        WHITE, {
            { 0b100101010111, FIVE_BLOCK_SCORE},
            { 0b100101010110, FIVE_BLOCK_SCORE},
            { 0b010110010101, FIVE_BLOCK_SCORE},
            { 0b100110010101, FIVE_BLOCK_SCORE},
            { 0b110110010101, FIVE_BLOCK_SCORE},
            { 0b000110010101, FIVE_BLOCK_SCORE},
            { 0b010101100101, FIVE_BLOCK_SCORE},
            { 0b100101100101, FIVE_BLOCK_SCORE},
            { 0b110101100101, FIVE_BLOCK_SCORE},
            { 0b000101100101, FIVE_BLOCK_SCORE},
            { 0b010101011001, FIVE_BLOCK_SCORE},
            { 0b100101011001, FIVE_BLOCK_SCORE},
            { 0b110101011001, FIVE_BLOCK_SCORE},
            { 0b000101011001, FIVE_BLOCK_SCORE},
            { 0b111001010101, FIVE_BLOCK_SCORE},
            { 0b011001010100, FIVE_BLOCK_SCORE},
            { 0b011001010111, FIVE_BLOCK_SCORE},
            { 0b011001010101, FIVE_BLOCK_SCORE},
            { 0b011001010110, FIVE_BLOCK_SCORE},
            { 0b110110010101, FIVE_BLOCK_SCORE},
            { 0b010110010100, FIVE_BLOCK_SCORE},
            { 0b010110010111, FIVE_BLOCK_SCORE},
            { 0b010110010101, FIVE_BLOCK_SCORE},
            { 0b010110010110, FIVE_BLOCK_SCORE},
            { 0b010101100100, FIVE_BLOCK_SCORE},
            { 0b010101100111, FIVE_BLOCK_SCORE},
            { 0b010101100101, FIVE_BLOCK_SCORE},
            { 0b010101100110, FIVE_BLOCK_SCORE},
            { 0b010101011000, FIVE_BLOCK_SCORE},
            { 0b010101011011, FIVE_BLOCK_SCORE},
            { 0b010101011001, FIVE_BLOCK_SCORE},
            { 0b010101011010, FIVE_BLOCK_SCORE},
            { 0b100101010000, OPEN_BLOCK_SCORE},
            { 0b000101011000, OPEN_BLOCK_SCORE},
            { 0b000001010110, OPEN_BLOCK_SCORE},
            { 0b001001010100, OPEN_BLOCK_SCORE},
            { 0b100101010011, OPEN_BLOCK_SCORE},
            { 0b100101010010, OPEN_BLOCK_SCORE},
            { 0b100001010110, OPEN_BLOCK_SCORE},
            { 0b110001010110, OPEN_BLOCK_SCORE},
            { 0b000101100100, OPEN_BLOCK_SCORE},
        }
    },
};

const std::array<t_coord, 4> Board::_directions {{
    {0, 1},
    {1, 0},
    {-1, 1},
    {1, 1}
}};

const std::vector<t_coord> Board::_moveset_cells {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
    {1, -1},
    {-1, 1},
    {1, 1},
    {-1, -1},
};


Board::Board(uint8_t size) {
    if (size > 19)
        throw std::logic_error("Boards cannot be bigger than 19");
    this->size = size;
    board = new uint64_t[size];
    _illegal_boards[0] = new uint64_t[size];
    _illegal_boards[1] = new uint64_t[size];

    std::memset(board, 0, sizeof(uint64_t) * size);
    std::memset(_illegal_boards[0], 0, sizeof(uint64_t) * size);
    std::memset(_illegal_boards[1], 0, sizeof(uint64_t) * size);
    std::memset(_capture_count, 0, sizeof(int) * 2);

    _evaluation_edges = {
        {0, size - 1},
        {0, size - 1}
    };
}

Board::~Board() {
    delete[] board;
    delete[] _illegal_boards[0];
    delete[] _illegal_boards[1];
}

void Board::validate_coord(t_coord position, t_piece piece) const {
    if (position.x < 0 || position.x >= size || position.y < 0 || position.y >= size)
        throw std::logic_error("Position out of range");
    if ((_illegal_boards[piece - 1][position.y] >> (position.x << 1)) & 3)
        throw std::logic_error("Illegal move");
}

inline t_piece Board::get_piece(t_coord piece_coord) const {
    if (piece_coord.x < 0 || piece_coord.x >= size || piece_coord.y < 0 || piece_coord.y >= size)
        return ERROR;
    return (t_piece)((board[piece_coord.y] >> (piece_coord.x << 1)) & 3);
}

inline t_piece Board::get_piece(uint64_t *board, t_coord piece_coord) const{
    if (piece_coord.x < 0 || piece_coord.x >= size || piece_coord.y < 0 || piece_coord.y >= size)
        return ERROR;
    return (t_piece)((board[piece_coord.y] >> (piece_coord.x << 1)) & 3);
}

void Board::update_board(uint64_t *board, t_coord pos, t_piece piece) {
    uint64_t mask = ~(uint64_t(3) << pos.x * 2);
    board[pos.y] = (board[pos.y] & mask) | (uint64_t(piece) << (pos.x) * 2);
}

void Board::set_position(t_coord position, t_piece piece) {
    _evaluation_edges = {
        {std::min(position.x, _evaluation_edges.x.first), std::max(position.x, _evaluation_edges.x.second)},
        {std::min(position.y, _evaluation_edges.y.first), std::max(position.y, _evaluation_edges.y.second)}
    };
    update_board(board, position, piece);
}

inline void Board::remove_piece(t_coord position) {
    set_position(position, EMPTY);
}


bool Board::possible_capture(t_coord pos, t_piece color, t_coord dir) const {
    for (auto& curr_dir : _directions) {
        if (curr_dir == dir)
            continue;
        for (auto& curr_dir : {curr_dir, t_coord{-curr_dir.x, -curr_dir.y}}) {
            uint8_t pattern = capture_pattern(pos, curr_dir, color);
            if ((color == BLACK) ? pattern == BLACK_CAPTURE_PATTERN: pattern == WHITE_CAPTURE_PATTERN)
                return true;
        }
    };
    return false;
}

bool Board::check_for_win(t_coord pos, t_piece color, t_coord dir) const {
    uint64_t combo = 0;
    t_piece piece;

    for (;;) {
        if (combo == 5)
            return true;
        piece = get_piece(pos);
        if (piece != color)
            break;
        if (possible_capture(pos, GET_OPPOSITE_PIECE(color), dir))
            combo = 0;
        else
            combo++;
        pos += dir;
    }
    return false;
}

int64_t Board::evaluate_position(t_coord pos, t_piece color, t_coord dir, const t_scores_map &patterns) const {
    uint16_t pattern = 0xFFF;
    t_piece piece;
    t_coord current_pos = pos;

    current_pos -= dir;
    for (int i = 0; i < 6; i++) {
        piece = get_piece(current_pos);
        if (i == 0 && piece == color)
            return 0;
        if (i != 0 && piece == GET_OPPOSITE_PIECE(color))
            break;
        pattern = (pattern << 2) | piece;
        current_pos += dir;
    }
    auto it = patterns.find(pattern & 0xFFF);
    t_scores score = (it != patterns.end()) ? it->second : static_cast<t_scores>(0);
    if (score == FIVE_SCORE ){
        if (check_for_win(pos, color, dir))
            return WIN_SCORE;
}
    return (it != patterns.end()) ? it->second : 0;
}

bool Board::evaluate_capture(t_coord pos, t_coord dir)
{
    t_piece check_piece = get_piece(pos);

    for (auto& factor: {1, -1}) {
        t_coord check_pos = pos + dir * factor;
        uint8_t pattern = check_piece;

        for (int i = 1; i < 4; i++) {
            t_piece curr_piece = get_piece(check_pos);
            if (curr_piece == ERROR || curr_piece == EMPTY || (i < 2 && curr_piece == check_piece))
                return false;
            pattern = pattern << 2 | get_piece(check_pos);
            check_pos += dir;        
        }
        if ((check_piece == BLACK) ? pattern == BLACK_CAPTURE_PATTERN: pattern == WHITE_CAPTURE_PATTERN)
            return true;
    }
    return false;
}

DualColorPotential Board::position_potential(t_updates& updates_queue, t_coord pos, t_coord dir)
{
    DualColorPotential result = {0, 0};
    const t_piece colors[2] = {BLACK, WHITE};

    for (int color_index = 0; color_index < 2; color_index++)
    {
        t_piece color = colors[color_index];
        int32_t attack_score = 0;
        int32_t defense_score = 0;
        int32_t capture_score = 0;
        int32_t illegal_score = 0;
        t_piece current_piece;
        uint16_t current_pattern;
        uint16_t altered_pattern;
        t_coord pattern_position;
        uint8_t capture_count;

        const t_scores_map &attack_patterns = Board::_attack_patterns.at(color);
        const t_scores_map &capture_patterns = Board::_capture_patterns.at(color);
        const t_scores_map &illegal_patterns = Board::_illegal_patterns.at(color);
        const t_scores_map &defense_patterns = Board::_defense_patterns.at(color);

        capture_count = _capture_count[color - 1];
        current_pattern = colors[color_index ];
        pattern_position = pos + dir;
        for (int j = 0; j < 5; j++)
        {
            current_piece = get_piece(pos);
            if (current_piece == EMPTY)
                current_piece = get_piece(_illegal_boards[color_index], pattern_position);
            current_pattern <<= 2;
            current_pattern |= get_piece(pattern_position);
            pattern_position += dir;
        }

        for (int i = 0; i < 6; i++)
        {
            current_piece = get_piece(pos);
            current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
            if (capture_patterns.count(current_pattern))
                capture_score += CAPTURE_SCORE * (capture_count + 1);
            if (attack_patterns.count(current_pattern))
                attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
            if (defense_patterns.count(current_pattern))
                defense_score = std::max(int32_t(defense_patterns.at(current_pattern)), attack_score);
            if (illegal_patterns.count(current_pattern))
                illegal_score = ILLEGAL_SCORE;
            pos -= dir;
            current_pattern >>= 2;
        }
        int64_t total_score = 0;
        if (illegal_score)
            total_score = ILLEGAL_SCORE;
        else
            total_score = attack_score + defense_score + capture_score;
        if (color == BLACK)
            result.black_potential = total_score;
        else
            result.white_potential = total_score;
    }
    
    return result;
}


uint8_t Board::capture_pattern(t_coord pos, t_coord dir, t_piece piece) const {
    uint8_t pattern = 0;
    uint8_t empty_c = 0;
    uint8_t piece_c = 0;

    for (int i = 0; i < 4; ++i) {
        t_coord check_pos = pos + dir * (i - 1);
        t_piece curr_piece = get_piece(check_pos);
        
        if (curr_piece == ERROR || 
            (curr_piece == EMPTY && (empty_c++ || get_piece(_illegal_boards[piece - 1], check_pos))) ||
            (curr_piece == piece && piece_c++ > 1)) {
            return 0;
        }
        pattern |= (curr_piece == EMPTY ? piece : curr_piece) << (i << 1);
    }
    return pattern;
}
void Board::evaluate_new_move(t_updates &updates_queue, t_coord pos) {
    static const t_piece colors[2] = {BLACK, WHITE};
    bool illegal[2] = {false, false};
    int64_t color_score[2] = {0, 0};

    for (auto& dir: _directions) {
        if (get_piece(pos + dir) != EMPTY)
            continue;
        DualColorPotential potentials = position_potential(updates_queue, pos, dir);
        
        for (int i = 0; i < 2; ++i) {
            t_piece color = colors[i];
            int64_t score = (color == BLACK) ? potentials.black_potential : potentials.white_potential;

            if (score == ILLEGAL_SCORE){
                record_illegal_update(updates_queue, pos, color, ADD);
                illegal[i] = true;
            }
            color_score[i] += score;
        }
    }
    if (!illegal[0])
        record_illegal_update(updates_queue, pos, colors[0], REMOVE);
    if (!illegal[1])
        record_illegal_update(updates_queue, pos, colors[1], REMOVE);
    record_moveset_update(updates_queue, pos, colors[0], color_score[0], ADD);
    record_moveset_update(updates_queue, pos, colors[1], color_score[1], ADD);
}

void Board::record_illegal_update(t_updates &updates_queue, t_coord pos, t_piece color, t_update_type type) {
    // if (type == ADD){
    //     ++_illegal_positions[color - 1][pos];
    //     if (_illegal_positions[color - 1][pos])
    //         update_board(_illegal_boards[color - 1], pos, ERROR);
    // }
    // else {
    //     --_illegal_positions[color - 1][pos];
    //     if (!_illegal_positions[color - 1][pos])
    //         update_board(_illegal_boards[color - 1], pos, EMPTY);
    // }
    // updates_queue.emplace_back(t_update{ILLEGAL, type, pos});
}

void Board::revert_illegal_update(t_update& update) {
    // if (update.piece) {
    //     if (update.type == ADD){
    //         if (_illegal_positions[update.piece - 1][update.pos] < 1)
    //             return;
    //         --_illegal_positions[update.piece - 1][update.pos];
    //         if (_illegal_positions[update.piece - 1][update.pos] == 0)
    //             update_board(_illegal_boards[update.piece - 1], update.pos, EMPTY);
    //     }
    //     else{
    //         ++_illegal_positions[update.piece - 1][update.pos];
    //         if (_illegal_positions[update.piece - 1][update.pos] > 0)
    //             update_board(_illegal_boards[update.piece - 1], update.pos, ERROR);
    //     }
    // }
}

void Board::record_moveset_update(t_updates &updates_queue, t_coord pos, t_piece color, int64_t score, t_update_type type) {
    t_scored_moveset& moveset = _moveset_positions[color - 1][pos];
    t_scored_moveset old_moveset = moveset;
    if (type == ADD) {
        ++moveset.count;
        if (score == ILLEGAL_SCORE)
            moveset.blocked = true;
        else
            moveset.blocked = false;
        moveset.score = score;
    }
    else {
        --moveset.count;
    } 
    updates_queue.emplace_back(t_update{MOVESET, type, pos, .piece=color, .moveset_update = t_moveset_update{old_moveset, moveset}});
}

void Board::revert_moveset_update(const t_update& update) {
    if (update.piece == BLACK || update.piece == WHITE) {
        t_scored_moveset& current_moveset = _moveset_positions[update.piece - 1][update.pos];
        const t_scored_moveset& old_moveset = update.moveset_update[update.piece - 1].old_moveset;

        if (update.type == ADD)
            --current_moveset.count;
        else
            ++current_moveset.count;

        current_moveset.blocked = old_moveset.blocked;
        current_moveset.score = old_moveset.score;

        if (current_moveset.count == 0)
            _moveset_positions[update.piece - 1].erase(update.pos);
    }
}

void Board::record_board_update(t_updates &updates_queue, t_coord pos, t_piece piece, t_update_type type) {
    if (type == ADD)
        set_position(pos, piece);
    else
    {
        remove_piece(pos);
        _capture_count[piece - 1]++;
    }
    updates_queue.emplace_back(t_update{BOARD, type, pos, .piece = piece});
}

void Board::update_node(t_updates& updates_queue, t_coord curr_pos, t_piece curr_piece) {
    t_coord pos = curr_pos;
    t_piece piece = curr_piece;

    record_board_update(updates_queue, pos, piece, ADD);
    for (const auto& dir : _moveset_cells) {
        if (evaluate_capture(pos, dir)) {
            t_coord capture_pos = pos + dir;
            for (int i = 0; i < 2; ++i, capture_pos += dir) {
                record_board_update(updates_queue, capture_pos, GET_OPPOSITE_PIECE(curr_piece), REMOVE);
                for (const auto& update_dir : _moveset_cells) {
                    record_moveset_update(updates_queue, capture_pos + update_dir, BLACK, 0, REMOVE);
                    record_moveset_update(updates_queue, capture_pos + update_dir, WHITE, 0, REMOVE);
                }
                evaluate_new_move(updates_queue, capture_pos);
            }
        }
    }
    for (const auto& dir : _moveset_cells){
        t_coord next_pos = pos + dir;
        if (get_piece(next_pos) == EMPTY)
            evaluate_new_move(updates_queue, next_pos);
    }
}

t_ordered_moves Board::order_moves(t_piece color) {
    t_ordered_moves moves;
    t_moveset& moveset = _moveset_positions[color - 1];
    if (_moveset_positions[color - 1].empty())
    {
        moves.push_back({0, t_coord{size >> 1, size >> 1}});
        return moves;
    }
    for (auto& [pos, scored_moveset] : moveset) {
        if (scored_moveset.blocked)
            continue;
        if (get_piece(pos) != EMPTY)
            continue;
        if (!scored_moveset.count)
            continue;
        moves.push_back({scored_moveset.score, pos});
    }
    std::sort(moves.begin(), moves.end(), std::greater<>());
    return moves;
}

size_t Board::make_move(t_coord pos, t_piece piece, t_updates& updates_queue) {
    size_t  queue_size = updates_queue.size();
    update_node(updates_queue, pos, piece);
    return updates_queue.size() - queue_size;
}

void Board::revert_updates(t_updates& updates, size_t count) {
    while (count--){
        t_update update = updates.back();
        switch (update.target) {
            case BOARD:
                if (update.type == ADD)
                    remove_piece(update.pos);
                else {
                    set_position(update.pos, update.piece);
                    _capture_count[update.piece - 1]--;
                }
                break;
            case ILLEGAL:
                revert_illegal_update(update);
                break;
            case MOVESET:
                revert_moveset_update(update);
                break;
        }
        updates.pop_back();
    }
}

int64_t Board::evaluate_board(t_piece player_color) const {
    int64_t             score = 0;
    const t_scores_map& p_att_patterns = Board::_attack_patterns.at(player_color);
    const t_scores_map& op_att_patterns = Board::_attack_patterns.at(GET_OPPOSITE_PIECE(player_color));
    const t_piece       opposite_color = GET_OPPOSITE_PIECE(player_color);

    if (_capture_count[player_color - 1] >= 5)
        return WIN_SCORE;
    if (_capture_count[opposite_color - 1] >= 5)
        return -WIN_SCORE;
    for (int y = _evaluation_edges.y.first; y <= _evaluation_edges.y.second; ++y) {
        uint64_t row = board[y];
        if (!row)
            continue;
        int x = _evaluation_edges.x.first;
        while (row) {
            int bit_pos = __builtin_ctzll(row);
            x = bit_pos >> 1;

            if (x > _evaluation_edges.x.second)
                break;

            t_piece piece = (t_piece)((row >> (x * 2)) & 3);
            if (piece != EMPTY) {
                t_coord             pos = {x, y};
                const t_scores_map& att_patterns = (piece == player_color) ? p_att_patterns : op_att_patterns;
                int64_t             position_score = 0;
                for (const auto& dir : _directions)
                {
                    int64_t score = evaluate_position(pos, piece, dir, att_patterns);
                    if (score == WIN_SCORE)
                        return (piece == player_color) ? WIN_SCORE : -WIN_SCORE;
                    position_score += score;
                }
                score += (piece == player_color) ? position_score : -position_score;
            }
            row &= ~(3ULL << bit_pos);
        }
    }

    return score;
}

void Board::print_board(t_piece curr_piece) const {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            t_coord pos{x, y};
            t_piece piece = get_piece(pos);
            if (piece == EMPTY) {
                auto it = _moveset_positions[curr_piece - 1].find(pos);
                if (it != _moveset_positions[curr_piece - 1].end() && it->second.count) {
                    // std::cout << "\033[31m" << piece << "\033[0m ";
                    std::cout << "* ";
                } else {
                    if (get_piece(_illegal_boards[curr_piece - 1], pos))
                        std::cout << "? ";
                    else
                        std::cout << ". ";
                }
            } else {
                std::cout << piece << " ";
            }
        }
        std::cout << std::endl;
    }
    // print the score of the board
    // std::cout << evaluate_board(curr_piece) << std::endl;
}


// int main(){
//     Board board(19);
//     t_updates updates;
//     t_piece piece = BLACK;
//     t_piece opposite_piece = WHITE;
//     t_coord pos_1 = {9, 9};
//     t_coord pos_2 = {8, 9};
//     // t_coord pos_3 = {7, 9};
//     size_t count_1 = board.make_move(pos_1, piece, updates);
//     board.print_board(piece);

//     size_t count_2 = board.make_move(pos_2, piece, updates);
//     int64_t score = board.evaluate_board(piece);
//     // std::cout << "-----------------------------" << std::endl;
//     // std::cout << score << std::endl;
//     // score = board.position_potential(pos_1 + t_coord{1, 0}, t_coord{1, 0}).black_potential;
//     // std::cout << score << std::endl;
//     // size_t count_3 = board.make_move(pos_3, piece, updates);
//     // for (auto& update : updates)
//     //     std::cout << update.target << " " << update.type << " " << update.pos << std::endl;
//     // board.print_board(piece);
//     // board.revert_updates(updates, count_2);
//     // for (auto& update : updates)
//     //     std::cout << update.target << " " << update.type << " " << update.pos << std::endl;
//     board.print_board(piece);
//     return 0;
// };