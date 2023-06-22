#include "Gomoku.hpp"


const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            {0b010101010100, Gomoku::FIVE_SCORE},
            {0b010101010110, Gomoku::FIVE_SCORE},
            {0b010101010111, Gomoku::FIVE_SCORE},
            {0b000101010101, Gomoku::FIVE_SCORE},
            {0b100101010101, Gomoku::FIVE_SCORE},
            {0b110101010101, Gomoku::FIVE_SCORE},
            {0b000101010100, Gomoku::OPEN_FOUR_SCORE},
            {0b110101010100, Gomoku::FOUR_SCORE},
            {0b100101010100, Gomoku::FOUR_SCORE},
            {0b000101010111, Gomoku::FOUR_SCORE},
            {0b000101010110, Gomoku::FOUR_SCORE},
            {0b000101010000, Gomoku::OPEN_THREE_SCORE},
            {0b000101010011, Gomoku::OPEN_THREE_SCORE},
            {0b000101010010, Gomoku::OPEN_THREE_SCORE},
            {0b000101010001, Gomoku::OPEN_THREE_SCORE},
            {0b000001010100, Gomoku::OPEN_THREE_SCORE},
            {0b110001010100, Gomoku::OPEN_THREE_SCORE},
            {0b100001010100, Gomoku::OPEN_THREE_SCORE},
            {0b010001010100, Gomoku::OPEN_THREE_SCORE},
            {0b000100010100, Gomoku::OPEN_THREE_SCORE},
            {0b000101000100, Gomoku::OPEN_THREE_SCORE},
            {0b000001010110, Gomoku::THREE_SCORE},
            {0b000001010111, Gomoku::THREE_SCORE},
            {0b100101010000, Gomoku::THREE_SCORE},
            {0b110101010000, Gomoku::THREE_SCORE},
            {0b000101000000, Gomoku::OPEN_TWO_SCORE},
            {0b000101000010, Gomoku::OPEN_TWO_SCORE},
            {0b000101000011, Gomoku::OPEN_TWO_SCORE},
            {0b000001010000, Gomoku::OPEN_TWO_SCORE},
            {0b000001010010, Gomoku::OPEN_TWO_SCORE},
            {0b000001010011, Gomoku::OPEN_TWO_SCORE},
            {0b000001010000, Gomoku::OPEN_TWO_SCORE},
            {0b100001010000, Gomoku::OPEN_TWO_SCORE},
            {0b110001010000, Gomoku::OPEN_TWO_SCORE},
            {0b000000010100, Gomoku::OPEN_TWO_SCORE},
            {0b100000010100, Gomoku::OPEN_TWO_SCORE},
            {0b110000010100, Gomoku::OPEN_TWO_SCORE},
            {0b000000010111, Gomoku::TWO_SCORE},
            {0b000001000110, Gomoku::TWO_SCORE},
            {0b100100010000, Gomoku::TWO_SCORE},
            {0b110101000000, Gomoku::TWO_SCORE},
            
        }
    },
    {
        Gomoku::WHITE, {
            {0b101010101000, Gomoku::FIVE_SCORE},
            {0b101010101001, Gomoku::FIVE_SCORE},
            {0b101010101011, Gomoku::FIVE_SCORE},
            {0b001010101010, Gomoku::FIVE_SCORE},
            {0b011010101010, Gomoku::FIVE_SCORE},
            {0b111010101010, Gomoku::FIVE_SCORE},
            {0b001010101000, Gomoku::OPEN_FOUR_SCORE},
            {0b111010101000, Gomoku::FOUR_SCORE},
            {0b011010101000, Gomoku::FOUR_SCORE},
            {0b001010101011, Gomoku::FOUR_SCORE},
            {0b001010101001, Gomoku::FOUR_SCORE},
            {0b001010100000, Gomoku::OPEN_THREE_SCORE},
            {0b001010100011, Gomoku::OPEN_THREE_SCORE},
            {0b001010100001, Gomoku::OPEN_THREE_SCORE},
            {0b001010100010, Gomoku::OPEN_THREE_SCORE},
            {0b000010101000, Gomoku::OPEN_THREE_SCORE},
            {0b110010101000, Gomoku::OPEN_THREE_SCORE},
            {0b010010101000, Gomoku::OPEN_THREE_SCORE},
            {0b100010101000, Gomoku::OPEN_THREE_SCORE},
            {0b001000101000, Gomoku::OPEN_THREE_SCORE},
            {0b001010001000, Gomoku::OPEN_THREE_SCORE},
            {0b000010101001, Gomoku::THREE_SCORE},
            {0b000010101011, Gomoku::THREE_SCORE},
            {0b011010100000, Gomoku::THREE_SCORE},
            {0b111010100000, Gomoku::THREE_SCORE},
            {0b001010000000, Gomoku::OPEN_TWO_SCORE},
            {0b001010000001, Gomoku::OPEN_TWO_SCORE},
            {0b001010000011, Gomoku::OPEN_TWO_SCORE},
            {0b000010100000, Gomoku::OPEN_TWO_SCORE},
            {0b000010100001, Gomoku::OPEN_TWO_SCORE},
            {0b000010100011, Gomoku::OPEN_TWO_SCORE},
            {0b000010100000, Gomoku::OPEN_TWO_SCORE},
            {0b010010100000, Gomoku::OPEN_TWO_SCORE},
            {0b110010100000, Gomoku::OPEN_TWO_SCORE},
            {0b000000101000, Gomoku::OPEN_TWO_SCORE},
            {0b010000101000, Gomoku::OPEN_TWO_SCORE},
            {0b110000101000, Gomoku::OPEN_TWO_SCORE},
            {0b000010001001, Gomoku::TWO_SCORE},
            {0b000000101011, Gomoku::TWO_SCORE},
            {0b0110001000000, Gomoku::TWO_SCORE},
            {0b111010000000, Gomoku::TWO_SCORE},
        },
    }
};

const Gomoku::t_patterns Gomoku::_illegal_patterns
{
    {
        Gomoku::BLACK, {
            {0b000101010000, Gomoku::ILLEGAL_SCORE},
            {0b000101010011, Gomoku::ILLEGAL_SCORE},
            {0b000101010010, Gomoku::ILLEGAL_SCORE},
            {0b000101010001, Gomoku::ILLEGAL_SCORE},
            {0b000001010100, Gomoku::ILLEGAL_SCORE},
            {0b110001010100, Gomoku::ILLEGAL_SCORE},
            {0b100001010100, Gomoku::ILLEGAL_SCORE},
            {0b010001010100, Gomoku::ILLEGAL_SCORE},
            {0b000100010100, Gomoku::ILLEGAL_SCORE},
            {0b000101000100, Gomoku::ILLEGAL_SCORE},
            {0b100101100000, Gomoku::ILLEGAL_SCORE},
            {0b100101100011, Gomoku::ILLEGAL_SCORE},
            {0b100101100010, Gomoku::ILLEGAL_SCORE},
            {0b100101100001, Gomoku::ILLEGAL_SCORE},
            {0b100101101000, Gomoku::ILLEGAL_SCORE},
            {0b100101101010, Gomoku::ILLEGAL_SCORE},
            {0b100101101011, Gomoku::ILLEGAL_SCORE},
            {0b100101101001, Gomoku::ILLEGAL_SCORE},
            {0b100101100100, Gomoku::ILLEGAL_SCORE},
            {0b100101100101, Gomoku::ILLEGAL_SCORE},
            {0b100101100111, Gomoku::ILLEGAL_SCORE},
            {0b100101100110, Gomoku::ILLEGAL_SCORE},
        }
    },
    {
        Gomoku::WHITE, {
            {0b001010100000, Gomoku::ILLEGAL_SCORE},
            {0b001010100011, Gomoku::ILLEGAL_SCORE},
            {0b001010100001, Gomoku::ILLEGAL_SCORE},
            {0b001010100010, Gomoku::ILLEGAL_SCORE},
            {0b000010101000, Gomoku::ILLEGAL_SCORE},
            {0b110010101000, Gomoku::ILLEGAL_SCORE},
            {0b010010101000, Gomoku::ILLEGAL_SCORE},
            {0b100010101000, Gomoku::ILLEGAL_SCORE},
            {0b001000101000, Gomoku::ILLEGAL_SCORE},
            {0b001010001000, Gomoku::ILLEGAL_SCORE},
            {0b011010010000, Gomoku::ILLEGAL_SCORE},
            {0b011010010011, Gomoku::ILLEGAL_SCORE},
            {0b011010010001, Gomoku::ILLEGAL_SCORE},
            {0b011010010010, Gomoku::ILLEGAL_SCORE},
            {0b011010010100, Gomoku::ILLEGAL_SCORE},
            {0b011010010101, Gomoku::ILLEGAL_SCORE},
            {0b011010010111, Gomoku::ILLEGAL_SCORE},
            {0b011010010110, Gomoku::ILLEGAL_SCORE},
            {0b011010011000, Gomoku::ILLEGAL_SCORE},
            {0b011010011010, Gomoku::ILLEGAL_SCORE},
            {0b011010011011, Gomoku::ILLEGAL_SCORE},
            {0b011010011001, Gomoku::ILLEGAL_SCORE},
        },
    }
};

const Gomoku::t_patterns Gomoku::_defense_patterns = {
    {
        Gomoku::BLACK, {
            { 0b011010101011, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011010101001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b111001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b001001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010011010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011010011010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b111010011010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b001010011010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011010100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b111010100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b001010100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b110110101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100110101000, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100110101011, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100110101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100110101001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b111001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101001101000, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101001101011, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101001101010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101001101001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010011000, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010011011, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010011010, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010100100, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010100111, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b101010100101, Gomoku::FIVE_BLOCK_SCORE},

// Block Free threes ----- generated by capture ---
            { 0b011010100000, Gomoku::OPEN_BLOCK_SCORE},
            { 0b001010100100, Gomoku::OPEN_BLOCK_SCORE},
            { 0b000010101001, Gomoku::OPEN_BLOCK_SCORE},
            { 0b000110101000, Gomoku::OPEN_BLOCK_SCORE},
            { 0b011010100011, Gomoku::OPEN_BLOCK_SCORE},
            { 0b011010100001, Gomoku::OPEN_BLOCK_SCORE},
            { 0b010010101001, Gomoku::OPEN_BLOCK_SCORE},
            { 0b110010101001, Gomoku::OPEN_BLOCK_SCORE},
            { 0b001010011000, Gomoku::OPEN_BLOCK_SCORE},

// ------------------------------------------------        

        }
    },
    {
        Gomoku::WHITE, {
            { 0b100101010111, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100101010110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b110110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b000110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101100101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100101100101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b110101100101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b000101100101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b100101011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b110101011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b000101011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b111001010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011001010100, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011001010111, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011001010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b011001010110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b110110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010110010100, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010110010111, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010110010101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010110010110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101100100, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101100111, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101100101, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101100110, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101011000, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101011011, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101011001, Gomoku::FIVE_BLOCK_SCORE},
            { 0b010101011010, Gomoku::FIVE_BLOCK_SCORE},

// Block Free threes ----- generated by capture ---
            { 0b100101010000, Gomoku::OPEN_BLOCK_SCORE},
            { 0b000101011000, Gomoku::OPEN_BLOCK_SCORE},
            { 0b000001010110, Gomoku::OPEN_BLOCK_SCORE},
            { 0b001001010100, Gomoku::OPEN_BLOCK_SCORE},
            { 0b100101010011, Gomoku::OPEN_BLOCK_SCORE},
            { 0b100101010010, Gomoku::OPEN_BLOCK_SCORE},
            { 0b100001010110, Gomoku::OPEN_BLOCK_SCORE},
            { 0b110001010110, Gomoku::OPEN_BLOCK_SCORE},
            { 0b000101100100, Gomoku::OPEN_BLOCK_SCORE},
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

void    Gomoku::update_board(t_board &board, const t_update_list &update_list)
{
    for (auto &piece : update_list)
    {
        if (piece.type == Gomoku::ADD)
            board.add_piece(piece.coord, piece.piece);
        if (piece.type == Gomoku::REMOVE)
            board.remove_piece(piece.coord);
    }
}

void Gomoku::revert_board_update(t_board &board, const t_update_list &update_list)
{
    for (auto &piece : update_list)
    {
        if (piece.type == Gomoku::ADD)
            board.remove_piece(piece.coord);
        if (piece.type == Gomoku::REMOVE)
            board.add_piece(piece.coord, piece.piece);
    }
}

void Gomoku::print_board(t_board &board, t_piece current_piece)
{
    for (short y = 0; y < board.size; y++)
    {
        for (short x = 0; x < board.size; x++)
        {
            t_coord current_move = {x, y};
            t_piece piece = board.get_piece(current_move);
            switch (piece)
            {
                case Gomoku::BLACK:
                    std::cout << "X ";
                    break;
                case Gomoku::WHITE:
                    std::cout << "O ";
                    break;
                case Gomoku::EMPTY:
                    if (this->is_move_valid(this->_board, current_move, current_piece))
                    {
                        if (this->_ai_moveset.count(current_move))
                            std::cout << "\033[1;31m. \033[0m";
                        else
                            std::cout << ". ";
                    }
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

int32_t Gomoku::evaluate_move(t_board &board, t_coord piece_coord, t_piece piece)
{
    int32_t score = 0;

    for (auto& dir: this->_directions)
        score += this->evaluate_dir(board, piece_coord, piece, dir);
    return (score);
}

Gomoku::Gomoku(uint8_t board_size, t_difficulty first_difficulty,
    t_difficulty second_difficulty, t_player_type first_player_type, t_player_type second_player_type, t_rule rule): _board(board_size)
{
    if (board_size != 15 && board_size != 19)
        throw std::invalid_argument("Board size must be between 15 or 19");
    // this->_board = t_board{board_size};
    this->_first_player  = get_player(first_player_type, Gomoku::BLACK, first_difficulty);
    this->_second_player = get_player(second_player_type, Gomoku::WHITE, second_difficulty);
    this->_rule = rule;
    this->_depth = 5;
    this->_game_over = false;
    this->_turn = 0;
}

Gomoku::~Gomoku()
{
}

bool    Gomoku::is_inside_square(t_board& board, t_coord piece_coord)
{
    t_coord square_coord;
    uint8_t square_size;

    square_size = (this->_rule == Gomoku::PRO) ? PRO_SIZE : LONG_PRO_SIZE;
    square_coord = GET_BOARD_CENTER(board) - t_coord{square_size / 2, square_size / 2};
    return (piece_coord.x >= square_coord.x && piece_coord.x < square_coord.x + square_size
            && piece_coord.y >= square_coord.y && piece_coord.y < square_coord.y + square_size);
}

bool    Gomoku::is_move_valid(t_board& board, t_coord piece_coord, t_piece piece)
{
    int32_t     score  = 0;

    if (this->_rule != Gomoku::STANDARD && this->_turn == 2)
        return (!this->is_inside_square(board, piece_coord));
    if (board.get_piece(piece_coord) != Gomoku::EMPTY)
        return (false);
    board.add_piece(piece_coord, piece);
    for (auto &dir: Gomoku::_directions)
    {
        score = this->evaluate_dir(board, piece_coord, piece, dir);
        if (score == Gomoku::ILLEGAL_SCORE)
            break;
    }
    board.remove_piece(piece_coord);
    return (score != Gomoku::ILLEGAL_SCORE);
}

int32_t Gomoku::evaluate_dir(t_board &board, t_coord piece_coord, t_piece piece, t_coord direction, bool board_eval)
{
    int32_t                                 attack_score;
    int32_t                                 defense_score;
    uint16_t                                current_pattern;
    uint16_t                                initial_pattern;
    t_piece                                 current_piece;
    t_coord                                 pattern_position;

    const std::map<uint16_t, t_scores>      &attack_patterns         = Gomoku::_attack_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &capture_patterns        = Gomoku::_capture_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &illegal_patterns        = Gomoku::_illegal_patterns.at(piece);
    const std::map<uint16_t, t_scores>      &defense_patterns        = Gomoku::_defense_patterns.at(piece);

    attack_score = 0;
    defense_score = 0;
    current_pattern = 0;
    pattern_position = piece_coord + direction;
    for (int j = 0; j < 5; j++)
    {
        current_pattern <<= 2;
        current_pattern |= board.get_piece(pattern_position);
        pattern_position += direction;
    }
    for (int i = 0; i < 6; i++)
    {
        if (current_pattern == Gomoku::ERROR)
            break;
        current_piece = board.get_piece(piece_coord);
        current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
        if (board_eval == false && illegal_patterns.count(current_pattern))
            return (Gomoku::ILLEGAL_SCORE);
        if (capture_patterns.count(current_pattern >> 4))
            return (Gomoku::CAPTURE_SCORE);
        if (attack_patterns.count(current_pattern))
            attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
        if (board_eval == false && defense_patterns.count(current_pattern))
            defense_score = std::max(int32_t(defense_patterns.at(current_pattern)), defense_score);   
        piece_coord -= direction;
        current_pattern >>= 2;
    }
    return (attack_score + defense_score);
}

int64_t Gomoku::evaluate_board(t_board &board, t_piece player_color, t_capture_count capture_count)
{
    int64_t     score;
    t_coord     piece_coord;
    t_piece     piece;
    uint64_t    line;

    score = capture_count.maximizer_count * Gomoku::CAPTURE_SCORE;
    score -= capture_count.minimizer_count * Gomoku::CAPTURE_SCORE;
    for (piece_coord.y = 0; piece_coord.y < board.size; piece_coord.y++)
    {
        line = board.data[piece_coord.y];
        do {
            if (line == 0)
                break;
            piece_coord.x = (__builtin_ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            piece = board.get_piece(piece_coord);
            for (auto &dir: Gomoku::_directions)
            {
                if (piece == player_color)
                    score += 1.4 * this->evaluate_dir(board, piece_coord, player_color, dir, true);
                else if (piece == GET_OPPONENT(player_color))
                    score -= this->evaluate_dir(board, piece_coord, player_color, dir, true);
            }
        } while (piece_coord.x < board.size);
    }

    return (score);
}
int64_t Gomoku::evaluate_moveset(t_moveset& moveset, t_board &board, t_piece player_color, t_capture_count capture_count)
{
    int64_t       score = 0;
    int32_t       move_score = 0;
    int32_t       pattern_score = 0;
    t_update_list captured_stones;
    
    score += capture_count.maximizer_count * Gomoku::CAPTURE_SCORE;
    score -= capture_count.minimizer_count * Gomoku::CAPTURE_SCORE;
    for (const auto& move : moveset)
    {
        for (const auto& piece: {Gomoku::WHITE, Gomoku::BLACK})
        {
            board.add_piece(move, piece);
            for (auto& dir: this->_directions)
            {
                pattern_score = this->evaluate_dir(board, move, piece, dir, false);
                if (move_score == Gomoku::ILLEGAL_SCORE)
                {
                    move_score = 0;
                    break;
                }
                if (pattern_score == Gomoku::CAPTURE_SCORE)
                {
                    this->extract_captured_stoned(board, captured_stones, move, dir, piece);
                    move_score += (captured_stones.size() / 2) * Gomoku::CAPTURE_SCORE;
                    this->update_board(board, captured_stones);
                    move_score += this->evaluate_dir(board, move, piece, dir, true);
                    this->revert_board_update(board, captured_stones);
                }
                else
                    move_score += pattern_score;
            }
            if (piece == player_color)
                score += 1.4 * move_score;
            else
                score -= move_score;
            board.remove_piece(move);
        }
    }
    return (score);
}

bool Gomoku::is_winning_move(t_board &board, t_moveset &moveset, t_piece piece, t_coord move, uint8_t capture_count)
{
    t_sorted_updates possible_moves;

    for (const auto& dir: _directions)
    {
        if (this->evaluate_dir(board, move, piece, dir) >= Gomoku::FIVE_SCORE)
        {
            possible_moves = this->generate_sorted_updates(moveset, board, GET_OPPONENT(piece));
            for (const auto& opp_move : possible_moves)
            {
                this->update_board(board, opp_move.updates);
                if (this->evaluate_dir(board, move, piece, dir) < Gomoku::FIVE_SCORE)
                {
                    this->revert_board_update(board, opp_move.updates);
                    return (false);
                }
                this->revert_board_update(board, opp_move.updates);
            }
            return (true);
        }
    }
    if (capture_count >= MAX_CAPTURE)
        return (true);
    return (false);
}

void Gomoku::extract_captured_stoned(t_board &board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece)
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

void Gomoku::generate_scored_update(t_board &board, t_coord move, t_piece piece, t_scored_update& scored_update)
{
    int32_t         pattern_eval;
    uint16_t        current_pattern;

    scored_update.move.score = 0;
    board.add_piece(move, piece);
    for (auto& dir: this->_directions)
    {
        pattern_eval = this->evaluate_dir(board, move, piece, dir);
        if (pattern_eval == Gomoku::ILLEGAL_SCORE)
            break;
        if (pattern_eval == Gomoku::CAPTURE_SCORE)
        {
            this->extract_captured_stoned(board, scored_update.updates, move, dir, piece);
            scored_update.cupture_count++;
        }
        if (pattern_eval >= Gomoku::FIVE_SCORE)
            scored_update.move.winning = true;
        scored_update.move.score += pattern_eval;
    }
    board.remove_piece(move);
    if (pattern_eval == Gomoku::ILLEGAL_SCORE)
        scored_update.updates.clear();
    else
        scored_update.updates.push_back(t_move_update{move, piece, Gomoku::ADD});
}

Gomoku::t_sorted_updates Gomoku::generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece)
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


void Gomoku::update_node_state(t_board &board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
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
                if (board.get_piece(new_move) == Gomoku::EMPTY && moveset.count(new_move) == 0)
                    added_moves.insert(new_move);
            }
        }
        if (updates.type == Gomoku::REMOVE)
            added_moves.insert(updates.coord);
    }
    for (const auto& move: added_moves)
        moveset.insert(move);
}

void Gomoku::revert_node_state(t_board &board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
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

Gomoku::t_scored_move Gomoku::negascout(t_moveset& moveset,
            t_board &board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece)
{
    t_moveset           added_moveset;
    t_scored_move       move_eval;
    t_scored_move       best_eval;
    uint8_t             move_counter;


    if (depth == 0)
        return (t_scored_move{Gomoku::_invalid_coord, this->evaluate_board(board, piece, count)});
    move_counter = 0;
    best_eval = t_scored_move{Gomoku::_invalid_coord, -INTMAX_MAX};
    for (const auto& update: this->generate_sorted_updates(moveset, board, piece))
    {
        added_moveset.clear();
        count.maximizer_count += update.cupture_count;
        if (update.move.winning || count.maximizer_count >= MAX_CAPTURE)
            if (is_winning_move(board, moveset, piece, update.move.coord, count.maximizer_count))
                return t_scored_move{update.move.coord, INTMAX_MAX - depth};
        this->update_node_state(board, added_moveset, moveset, update.updates);
        if (move_counter == 0)
            move_eval = -this->negascout(moveset, board, depth - 1, FLIP_PRUNNER(prunner), FLIP_CAPTURE(count), GET_OPPONENT(piece));
        else
        {
            move_eval = -this->negascout(moveset, board, depth - 1, SW_PRUNNER(prunner), FLIP_CAPTURE(count), GET_OPPONENT(piece));
            if (prunner.alpha < move_eval.score  && move_eval.score < prunner.beta)
                move_eval = -this->negascout(moveset, board, depth - 1, t_prunner{-prunner.beta, -move_eval.score}, FLIP_CAPTURE(count), GET_OPPONENT(piece));
        }
        count.maximizer_count -= update.cupture_count;
        this->revert_node_state(board, added_moveset, moveset, update.updates);
        if (move_eval.score > best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.alpha = std::max(prunner.alpha, best_eval.score);
        if (prunner.alpha >= prunner.beta)
            break;
        move_counter++;
    }
    return (best_eval);    
}

Gomoku::t_moveset   Gomoku::generate_rule_moveset(t_piece piece, t_board& board)
{
    t_moveset   moveset;
    t_coord square_coord;
    uint8_t square_size;

    square_size = (this->_rule == Gomoku::PRO) ? PRO_SIZE + 1 : LONG_PRO_SIZE + 1;
    square_coord = GET_BOARD_CENTER(board) - t_coord{square_size / 2, square_size / 2};
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
        if (this->is_move_valid(board, square_coord, piece))
            moveset.insert(square_coord);
    }
    return (moveset);
}

Gomoku::t_coord Gomoku::iterative_depth_search(t_moveset& moveset,
            t_board &board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece)
{
    auto start = std::chrono::steady_clock::now();
    t_scored_move best_move;

    for (uint8_t depth = 1; depth <= this->_depth; depth++)
    {
        auto end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= 500)
            break;
        best_move = this->negascout(moveset, this->_board, depth, INITIAL_PRUNNER, count, piece);
    }
    return (best_move.coord);
}

Gomoku::t_coord Gomoku::ai_move(t_player& player, t_player &opponent)
{
    t_coord         best_move;
    t_moveset       current_moveset;

    auto start = std::chrono::steady_clock::now();
    if (_turn == 0)
        best_move = GET_BOARD_CENTER(this->_board);
    else
    {
        if (_turn == 2 && this->_rule != Gomoku::STANDARD)
        {
            current_moveset = this->generate_rule_moveset(player.piece, this->_board);
            best_move = this->iterative_depth_search(current_moveset,
                this->_board, this->_depth,
                t_prunner{-INTMAX_MAX, INTMAX_MAX},
                t_capture_count{player.capture_count, opponent.capture_count}, player.piece);
        }
        else
            best_move = this->iterative_depth_search(this->_ai_moveset,
                this->_board, this->_depth,
                t_prunner{-INTMAX_MAX, INTMAX_MAX},
                t_capture_count{player.capture_count, opponent.capture_count}, player.piece);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
    return best_move;
}

Gomoku::t_coord Gomoku::human_move(t_player& player, t_player &opponent)
{
    t_coord coord;

    (void)opponent;
    for (;;)
    {
        try
        {
            if (this->_turn == 0  && this->_rule != Gomoku::STANDARD)
                return GET_BOARD_CENTER(this->_board);
            switch (this->get_game_command())
            {
                case 'S':
                    PRINT_COORD(this->ai_move(player, opponent));
                    std::cout << "END SUGGESTION" << std::endl;
                    break;
                case 'M':
                    std::cin >> coord.x >> coord.y;
                    if (this->is_move_valid(this->_board, coord, player.piece))
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


void Gomoku::update_game_state(t_board& board, t_player& player, t_coord current_move)
{
    t_coord             new_move;
    t_scored_update     scored_update{0};

    this->generate_scored_update(board, current_move, player.piece, scored_update);
    this->update_board(board, scored_update.updates);
    for (const auto& updates: scored_update.updates)
    {
        if (updates.type == Gomoku::ADD)
        {
            this->_ai_moveset.erase(updates.coord);
            for (const auto& factor : Gomoku::_moveset_cells)
            {
                new_move = updates.coord + factor;
                if (board.get_piece(new_move) == Gomoku::EMPTY)
                    this->_ai_moveset.insert(new_move);
            }
        }
        if (updates.type == Gomoku::REMOVE)
            this->_ai_moveset.insert(updates.coord);
    }    
    player.capture_count += scored_update.cupture_count;
    this->_turn++;
}

Gomoku::t_sequence Gomoku::extract_winning_sequence(t_board &board, t_piece piece, t_coord start_coord)
{
    t_sequence  sequence;

    for (const auto& dir: Gomoku::_directions)
    {
        if (this->evaluate_dir(board, start_coord, piece, dir) == Gomoku::FIVE_SCORE)
        {
            sequence.push_back(start_coord);
            for(t_coord new_coord = start_coord + dir; board.get_piece(new_coord) == piece; new_coord += dir)
                sequence.push_back(new_coord);
            for(t_coord new_coord = start_coord - dir; board.get_piece(new_coord) == piece; new_coord -= dir)
                sequence.push_back(new_coord);
        }
    }
    return (sequence);
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
        this->update_game_state(this->_board, player, current_move);
        PRINT_CAPTURE_COUNT();
        this->print_board(this->_board, opponent.piece);
        if (this->is_winning_move(this->_board, this->_ai_moveset, player.piece, current_move, player.capture_count))
        {
            PRINT_PLAYER_WIN(player.piece);
            for (const auto& coord: this->extract_winning_sequence(this->_board, player.piece, current_move))
                PRINT_COORD(coord);
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

    Gomoku game(19, p1_diff, p2_diff, p1_type, p2_type, Gomoku::PRO);
    // Gomoku game(19, p1_diff, p2_diff, Gomoku::AI, Gomoku::AI, Gomoku::PRO);

    game.start_game();

    return (0);
}