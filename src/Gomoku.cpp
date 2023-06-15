#include "Gomoku.hpp"


const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            { 0b010101010101, Gomoku::WINNING_SCORE },
            { 0b010101010100, Gomoku::WINNING_SCORE },
            { 0b010101010111, Gomoku::WINNING_SCORE },
            { 0b010101010110, Gomoku::WINNING_SCORE },
            { 0b000101010101, Gomoku::WINNING_SCORE },
            { 0b110101010101, Gomoku::WINNING_SCORE },
            { 0b100101010101, Gomoku::WINNING_SCORE },
            { 0b010101010101, Gomoku::WINNING_SCORE },
            { 0b000101010100, Gomoku::FREE_FOUR_SCORE },

            { 0b010101010000, Gomoku::FOUR_SCORE },
            { 0b010101010010, Gomoku::FOUR_SCORE },
            { 0b010101010011, Gomoku::FOUR_SCORE },
            { 0b000001010101, Gomoku::FOUR_SCORE },
            { 0b110001010101, Gomoku::FOUR_SCORE },
            { 0b100001010101, Gomoku::FOUR_SCORE },

// Free threes ----- generated by capture ---
            { 0b000101010000, Gomoku::FREE_SCORE },
            { 0b000001010100, Gomoku::FREE_SCORE },
            { 0b000101010010, Gomoku::FREE_SCORE },
            { 0b000101010011, Gomoku::FREE_SCORE },
            { 0b100001010100, Gomoku::FREE_SCORE },
            { 0b110001010100, Gomoku::FREE_SCORE },
            { 0b000101000100, Gomoku::FREE_SCORE },
// -------------------------------------------        
            { 0b000001010111, Gomoku::THREE_SCORE },
            { 0b000001010110, Gomoku::THREE_SCORE },
            { 0b110101010000, Gomoku::THREE_SCORE },
            { 0b100101010000, Gomoku::THREE_SCORE },

            { 0b000000000101, Gomoku::TWO_SCORE },
            { 0b000000010100, Gomoku::TWO_SCORE },
            { 0b000000010111, Gomoku::TWO_SCORE },
            { 0b010100000000, Gomoku::TWO_SCORE },
            { 0b000101000000, Gomoku::TWO_SCORE },
            { 0b110101000000, Gomoku::TWO_SCORE },
            { 0b100101000000, Gomoku::TWO_SCORE },

            { 0b000000000001, Gomoku::ONE_SCORE },
            { 0b110000000001, Gomoku::ONE_SCORE },
            { 0b100000000001, Gomoku::ONE_SCORE },
            { 0b000000000111, Gomoku::ONE_SCORE },
            { 0b000000000110, Gomoku::ONE_SCORE },
            { 0b010000000010, Gomoku::ONE_SCORE },
            { 0b010000000011, Gomoku::ONE_SCORE },
            { 0b110100000000, Gomoku::ONE_SCORE },
            { 0b100100000000, Gomoku::ONE_SCORE },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b101010101010, Gomoku::WINNING_SCORE },
            { 0b101010101000, Gomoku::WINNING_SCORE },
            { 0b101010101011, Gomoku::WINNING_SCORE },
            { 0b101010101001, Gomoku::WINNING_SCORE },
            { 0b001010101010, Gomoku::WINNING_SCORE },
            { 0b111010101010, Gomoku::WINNING_SCORE },
            { 0b011010101010, Gomoku::WINNING_SCORE },
            { 0b101010101010, Gomoku::WINNING_SCORE },
            { 0b001010101000, Gomoku::FREE_FOUR_SCORE },

            { 0b101010100000, Gomoku::FOUR_SCORE },
            { 0b101010100001, Gomoku::FOUR_SCORE },
            { 0b101010100011, Gomoku::FOUR_SCORE },
            { 0b000010101010, Gomoku::FOUR_SCORE },
            { 0b110010101010, Gomoku::FOUR_SCORE },
            { 0b010010101010, Gomoku::FOUR_SCORE },

// Free threes ----- generated by capture ---
            { 0b001010100000, Gomoku::FREE_SCORE },
            { 0b000010101000, Gomoku::FREE_SCORE },
            { 0b001010100001, Gomoku::FREE_SCORE },
            { 0b001010100011, Gomoku::FREE_SCORE },
            { 0b010010101000, Gomoku::FREE_SCORE },
            { 0b110010101000, Gomoku::FREE_SCORE },
            { 0b001010001000, Gomoku::FREE_SCORE },
// -------------------------------------------        
            { 0b000010101011, Gomoku::THREE_SCORE },
            { 0b000010101001, Gomoku::THREE_SCORE },
            { 0b111010100000, Gomoku::THREE_SCORE },
            { 0b011010100000, Gomoku::THREE_SCORE },

            { 0b000000001010, Gomoku::TWO_SCORE },
            { 0b000000101000, Gomoku::TWO_SCORE },
            { 0b000000101011, Gomoku::TWO_SCORE },
            { 0b101000000000, Gomoku::TWO_SCORE },
            { 0b001010000000, Gomoku::TWO_SCORE },
            { 0b111010000000, Gomoku::TWO_SCORE },
            { 0b011010000000, Gomoku::TWO_SCORE },

            { 0b000000000010, Gomoku::ONE_SCORE },
            { 0b110000000010, Gomoku::ONE_SCORE },
            { 0b010000000010, Gomoku::ONE_SCORE },
            { 0b000000001011, Gomoku::ONE_SCORE },
            { 0b000000001001, Gomoku::ONE_SCORE },
            { 0b100000000001, Gomoku::ONE_SCORE },
            { 0b100000000011, Gomoku::ONE_SCORE },
            { 0b111000000000, Gomoku::ONE_SCORE },
            { 0b011000000000, Gomoku::ONE_SCORE },
        },
    }
};

const Gomoku::t_patterns Gomoku::_defense_patterns = {
    {
        Gomoku::BLACK, {
            { 0b011010101011, Gomoku::WIN_BLOCK_SCORE},
            { 0b011010101001, Gomoku::WIN_BLOCK_SCORE},
            { 0b101001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b011001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b111001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b001001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010011010, Gomoku::WIN_BLOCK_SCORE},
            { 0b011010011010, Gomoku::WIN_BLOCK_SCORE},
            { 0b111010011010, Gomoku::WIN_BLOCK_SCORE},
            { 0b001010011010, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b011010100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b111010100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b001010100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b110110101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b100110101000, Gomoku::WIN_BLOCK_SCORE},
            { 0b100110101011, Gomoku::WIN_BLOCK_SCORE},
            { 0b100110101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b100110101001, Gomoku::WIN_BLOCK_SCORE},
            { 0b111001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b101001101000, Gomoku::WIN_BLOCK_SCORE},
            { 0b101001101011, Gomoku::WIN_BLOCK_SCORE},
            { 0b101001101010, Gomoku::WIN_BLOCK_SCORE},
            { 0b101001101001, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010011000, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010011011, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010011010, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010100100, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010100111, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b101010100101, Gomoku::WIN_BLOCK_SCORE},

// Block Free threes ----- generated by capture ---
            { 0b011010100000, Gomoku::FREE_BLOCK_SCORE },
            { 0b001010100100, Gomoku::FREE_BLOCK_SCORE },
            { 0b000010101001, Gomoku::FREE_BLOCK_SCORE },
            { 0b000110101000, Gomoku::FREE_BLOCK_SCORE },
            { 0b011010100011, Gomoku::FREE_BLOCK_SCORE },
            { 0b011010100001, Gomoku::FREE_BLOCK_SCORE },
            { 0b010010101001, Gomoku::FREE_BLOCK_SCORE },
            { 0b110010101001, Gomoku::FREE_BLOCK_SCORE },
            { 0b001010011000, Gomoku::FREE_BLOCK_SCORE },

// ------------------------------------------------        

        }
    },
    {
        Gomoku::WHITE, {
            { 0b100101010111, Gomoku::WIN_BLOCK_SCORE},
            { 0b100101010110, Gomoku::WIN_BLOCK_SCORE},
            { 0b010110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b100110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b110110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b000110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101100101, Gomoku::WIN_BLOCK_SCORE},
            { 0b100101100101, Gomoku::WIN_BLOCK_SCORE},
            { 0b110101100101, Gomoku::WIN_BLOCK_SCORE},
            { 0b000101100101, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b100101011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b110101011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b000101011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b111001010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b011001010100, Gomoku::WIN_BLOCK_SCORE},
            { 0b011001010111, Gomoku::WIN_BLOCK_SCORE},
            { 0b011001010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b011001010110, Gomoku::WIN_BLOCK_SCORE},
            { 0b110110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b010110010100, Gomoku::WIN_BLOCK_SCORE},
            { 0b010110010111, Gomoku::WIN_BLOCK_SCORE},
            { 0b010110010101, Gomoku::WIN_BLOCK_SCORE},
            { 0b010110010110, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101100100, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101100111, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101100101, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101100110, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101011000, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101011011, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101011001, Gomoku::WIN_BLOCK_SCORE},
            { 0b010101011010, Gomoku::WIN_BLOCK_SCORE},

// Block Free threes ----- generated by capture ---
            { 0b100101010000, Gomoku::FREE_BLOCK_SCORE },
            { 0b000101011000, Gomoku::FREE_BLOCK_SCORE },
            { 0b000001010110, Gomoku::FREE_BLOCK_SCORE },
            { 0b001001010100, Gomoku::FREE_BLOCK_SCORE },
            { 0b100101010011, Gomoku::FREE_BLOCK_SCORE },
            { 0b100101010010, Gomoku::FREE_BLOCK_SCORE },
            { 0b100001010110, Gomoku::FREE_BLOCK_SCORE },
            { 0b110001010110, Gomoku::FREE_BLOCK_SCORE },
            { 0b000101100100, Gomoku::FREE_BLOCK_SCORE },
// ------------------------------------------------    
        }
    },
};



const Gomoku::t_patterns Gomoku::_capture_patterns
{
    {
        Gomoku::BLACK, {
            { 0b01101001, Gomoku::CAPTURE_SCORE },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b10010110, Gomoku::CAPTURE_SCORE },
        },
    }
};

const Gomoku::t_patterns Gomoku::_illegal_patterns
{
    {
        Gomoku::BLACK, {
            { 0b000101010000, Gomoku::ILLEGAL_SCORE },
            { 0b000001010100, Gomoku::ILLEGAL_SCORE },
            { 0b110001010100, Gomoku::ILLEGAL_SCORE },
            { 0b100001010100, Gomoku::ILLEGAL_SCORE },
            { 0b010001010100, Gomoku::ILLEGAL_SCORE },
            { 0b000101010011, Gomoku::ILLEGAL_SCORE },
            { 0b000101010010, Gomoku::ILLEGAL_SCORE },
            { 0b000101010001, Gomoku::ILLEGAL_SCORE },
            { 0b100101100000, Gomoku::ILLEGAL_SCORE },
            { 0b100101100101, Gomoku::ILLEGAL_SCORE },
            { 0b100101101010, Gomoku::ILLEGAL_SCORE },
            { 0b100101100110, Gomoku::ILLEGAL_SCORE },
            { 0b100101101001, Gomoku::ILLEGAL_SCORE },
            { 0b100101100111, Gomoku::ILLEGAL_SCORE },
            { 0b100101101011, Gomoku::ILLEGAL_SCORE },
            { 0b001001011000, Gomoku::ILLEGAL_SCORE },
            { 0b011001011001, Gomoku::ILLEGAL_SCORE },
            { 0b011001011010, Gomoku::ILLEGAL_SCORE },
            { 0b101001011010, Gomoku::ILLEGAL_SCORE },
            { 0b101001011001, Gomoku::ILLEGAL_SCORE },
            { 0b011001011011, Gomoku::ILLEGAL_SCORE },
            { 0b101001011011, Gomoku::ILLEGAL_SCORE },
            { 0b111001011001, Gomoku::ILLEGAL_SCORE },
            { 0b111001011010, Gomoku::ILLEGAL_SCORE },
            { 0b000010010110, Gomoku::ILLEGAL_SCORE },
            { 0b010110010110, Gomoku::ILLEGAL_SCORE },
            { 0b101010010110, Gomoku::ILLEGAL_SCORE },
            { 0b100110010110, Gomoku::ILLEGAL_SCORE },
            { 0b011010010110, Gomoku::ILLEGAL_SCORE },
            { 0b111010010110, Gomoku::ILLEGAL_SCORE },
            { 0b110110010110, Gomoku::ILLEGAL_SCORE },
            { 0b000100010100, Gomoku::ILLEGAL_SCORE },
            { 0b000101000100, Gomoku::ILLEGAL_SCORE }
        }
    },
    {
        Gomoku::WHITE, {
            { 0b001010100000, Gomoku::ILLEGAL_SCORE },
            { 0b000010101000, Gomoku::ILLEGAL_SCORE },
            { 0b110010101000, Gomoku::ILLEGAL_SCORE },
            { 0b010010101000, Gomoku::ILLEGAL_SCORE },
            { 0b100010101000, Gomoku::ILLEGAL_SCORE },
            { 0b001010100011, Gomoku::ILLEGAL_SCORE },
            { 0b001010100001, Gomoku::ILLEGAL_SCORE },
            { 0b001010100010, Gomoku::ILLEGAL_SCORE },
            { 0b011010010000, Gomoku::ILLEGAL_SCORE },
            { 0b011010011010, Gomoku::ILLEGAL_SCORE },
            { 0b011010010101, Gomoku::ILLEGAL_SCORE },
            { 0b011010011001, Gomoku::ILLEGAL_SCORE },
            { 0b011010010110, Gomoku::ILLEGAL_SCORE },
            { 0b011010011011, Gomoku::ILLEGAL_SCORE },
            { 0b011010010111, Gomoku::ILLEGAL_SCORE },
            { 0b000110100100, Gomoku::ILLEGAL_SCORE },
            { 0b100110100110, Gomoku::ILLEGAL_SCORE },
            { 0b100110100101, Gomoku::ILLEGAL_SCORE },
            { 0b010110100101, Gomoku::ILLEGAL_SCORE },
            { 0b010110100110, Gomoku::ILLEGAL_SCORE },
            { 0b100110100111, Gomoku::ILLEGAL_SCORE },
            { 0b010110100111, Gomoku::ILLEGAL_SCORE },
            { 0b110110100110, Gomoku::ILLEGAL_SCORE },
            { 0b110110100101, Gomoku::ILLEGAL_SCORE },
            { 0b000001101001, Gomoku::ILLEGAL_SCORE },
            { 0b101001101001, Gomoku::ILLEGAL_SCORE },
            { 0b010101101001, Gomoku::ILLEGAL_SCORE },
            { 0b011001101001, Gomoku::ILLEGAL_SCORE },
            { 0b100101101001, Gomoku::ILLEGAL_SCORE },
            { 0b110101101001, Gomoku::ILLEGAL_SCORE },
            { 0b111001101001, Gomoku::ILLEGAL_SCORE },
            { 0b001000101000, Gomoku::ILLEGAL_SCORE },
            { 0b001010001000, Gomoku::ILLEGAL_SCORE }
        },
    }
};


const std::array<Gomoku::t_coord, 4> Gomoku::_directions {{
    {0, -1},
    {-1, 0},
    {1, -1},
    {1, 1}
}};

const std::vector<Gomoku::t_coord> Gomoku::_moveset_cells {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
    {1, -1},
    {-1, 1},
    {1, 1},
    {-1, -1},
};

const Gomoku::t_coord Gomoku::_invalid_coord = { -1, -1 };

inline void Gomoku::add_board_piece(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    board[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
}

inline void    Gomoku::remove_board_piece(uint64_t* board, t_coord piece_coord)
{
    board[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
}

void    Gomoku::update_board(uint64_t *board, const t_update_list &update_list)
{
    for (auto &piece : update_list)
    {
        if (piece.type == Gomoku::ADD)
            this->add_board_piece(board, piece.coord, piece.piece);
        if (piece.type == Gomoku::REMOVE)
            this->remove_board_piece(board, piece.coord);
    }
}

void Gomoku::revert_board_update(uint64_t *board, const t_update_list &update_list)
{
    for (auto &piece : update_list)
    {
        if (piece.type == Gomoku::ADD)
            this->remove_board_piece(board, piece.coord);
        if (piece.type == Gomoku::REMOVE)
            this->add_board_piece(board, piece.coord, piece.piece);
    }
}

void Gomoku::print_board(t_piece current_piece)
{
    for (short y = 0; y < this->_board_size; y++)
    {
        for (short x = 0; x < this->_board_size; x++)
        {
            t_coord current_move = {x, y};
            t_piece piece = this->get_piece(this->_board, current_move);
            switch (piece)
            {
                case Gomoku::BLACK:
                    std::cout << "X ";
                    break;
                case Gomoku::WHITE:
                    std::cout << "O ";
                    break;
                case Gomoku::EMPTY:
                    if (this->is_move_valid(current_move, current_piece))
                        std::cout << ". ";
                    else
                        std::cout << "? ";
                    break;
                default:
                    std::cout << "? ";
                    break;
            }
        }
        std::cout << std::endl; 
    }
}

Gomoku::t_player Gomoku::get_player(t_player_type player_type,
                                        t_piece player_color, t_difficulty difficulty)
{
    t_player player;

    memset(&player, 0, sizeof(t_player));
    player.piece = player_color;
    if (player_type == Gomoku::HUMAN)
        player.move = &Gomoku::human_move;
    else if (player_type == Gomoku::AI)
    {
        player.move = &Gomoku::ai_move;
        player.difficulty = difficulty;
    }
    return player;
}

Gomoku::Gomoku(uint8_t board_size, t_difficulty first_difficulty,
    t_difficulty second_difficulty, t_player_type first_player_type, t_player_type second_player_type, t_rule rule)
{
    if (board_size < 5 || board_size > 19)
        throw std::invalid_argument("Board size must be between 5 and 19");
    this->_board_size = board_size;
    this->_board = new uint64_t[board_size]();
    this->_first_player  = get_player(first_player_type, Gomoku::BLACK, first_difficulty);
    this->_second_player = get_player(second_player_type, Gomoku::WHITE, second_difficulty);
    this->_rule = rule;
    this->_depth = 5;
    this->_turn = 0;
    this->_game_over = false;
}

Gomoku::~Gomoku()
{
    delete[] this->_board;
}

inline Gomoku::t_piece Gomoku::get_piece(uint64_t *board, t_coord piece_coord)
{
    if (piece_coord.y < 0 || piece_coord.y >= this->_board_size
            || piece_coord.x < 0 || piece_coord.x >= this->_board_size)
        return (Gomoku::ERROR);
    return (t_piece((board[piece_coord.y] >> (piece_coord.x * 2)) & 0b11));
}

bool    Gomoku::is_inside_square(t_coord piece_coord)
{
    t_coord square_coord;
    uint8_t square_size;

    square_size = (this->_rule == Gomoku::PRO) ? PRO_SIZE : LONG_PRO_SIZE;
    square_coord = GET_BOARD_CENTER() - t_coord{square_size / 2, square_size / 2};
    return (piece_coord.x >= square_coord.x && piece_coord.x < square_coord.x + square_size
            && piece_coord.y >= square_coord.y && piece_coord.y < square_coord.y + square_size);
}

bool    Gomoku::is_move_valid(t_coord piece_coord, t_piece piece)
{
    uint64_t    *board = this->_board;
    int32_t     score  = 0;

    if (this->_rule != Gomoku::STANDARD && this->_turn == 2)
        return (!this->is_inside_square(piece_coord));
    if (this->get_piece(board, piece_coord) != Gomoku::EMPTY)
        return (false);
    this->add_board_piece(board, piece_coord, piece);
    for (auto &dir: Gomoku::_directions)
    {
        score = this->evaluate_dir(board, piece_coord, piece, dir);
        if (score == Gomoku::ILLEGAL_SCORE)
            break;
    }
    this->remove_board_piece(board, piece_coord);
    return (score != Gomoku::ILLEGAL_SCORE);
}

int32_t Gomoku::evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction, bool capture)
{
    int32_t                                 attack_score;
    int32_t                                 defense_score;
    uint16_t                                current_pattern;
    uint16_t                                initial_pattern;
    t_piece                                 current_piece;
    t_coord                                 pattern_position;

    const std::map<uint16_t, t_scores>      &attack_patterns   = Gomoku::_attack_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &defense_patterns  = Gomoku::_defense_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &illegal_patterns  = Gomoku::_illegal_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &capture_patterns  = Gomoku::_capture_patterns.at(piece);

    attack_score = 0;
    defense_score = 0;
    current_pattern = 0;
    pattern_position = piece_coord + direction;
    for (int j = 0; j < 5; j++)
    {
        current_pattern <<= 2;
        current_pattern |= this->get_piece(board, pattern_position);
        pattern_position += direction;
    }
    for (int i = 0; i <= 6; i++)
    {
        current_piece = this->get_piece(board, piece_coord);
        current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
        if (!capture && illegal_patterns.count(current_pattern))
            return (Gomoku::ILLEGAL_SCORE);
        if (!capture && capture_patterns.count(current_pattern & FOUR_MASK))
            return (Gomoku::CAPTURE_SCORE);
        if (attack_patterns.count(current_pattern))
            attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
        if (defense_patterns.count(current_pattern))
            defense_score = std::max(int32_t(defense_patterns.at(current_pattern)), defense_score);
        piece_coord -= direction;
        current_pattern >>= 2;
    }
    return (attack_score + defense_score);
}

int32_t Gomoku::evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    int32_t score = 0;

    for (auto& dir: this->_directions)
        score += this->evaluate_dir(board, piece_coord, piece, dir);
    return (score);
}

int64_t Gomoku::evaluate_board(uint64_t *board, t_piece player_color, t_capture_count capture_count)
{
    int64_t     score;
    t_coord     piece_coord;
    t_piece     piece;
    uint64_t    line;

    score = capture_count.maximizer_count * Gomoku::CAPTURE_SCORE;
    score -= capture_count.minimizer_count * Gomoku::CAPTURE_SCORE;
    for (piece_coord.y = 0; piece_coord.y < this->_board_size; piece_coord.y++)
    {
        line = board[piece_coord.y];
        do {
            if (line == 0)
                break;
            piece_coord.x = (__builtin_ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            piece = this->get_piece(board, piece_coord);
            if (piece == player_color)
                score += this->evaluate_move(board, piece_coord, piece);
            else
                score -= this->evaluate_move(board, piece_coord, piece);
        } while (piece_coord.x < this->_board_size);
    }

    return (score);
}

bool Gomoku::is_winning_move(uint64_t* board, t_piece piece, t_coord move, uint8_t capture_count)
{
    if (capture_count >= MAX_CAPTURE)
        return (true);
    if (this->evaluate_move(board, move, piece) >= Gomoku::WINNING_SCORE)
    {
        t_sorted_updates possible_moves = this->generate_sorted_updates(this->_ai_moveset, this->_board, GET_OPPONENT(piece));

        for (const auto& opp_move : possible_moves)
        {
            this->update_board(this->_board, opp_move.updates);
            if (this->evaluate_move(board, move, piece) < Gomoku::WINNING_SCORE)
            {
                this->revert_board_update(this->_board, opp_move.updates);
                return (false);
            }
            this->revert_board_update(this->_board, opp_move.updates);
        }
        return (true);
    }
    return (false);
}

void Gomoku::extract_captured_stoned(uint64_t *board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece)
{
    t_coord        current_pos;
    t_coord        move_dir;
    uint16_t       current_pattern;

    for (auto& factor: {-1, 1})
    {
        move_dir = dir * factor;
        if (IS_CAPTURE(board, move, move_dir))
        {
            update_list.push_back(t_move_update{move + move_dir, GET_OPPONENT(piece), Gomoku::REMOVE});
            update_list.push_back(t_move_update{move + move_dir * 2, GET_OPPONENT(piece), Gomoku::REMOVE});
        }
    }
}

void Gomoku::print_patterns(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    uint16_t        current_pattern;
    t_coord         pattern_position;

    current_pattern = 0;
    pattern_position = piece_coord + direction;
    std::cout << "direction: " << "( " << direction.x << "," << direction.y << " )" << std::endl;
    for (int j = 0; j < 5; j++)
    {
        current_pattern <<= 2;
        current_pattern |= this->get_piece(board, pattern_position);
        pattern_position += direction;
    }
    for (int i = 0; i < 6; i++)
    {
        current_pattern = (this->get_piece(board, piece_coord) << 10 | current_pattern);
        std::cout << std::bitset<16>(current_pattern) << std::endl;
        current_pattern >>= 2;
        piece_coord -= direction;
    }
}

void Gomoku::generate_scored_update(uint64_t* board, t_coord move, t_piece piece, t_scored_update& scored_update)
{
    int32_t         pattern_eval;
    uint16_t        current_pattern;

    scored_update.move.score = 0;
    this->add_board_piece(board, move, piece);
    for (auto& dir: this->_directions)
    {
        pattern_eval = this->evaluate_dir(board, move, piece, dir);
        if (pattern_eval == Gomoku::ILLEGAL_SCORE)
            break;
        scored_update.move.score += pattern_eval;
        if (pattern_eval == Gomoku::CAPTURE_SCORE)
        {
            this->extract_captured_stoned(board, scored_update.updates, move, dir, piece);
            scored_update.cupture_count++;
        }
    }
    this->remove_board_piece(board, move);
    if (pattern_eval == Gomoku::ILLEGAL_SCORE)
        scored_update.updates.clear();
    else
        scored_update.updates.push_back(t_move_update{move, piece, Gomoku::ADD});
}

Gomoku::t_sorted_updates Gomoku::generate_sorted_updates(t_moveset& moveset, uint64_t* board, t_piece piece)
{
    t_sorted_updates    sorted_updates;
    t_scored_update     scored_move;

    for (const auto& move: moveset)
    {
        scored_move = {0};
        scored_move.move.coord = move;
        this->generate_scored_update(board, move, piece, scored_move);
        if (scored_move.updates.empty())
            continue;
        sorted_updates.insert(scored_move);
    }
    return (sorted_updates);
}


void Gomoku::update_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
{
    t_coord new_move;

    this->update_board(board, update_list);
    for (const auto& updates: update_list)
    {
        if (updates.type == Gomoku::ADD)
        {
            moveset.erase(updates.coord);
            for (auto& factor : Gomoku::_moveset_cells)
            {
                new_move = updates.coord + factor;
                if (this->get_piece(board, new_move) == Gomoku::EMPTY && moveset.count(new_move) == 0)
                    added_moves.insert(new_move);
            }
        }
        if (updates.type == Gomoku::REMOVE)
            added_moves.insert(updates.coord);
    }
    for (const auto& move: added_moves)
        moveset.insert(move);
}

void Gomoku::revert_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
{
    this->revert_board_update(board, update_list);
    for (const auto& move: added_moves)
        moveset.erase(move);
    for (const auto& updates: update_list)
    {
        if (updates.type == Gomoku::REMOVE)
            moveset.erase(updates.coord);
        if (updates.type == Gomoku::ADD)
            moveset.insert(updates.coord);
    }
}

Gomoku::t_scored_move Gomoku::maximizer(t_moveset& moveset,
            uint64_t* board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece)
{
    t_moveset           added_moveset;
    t_scored_move       move_eval;
    t_scored_move       best_eval;
    uint8_t             move_counter;

    if (depth == 0)
        return (t_scored_move{Gomoku::_invalid_coord, this->evaluate_board(board, piece, count)});
    move_counter = 0;
    best_eval = t_scored_move{Gomoku::_invalid_coord, INTMAX_MIN};
    for (auto& update: this->generate_sorted_updates(moveset, board, piece))
    {
        added_moveset.clear();
        count.maximizer_count += update.cupture_count;
        if (update.move.score >= Gomoku::WINNING_SCORE || count.maximizer_count >= MAX_CAPTURE)
            return t_scored_move{update.move.coord, INTMAX_MAX - depth};
        this->update_node_state(board, added_moveset, moveset, update.updates);
        move_eval = this->minimizer(moveset, board, depth - 1, prunner, FLIP_CAPTURE(count), GET_OPPONENT(piece));
        count.maximizer_count -= update.cupture_count;
        this->revert_node_state(board, added_moveset, moveset, update.updates);
        if (move_eval.score >= best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.alpha = std::max(prunner.alpha, best_eval.score);
        if (prunner.beta <= prunner.alpha)
            break;
        if (move_counter++ > 17)
            break;
    }
    return (best_eval);    
}

Gomoku::t_scored_move Gomoku::minimizer
    (t_moveset& moveset, uint64_t* board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece)
{
    t_moveset           added_moveset;
    t_scored_move       move_eval;
    t_scored_move       best_eval;
    uint8_t             move_counter;

    if (depth == 0)
        return t_scored_move{Gomoku::_invalid_coord, -this->evaluate_board(board, piece, count)};
    move_counter = 0;
    best_eval = t_scored_move{Gomoku::_invalid_coord, INTMAX_MAX};
    for (auto& update: this->generate_sorted_updates(moveset, board, piece))
    {
        added_moveset.clear();
        count.maximizer_count += update.cupture_count;
        if (update.move.score >= Gomoku::WINNING_SCORE || count.maximizer_count >= MAX_CAPTURE)
            return t_scored_move{update.move.coord, INTMAX_MIN + depth};
        this->update_node_state(board, added_moveset, moveset, update.updates);
        move_eval = this->maximizer(moveset, board, depth - 1, prunner, FLIP_CAPTURE(count), GET_OPPONENT(piece));
        count.maximizer_count -= update.cupture_count;
        this->revert_node_state(board, added_moveset, moveset, update.updates);
        if (move_eval.score <= best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.beta = std::min(prunner.beta, best_eval.score);
        if (prunner.beta <= prunner.alpha)
            break;
        if (move_counter++ > 17)
            break;
    }
    return (best_eval);
}

Gomoku::t_moveset   Gomoku::generate_rule_moveset(t_piece piece)
{
    t_moveset   moveset;
    t_coord square_coord;
    uint8_t square_size;

    if (this->_rule == Gomoku::STANDARD)
        return (this->_ai_moveset);
    square_size = (this->_rule == Gomoku::PRO) ? PRO_SIZE + 1 : LONG_PRO_SIZE + 1;
    square_coord = GET_BOARD_CENTER() - t_coord{square_size / 2, square_size / 2};
    for (uint8_t x = 0; x < square_size * 4; x++)
    {
        if (x < square_size)
            square_coord.x++;
        else if (x < square_size * 2)
            square_coord.y++;
        else if (x < square_size * 3)
            square_coord.x--;
        else
            square_coord.y--;
        if (this->is_move_valid(square_coord, piece))
            moveset.insert(square_coord);
    }
    return (moveset);
}
Gomoku::t_coord Gomoku::ai_move(t_player& player, t_player &opponent)
{
    t_scored_move   best_move;
    t_moveset&      current_moveset = this->_ai_moveset;

    auto start = std::chrono::steady_clock::now();
    if (_turn == 0)
        best_move.coord = GET_BOARD_CENTER();
    else
    {
        if (_turn == 2)
            current_moveset = this->generate_rule_moveset(player.piece);
        best_move = this->maximizer(current_moveset,
            this->_board, this->_depth,
            t_prunner{INTMAX_MIN, INTMAX_MAX},
            t_capture_count{player.capture_count, opponent.capture_count}, player.piece);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
    return best_move.coord;
}

Gomoku::t_coord Gomoku::human_move(t_player& player, t_player &opponent)
{
    t_coord coord;

    (void)opponent;
    for (;;)
    {
        try
        {
            switch (this->get_game_command())
            {
                case 'S':
                    PRINT_COORD(this->ai_move(player, opponent));
                    std::cout << "END SUGGESTION" << std::endl;
                    break;
                case 'M':
                    std::cin >> coord.x >> coord.y;
                    if (this->is_move_valid(coord, player.piece))
                        return coord;
                    else
                        std::cout << "Illegal move" << std::endl;
                    break;
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Invalid move" << '\n';
        }
        
    }
    return (coord);
}

char Gomoku::get_game_command()
{
    char command;

    try
    {
        std::cin >> command;
    }
    catch(const std::exception& e)
    {
        command = 'N';
    }
    return command;
}


void Gomoku::update_game_state(t_coord current_move, t_player& player)
{
    t_coord             new_move;
    t_scored_update     scored_update{0};

    this->generate_scored_update(this->_board, current_move, player.piece, scored_update);
    this->update_board(this->_board, scored_update.updates);
    for (const auto& updates: scored_update.updates)
    {
        if (updates.type == Gomoku::ADD)
        {
            this->_ai_moveset.erase(updates.coord);
            for (auto& factor : Gomoku::_moveset_cells)
            {
                new_move = updates.coord + factor;
                if (this->get_piece(this->_board, new_move) == Gomoku::EMPTY)
                    this->_ai_moveset.insert(new_move);
            }
        }
        if (updates.type == Gomoku::REMOVE)
            this->_ai_moveset.insert(updates.coord);
    }    
    player.capture_count += scored_update.cupture_count;
    this->_turn++;
}

void Gomoku::make_move(t_player& player, t_player& opponent)
{
    t_coord         current_move;

    current_move  = (this->*player.move)(player, opponent);
    if (current_move == Gomoku::_invalid_coord)
        PRINT_PLAYER_FORFEIT(player.piece);
    else
    {
        PRINT_COORD(current_move);
        this->update_game_state(current_move, player);
        PRINT_CAPTURE_COUNT();
        this->print_board(opponent.piece);
        if (this->is_winning_move(this->_board, player.piece, current_move, player.capture_count))
        {
            PRINT_PLAYER_WIN(player.piece);
            STOP_GAME();
        }
        PRINT_DELINEATION();
    }
}

void Gomoku::start_game()
{
    for (;;)
        if (IS_GAME_OVER() == false)
            this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER());
}

int main(int argc, char **argv)
{
    Gomoku::t_coord new_move;
    Gomoku::t_player_type p1_type;
    Gomoku::t_player_type p2_type;
    Gomoku::t_difficulty p1_diff;
    Gomoku::t_difficulty p2_diff;

    p1_type = Gomoku::HUMAN;
    p2_type = Gomoku::HUMAN;
    p1_diff = Gomoku::EASY;
    p2_diff = Gomoku::EASY;

    for (int i = 1; i < argc; i++)
    {
        // Check player type
        if (!strcmp(argv[i], "--p1_type=human"))
            p1_type = Gomoku::HUMAN;
        else if (!strcmp(argv[i], "--p1_type=ai"))
            p1_type = Gomoku::AI;
        else if (!strcmp(argv[i], "--p2_type=human"))
            p2_type = Gomoku::HUMAN;
        else if (!strcmp(argv[i], "--p2_type=ai"))
            p2_type = Gomoku::AI;

        // Check difficulty
        else if (p1_type == Gomoku::AI)
        {
            if (!strcmp(argv[i], "--p1_diff=easy"))
                p1_diff = Gomoku::EASY;
            else if (!strcmp(argv[i], "--p1_diff=medium"))
                p1_diff = Gomoku::MEDIUM;
            else if (!strcmp(argv[i], "--p1_diff=hard"))
                p1_diff = Gomoku::HARD;
        }
        else if (p2_type == Gomoku::AI)
        {
            if (!strcmp(argv[i], "--p2_diff=easy"))
                p2_diff = Gomoku::EASY;
            else if (!strcmp(argv[i], "--p2_diff=medium"))
                p2_diff = Gomoku::MEDIUM;
            else if (!strcmp(argv[i], "--p2_diff=hard"))
                p2_diff = Gomoku::HARD;
        }
    }

    // Gomoku  game(19, Gomoku::EASY, Gomoku::EASY, Gomoku::AI, Gomoku::AI, Gomoku::PRO);

    Gomoku game(19, p1_diff, p2_diff, p1_type, p2_type, Gomoku::PRO);

    game.start_game();

    return (0);
}