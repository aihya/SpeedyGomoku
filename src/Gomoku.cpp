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
            {0b100101100010, Gomoku::ILLEGAL_SCORE},
            {0b100101100011, Gomoku::ILLEGAL_SCORE},
            {0b100101100001, Gomoku::ILLEGAL_SCORE},
            {0b100101101000, Gomoku::ILLEGAL_SCORE},
            {0b100101101010, Gomoku::ILLEGAL_SCORE},
            {0b100101101011, Gomoku::ILLEGAL_SCORE},
            {0b100101101001, Gomoku::ILLEGAL_SCORE},
            {0b100101101100, Gomoku::ILLEGAL_SCORE},
            {0b100101101110, Gomoku::ILLEGAL_SCORE},
            {0b100101101111, Gomoku::ILLEGAL_SCORE},
            {0b100101101101, Gomoku::ILLEGAL_SCORE},
            {0b100101100100, Gomoku::ILLEGAL_SCORE},
            {0b100101100110, Gomoku::ILLEGAL_SCORE},
            {0b100101100111, Gomoku::ILLEGAL_SCORE},
            {0b100101100101, Gomoku::ILLEGAL_SCORE},
            {0b000010010110, Gomoku::ILLEGAL_SCORE},
            {0b001010010110, Gomoku::ILLEGAL_SCORE},
            {0b001110010110, Gomoku::ILLEGAL_SCORE},
            {0b000110010110, Gomoku::ILLEGAL_SCORE},
            {0b100010010110, Gomoku::ILLEGAL_SCORE},
            {0b101010010110, Gomoku::ILLEGAL_SCORE},
            {0b101110010110, Gomoku::ILLEGAL_SCORE},
            {0b100110010110, Gomoku::ILLEGAL_SCORE},
            {0b110010010110, Gomoku::ILLEGAL_SCORE},
            {0b111010010110, Gomoku::ILLEGAL_SCORE},
            {0b111110010110, Gomoku::ILLEGAL_SCORE},
            {0b110110010110, Gomoku::ILLEGAL_SCORE},
            {0b010010010110, Gomoku::ILLEGAL_SCORE},
            {0b011010010110, Gomoku::ILLEGAL_SCORE},
            {0b011110010110, Gomoku::ILLEGAL_SCORE},
            {0b010110010110, Gomoku::ILLEGAL_SCORE},
        }
    },
    {
        Gomoku::WHITE, {
            { 0b001010100000, Gomoku::ILLEGAL_SCORE},
            { 0b001010100011, Gomoku::ILLEGAL_SCORE},
            { 0b001010100001, Gomoku::ILLEGAL_SCORE},
            { 0b001010100010, Gomoku::ILLEGAL_SCORE},
            { 0b000010101000, Gomoku::ILLEGAL_SCORE},
            { 0b110010101000, Gomoku::ILLEGAL_SCORE},
            { 0b010010101000, Gomoku::ILLEGAL_SCORE},
            { 0b100010101000, Gomoku::ILLEGAL_SCORE},
            { 0b001000101000, Gomoku::ILLEGAL_SCORE},
            { 0b001010001000, Gomoku::ILLEGAL_SCORE},
            { 0b011010010000, Gomoku::ILLEGAL_SCORE},
            { 0b011010010010, Gomoku::ILLEGAL_SCORE},
            { 0b011010010011, Gomoku::ILLEGAL_SCORE},
            { 0b011010010001, Gomoku::ILLEGAL_SCORE},
            { 0b011010011000, Gomoku::ILLEGAL_SCORE},
            { 0b011010011010, Gomoku::ILLEGAL_SCORE},
            { 0b011010011011, Gomoku::ILLEGAL_SCORE},
            { 0b011010011001, Gomoku::ILLEGAL_SCORE},
            { 0b011010011100, Gomoku::ILLEGAL_SCORE},
            { 0b011010011110, Gomoku::ILLEGAL_SCORE},
            { 0b011010011111, Gomoku::ILLEGAL_SCORE},
            { 0b011010011101, Gomoku::ILLEGAL_SCORE},
            { 0b011010010100, Gomoku::ILLEGAL_SCORE},
            { 0b011010010110, Gomoku::ILLEGAL_SCORE},
            { 0b011010010111, Gomoku::ILLEGAL_SCORE},
            { 0b011010010101, Gomoku::ILLEGAL_SCORE},
            { 0b000001101001, Gomoku::ILLEGAL_SCORE},
            { 0b001001101001, Gomoku::ILLEGAL_SCORE},
            { 0b001101101001, Gomoku::ILLEGAL_SCORE},
            { 0b000101101001, Gomoku::ILLEGAL_SCORE},
            { 0b100001101001, Gomoku::ILLEGAL_SCORE},
            { 0b101001101001, Gomoku::ILLEGAL_SCORE},
            { 0b101101101001, Gomoku::ILLEGAL_SCORE},
            { 0b100101101001, Gomoku::ILLEGAL_SCORE},
            { 0b110001101001, Gomoku::ILLEGAL_SCORE},
            { 0b111001101001, Gomoku::ILLEGAL_SCORE},
            { 0b111101101001, Gomoku::ILLEGAL_SCORE},
            { 0b110101101001, Gomoku::ILLEGAL_SCORE},
            { 0b010001101001, Gomoku::ILLEGAL_SCORE},
            { 0b011001101001, Gomoku::ILLEGAL_SCORE},
            { 0b011101101001, Gomoku::ILLEGAL_SCORE},
            { 0b010101101001, Gomoku::ILLEGAL_SCORE},
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
            { 0b011010010000, Gomoku::CAPTURE_SCORE },
            { 0b011010010010, Gomoku::CAPTURE_SCORE },
            { 0b011010010011, Gomoku::CAPTURE_SCORE },
            { 0b011010010001, Gomoku::CAPTURE_SCORE },
            { 0b011010011000, Gomoku::CAPTURE_SCORE },
            { 0b011010011010, Gomoku::CAPTURE_SCORE },
            { 0b011010011011, Gomoku::CAPTURE_SCORE },
            { 0b011010011001, Gomoku::CAPTURE_SCORE },
            { 0b011010011100, Gomoku::CAPTURE_SCORE },
            { 0b011010011110, Gomoku::CAPTURE_SCORE },
            { 0b011010011111, Gomoku::CAPTURE_SCORE },
            { 0b011010011101, Gomoku::CAPTURE_SCORE },
            { 0b011010010100, Gomoku::CAPTURE_SCORE },
            { 0b011010010110, Gomoku::CAPTURE_SCORE },
            { 0b011010010111, Gomoku::CAPTURE_SCORE },
            { 0b011010010101, Gomoku::CAPTURE_SCORE },
            { 0b000001101001, Gomoku::CAPTURE_SCORE },
            { 0b001001101001, Gomoku::CAPTURE_SCORE },
            { 0b001101101001, Gomoku::CAPTURE_SCORE },
            { 0b000101101001, Gomoku::CAPTURE_SCORE },
            { 0b100001101001, Gomoku::CAPTURE_SCORE },
            { 0b101001101001, Gomoku::CAPTURE_SCORE },
            { 0b101101101001, Gomoku::CAPTURE_SCORE },
            { 0b100101101001, Gomoku::CAPTURE_SCORE },
            { 0b110001101001, Gomoku::CAPTURE_SCORE },
            { 0b111001101001, Gomoku::CAPTURE_SCORE },
            { 0b111101101001, Gomoku::CAPTURE_SCORE },
            { 0b110101101001, Gomoku::CAPTURE_SCORE },
            { 0b010001101001, Gomoku::CAPTURE_SCORE },
            { 0b011001101001, Gomoku::CAPTURE_SCORE },
            { 0b011101101001, Gomoku::CAPTURE_SCORE },
            { 0b010101101001, Gomoku::CAPTURE_SCORE },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b100101100000, Gomoku::CAPTURE_SCORE },
            { 0b100101100010, Gomoku::CAPTURE_SCORE },
            { 0b100101100011, Gomoku::CAPTURE_SCORE },
            { 0b100101100001, Gomoku::CAPTURE_SCORE },
            { 0b100101101000, Gomoku::CAPTURE_SCORE },
            { 0b100101101010, Gomoku::CAPTURE_SCORE },
            { 0b100101101011, Gomoku::CAPTURE_SCORE },
            { 0b100101101001, Gomoku::CAPTURE_SCORE },
            { 0b100101101100, Gomoku::CAPTURE_SCORE },
            { 0b100101101110, Gomoku::CAPTURE_SCORE },
            { 0b100101101111, Gomoku::CAPTURE_SCORE },
            { 0b100101101101, Gomoku::CAPTURE_SCORE },
            { 0b100101100100, Gomoku::CAPTURE_SCORE },
            { 0b100101100110, Gomoku::CAPTURE_SCORE },
            { 0b100101100111, Gomoku::CAPTURE_SCORE },
            { 0b100101100101, Gomoku::CAPTURE_SCORE },
            { 0b000010010110, Gomoku::CAPTURE_SCORE },
            { 0b001010010110, Gomoku::CAPTURE_SCORE },
            { 0b001110010110, Gomoku::CAPTURE_SCORE },
            { 0b000110010110, Gomoku::CAPTURE_SCORE },
            { 0b100010010110, Gomoku::CAPTURE_SCORE },
            { 0b101010010110, Gomoku::CAPTURE_SCORE },
            { 0b101110010110, Gomoku::CAPTURE_SCORE },
            { 0b100110010110, Gomoku::CAPTURE_SCORE },
            { 0b110010010110, Gomoku::CAPTURE_SCORE },
            { 0b111010010110, Gomoku::CAPTURE_SCORE },
            { 0b111110010110, Gomoku::CAPTURE_SCORE },
            { 0b110110010110, Gomoku::CAPTURE_SCORE },
            { 0b010010010110, Gomoku::CAPTURE_SCORE },
            { 0b011010010110, Gomoku::CAPTURE_SCORE },
            { 0b011110010110, Gomoku::CAPTURE_SCORE },
            { 0b010110010110, Gomoku::CAPTURE_SCORE },
        },
    }
};

const std::array<Gomoku::t_coord, 4> Gomoku::_directions {{
    {0, 1},
    {1, 0},
    {-1, 1},
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
                            std::cout << "\033[1;31m* \033[0m";
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

Gomoku::Gomoku(uint8_t board_size, t_difficulty first_difficulty,
    t_difficulty second_difficulty, t_player_type first_player_type, t_player_type second_player_type, t_rule rule): _board(board_size),
    _last_best_move_x(Gomoku::_invalid_coord.x),
    _last_best_move_y(Gomoku::_invalid_coord.y),
    _search_complete(false)
{
	//if (board_size != 15 && board_size != 19)
	//    throw std::invalid_argument("Board size must be between 15 or 19");
    this->_first_player  = get_player(first_player_type, Gomoku::BLACK, first_difficulty);
    this->_second_player = get_player(second_player_type, Gomoku::WHITE, second_difficulty);
    this->_rule = rule;
    this->_depth[0] = (first_difficulty == Gomoku::HARD) ? 5 : (first_difficulty == Gomoku::MEDIUM) ? 3 : 1;
    this->_depth[1] = (second_difficulty == Gomoku::HARD) ? 5 : (second_difficulty == Gomoku::MEDIUM) ? 3 : 1;
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
        score = this->evaluate_move(board, piece_coord, piece, dir);
        if (score == Gomoku::ILLEGAL_SCORE)
            break;
    }
    board.remove_piece(piece_coord);
    return (score != Gomoku::ILLEGAL_SCORE);
}

int32_t Gomoku::evaluate_move(t_board &board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    int32_t                                 attack_score;
    int32_t                                 defense_score;
    uint16_t                                current_pattern;
    t_piece                                 current_piece;
    t_coord                                 pattern_position;

    const t_scores_map      &attack_patterns         = Gomoku::_attack_patterns.at(piece);
    const t_scores_map      &capture_patterns        = Gomoku::_capture_patterns.at(piece);
    const t_scores_map      &illegal_patterns        = Gomoku::_illegal_patterns.at(piece);
    const t_scores_map      &defense_patterns        = Gomoku::_defense_patterns.at(piece);

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
        current_piece = board.get_piece(piece_coord);
        current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
        if (illegal_patterns.count(current_pattern))
            return (Gomoku::ILLEGAL_SCORE);
        if (capture_patterns.count(current_pattern))
            return (Gomoku::CAPTURE_SCORE);
        if (attack_patterns.count(current_pattern))
            attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
        if (defense_patterns.count(current_pattern))
            defense_score = std::max(int32_t(defense_patterns.at(current_pattern)), attack_score);
        piece_coord -= direction;
        current_pattern >>= 2;
    }
    return (attack_score + defense_score);
}

bool Gomoku::check_illegal_moves(t_board &board, t_coord piece_coord, t_piece piece, t_coord direction) {
    uint16_t                                current_pattern;
    t_piece                                 current_piece;
    t_coord                                 pattern_position;

    const t_scores_map      &illegal_patterns        = Gomoku::_illegal_patterns.at(piece);

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
        current_piece = board.get_piece(piece_coord);
        current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
        if (illegal_patterns.count(current_pattern))
            return (true);
        piece_coord -= direction;
        current_pattern >>= 2;
    }
    return (false);
}

bool Gomoku::possible_capture(t_board&board, t_coord pos, t_piece color, t_coord dir) {
    t_coord check_pos;
    int32_t score;
    bool is_illegal = false;
    bool is_capture = false;
    t_piece opp_color = GET_OPPONENT(color);

    for (auto& curr_dir : _directions) {
        if (curr_dir == dir)
            continue;
        is_illegal = false;
        for (auto& factor : {-1, 1}){
            if (board.get_piece(pos + (curr_dir * factor)) == color){
                t_coord pos_1 = pos - (curr_dir * factor);
                t_coord pos_2 = pos + (curr_dir * (factor * 2));

                if (board.get_piece(pos_1) == opp_color && board.get_piece(pos_2) == EMPTY)
                    is_capture = is_move_valid(board, pos_2, opp_color);
                if (board.get_piece(pos_2) == opp_color && board.get_piece(pos_1) == EMPTY) 
                    is_capture = is_move_valid(board, pos_1, opp_color);
                if (is_capture)
                    return true;
            }
        }
    };
    return false;
}

bool Gomoku::check_for_win(t_board&board, t_coord pos, t_piece color, t_coord dir) {
    uint64_t combo = 0;
    t_piece piece;

    for (;;) {
        if (combo == 5)
            return true;
        piece = board.get_piece(pos);
        if (piece != color)
            break;
        if (possible_capture(board, pos, color, dir))
            combo = 0;
        else
            combo++;
        pos += dir;
    }
    return false;
}

int64_t Gomoku::evaluate_position(t_board&board, t_coord pos, t_piece color, t_coord dir, const t_scores_map &patterns) {
    uint16_t pattern = 0xFFF;
    t_piece piece;
    t_coord current_pos = pos;

    current_pos -= dir;
    for (int i = 0; i < 6; i++) {
        piece = board.get_piece(current_pos);
        if (i == 0 && piece == color)
            return 0;
        if (i != 0 && piece == GET_OPPONENT(color))
            break;
        pattern = (pattern << 2) | piece;
        current_pos += dir;
    }
    auto it = patterns.find(pattern & 0xFFF);
    t_scores score = (it != patterns.end()) ? it->second : static_cast<t_scores>(0);
    if (score == FIVE_SCORE){
        if (check_for_win(board, pos, color, dir))
            return WIN_SCORE;
    }
    return (it != patterns.end()) ? it->second : 0;
}

int64_t Gomoku::evaluate_board(t_board& board, t_piece player_color, t_capture_count capture_count) {
    int64_t score = 0;
    const t_scores_map& p_att_patterns = Gomoku::_attack_patterns.at(player_color);
    const t_scores_map& op_att_patterns = Gomoku::_attack_patterns.at(GET_OPPONENT(player_color));

    score += (capture_count.maximizer_count - capture_count.minimizer_count) * CAPTURE_SCORE;

    if (capture_count.maximizer_count >= 5)
        return WIN_SCORE;
    if (capture_count.minimizer_count >= 5)
        return -WIN_SCORE;

    for (int y = 0; y < board.size; ++y) {
        uint64_t row = board.data[y];
        if (!row)
            continue;

        while (row) {
            int bit_pos = __builtin_ctzll(row);

            if (bit_pos % 2 != 0) {
                bit_pos--;
            }

            int x = bit_pos >> 1;
            if (x >= board.size)
                break;

            t_piece piece = (t_piece)((row >> (x * 2)) & 3);
            if (piece != EMPTY) {
                t_coord pos = {x, y};
                const t_scores_map& att_patterns = (piece == player_color) ? p_att_patterns : op_att_patterns;
                int64_t position_score = 0;

                for (const auto& dir : _directions) {
                    int64_t score_eval = evaluate_position(board, pos, piece, dir, att_patterns);
                    if (score_eval == WIN_SCORE)
                        return (piece == player_color) ? WIN_SCORE : -WIN_SCORE;

                    position_score += score_eval;
                }

                score += (piece == player_color) ? position_score : -position_score;
            }

            row &= ~(3ULL << bit_pos);
        }
    }
    return score;
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
        pattern_eval = this->evaluate_move(board, move, piece, dir);
        if (pattern_eval == Gomoku::ILLEGAL_SCORE)
            break;
        if (pattern_eval == Gomoku::CAPTURE_SCORE)
        {
            this->extract_captured_stoned(board, scored_update.updates, move, dir, piece);
            scored_update.cupture_count += scored_update.updates.size() / 2;
        }
        scored_update.move.score += pattern_eval;
    }
    board.remove_piece(move);
    if (pattern_eval == Gomoku::ILLEGAL_SCORE)
        scored_update.updates.clear();
    else
        scored_update.updates.push_back(t_move_update{move, piece, Gomoku::ADD});
}

Gomoku::t_sorted_updates Gomoku::generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece, uint8_t depth)
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
        sorted_updates.push_back(scored_move);
    }

    std::sort(sorted_updates.begin(), sorted_updates.end(), [](const t_scored_update& a, const t_scored_update& b) {
        return a.move.score > b.move.score;
    });
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
    int64_t             alpha = prunner.alpha;

    if (depth == 0)
        return (t_scored_move{Gomoku::_invalid_coord, this->evaluate_board(board, piece, count)});
    best_eval = t_scored_move{Gomoku::_invalid_coord, -INTMAX_MAX};
    for (const auto& update: this->generate_sorted_updates(moveset, board, piece, depth))
    {
        if (_search_complete.load())
            return t_scored_move{Gomoku::_invalid_coord, INTMAX_MAX};

        added_moveset.clear();
        count.maximizer_count += update.cupture_count;
        if (count.maximizer_count >= MAX_CAPTURE)
            return (t_scored_move{update.move.coord, INTMAX_MAX - depth});
        this->update_node_state(board, added_moveset, moveset, update.updates);
        if (best_eval.score == -INTMAX_MAX)
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

void Gomoku::iterative_depth_search(t_moveset& moveset, t_board &board, uint8_t max_depth, 
                                    t_prunner prunner, t_capture_count count, t_piece piece) {
    t_scored_move move_score;

    for (uint8_t i_depth = 1; i_depth <= max_depth; i_depth += 2) {
        if (_search_complete.load()) {
            return;
        }
        this->_current_depth = i_depth;
        move_score = this->negascout(moveset, board, i_depth, INITIAL_PRUNNER, count, piece);
        if (move_score.coord != Gomoku::_invalid_coord) {
            _last_best_move_x.store(move_score.coord.x);
            _last_best_move_y.store(move_score.coord.y);
        }
        if (_search_complete.load()) {
            return;
        }
    }
    _search_complete.store(true);
}

Gomoku::t_coord Gomoku::ai_move(t_player& player, t_player &opponent, t_board& board) {
    t_moveset current_moveset = this->_ai_moveset;
    uint8_t depth = this->_depth[player.piece - 1];

    if (_turn == 0) {
        return GET_BOARD_CENTER(board);
    }
    if (_turn == 2 && this->_rule != Gomoku::STANDARD) {
        current_moveset = this->generate_rule_moveset(player.piece, board);
    }

    if (!current_moveset.empty()) {
        _last_best_move_x.store(current_moveset.begin()->x);
        _last_best_move_y.store(current_moveset.begin()->y);
    } else {
        _last_best_move_x.store(Gomoku::_invalid_coord.x);
        _last_best_move_y.store(Gomoku::_invalid_coord.y);
    }
    _search_complete.store(false);
    auto start = std::chrono::steady_clock::now();
    std::thread search_thread(&Gomoku::iterative_depth_search, this, std::ref(current_moveset),
        std::ref(board), depth, INITIAL_PRUNNER,
        t_capture_count{player.capture_count, opponent.capture_count}, player.piece);
    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        
        if (duration.count() >= 490 || _search_complete.load()) {
            _search_complete.store(true);
            break;
        }
    }
    search_thread.join();
    t_coord best_move = {_last_best_move_x.load(), _last_best_move_y.load()};
    if (best_move == Gomoku::_invalid_coord && !current_moveset.empty()) {
        best_move = *current_moveset.begin();
    }
    return best_move;
}
Gomoku::t_coord Gomoku::human_move(t_player& player, t_player &opponent, t_board& board)
{
    t_coord coord;
	t_coord suggestion;

    for (;;)
    {
        try
        {
            if (this->_turn == 0  && this->_rule != Gomoku::STANDARD)
                return GET_BOARD_CENTER(board);
            switch (this->get_game_command())
            {
                case 'S':
					{
    				auto start = std::chrono::steady_clock::now();
    				suggestion  = this->ai_move(player, opponent, board);
    				auto end = std::chrono::steady_clock::now();
    				double time = std::chrono::duration<double, std::milli>(end - start).count(); 
    				std::cout << time << std::endl;
                    PRINT_COORD(suggestion);
                    std::cout << "END SUGGESTION" << std::endl;
                    break;
					}
                case 'M':
                    std::cin >> coord.x >> coord.y;
                    if (this->is_move_valid(board, coord, player.piece))
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
        if (this->evaluate_move(board, start_coord, piece, dir) == Gomoku::FIVE_SCORE)
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

void Gomoku::make_move(t_player& player, t_player& opponent, t_board& board)
{
    t_coord         current_move;
    int64_t         score;

    auto start = std::chrono::steady_clock::now();
    current_move  = (this->*player.move)(player, opponent, board);
    auto end = std::chrono::steady_clock::now();
    
    double time = std::chrono::duration<double, std::milli>(end - start).count(); 
    std::cout << time << std::endl;
    this->average_time += time;
    if (current_move == Gomoku::_invalid_coord)
        PRINT_PLAYER_FORFEIT(player.piece);
    else
    {
        PRINT_COORD(current_move);
        this->update_game_state(this->_board, player, current_move);
        PRINT_CAPTURE_COUNT();
        score = this->evaluate_board(this->_board, player.piece, t_capture_count{player.capture_count, opponent.capture_count});
        std::cout << score << std::endl;
        this->print_board(this->_board, opponent.piece);
        if (score == Gomoku::WIN_SCORE || score == -Gomoku::WIN_SCORE)
        {
            if (score == Gomoku::WIN_SCORE)
                PRINT_PLAYER_WIN(player.piece);
            else
                PRINT_PLAYER_WIN(opponent.piece);
            STOP_GAME();
        }
        PRINT_DELINEATION();
    }
}

void Gomoku::start_game()
{
    for (;;)
    {
        if (IS_GAME_OVER())
            break;
        this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
    }
    this->average_time /= this->_turn;
    std::cout << "Average time: " << this->average_time << std::endl;
}

int main(int argc, char **argv)
{
    Gomoku::t_coord new_move;
    Gomoku::t_player_type p1_type;
    Gomoku::t_player_type p2_type;
    Gomoku::t_difficulty p1_diff;
    Gomoku::t_difficulty p2_diff;
    Gomoku::t_rule rule;
	uint16_t size;

    p1_type = Gomoku::HUMAN;
    p2_type = Gomoku::HUMAN;
    p1_diff = Gomoku::EASY;
    p2_diff = Gomoku::EASY;
    rule = Gomoku::STANDARD;

    if (argc < 2)
    {
        std::cout << "Usage: ./gomoku [size] [options]" << std::endl;
        return (1);
    }

	size = std::atoi(argv[1]);

    for (int i = 2; i < argc; i++)
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
        else if (strcmp(argv[i], "--p1_diff=easy") == 0)
            p1_diff = Gomoku::EASY;
        else if (strcmp(argv[i], "--p1_diff=medium") == 0)
            p1_diff = Gomoku::MEDIUM;
        else if (strcmp(argv[i], "--p1_diff=hard") == 0)
            p1_diff = Gomoku::HARD;
        else if (!strcmp(argv[i], "--p2_diff=easy"))
            p2_diff = Gomoku::EASY;
        else if (!strcmp(argv[i], "--p2_diff=medium"))
            p2_diff = Gomoku::MEDIUM;
        else if (!strcmp(argv[i], "--p2_diff=hard"))
            p2_diff = Gomoku::HARD;
        else {
            if (!strcmp(argv[i], "--rule=standard"))
                rule = Gomoku::STANDARD;
            else if (!strcmp(argv[i], "--rule=pro"))
                rule = Gomoku::PRO;
            else if (!strcmp(argv[i], "--rule=long_pro"))
                rule = Gomoku::LONG_PRO;
            continue;
        }
    
    }
    Gomoku game(size, p1_diff, p2_diff, p1_type, p2_type, rule);

    game.start_game();
    return (0);
}
