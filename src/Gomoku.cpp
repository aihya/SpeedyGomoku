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
                        // if (this->_ai_moveset.count(current_move))
                        //     std::cout << "\033[1;31m. \033[0m";
                        // else
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
    t_difficulty second_difficulty, t_player_type first_player_type, t_player_type second_player_type, t_rule rule): _board(board_size), _ttable(64)
{
    if (board_size != 15 && board_size != 19)
        throw std::invalid_argument("Board size must be between 15 or 19");
    this->_first_player  = get_player(first_player_type, Gomoku::BLACK, first_difficulty);
    this->_second_player = get_player(second_player_type, Gomoku::WHITE, second_difficulty);
    this->_rule = rule;
    this->_depth = 5;
    this->_game_over = false;
    this->_turn = 0;
    this->hit_count = 0;
    this->node_count = 0;
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

int64_t Gomoku::evaluate_pattern(t_board& board, t_coord start, t_piece player_color, std::set<std::pair<t_coord, t_coord>> &head_tail_set)
{
    bool                        tail_block;
    t_coord                     current_coord; 
    std::pair<t_coord, t_coord> head_tail;
    uint16_t                    head_pattern;
    uint16_t                    tail_pattern;
    uint16_t                    current_pattern;
    int64_t                     score;

    const std::map<uint16_t, t_scores> &attack_patterns = Gomoku::_attack_patterns.at(player_color);
    const std::map<uint16_t, t_scores> &defense_patterns = Gomoku::_defense_patterns.at(player_color);

    // here we can identify the pattern by just a coordinate and a dir not a pair of coord
    score = 0;
    for (const auto& dir: _directions)
    {
        tail_block = false;
        current_coord    = start;
        head_tail.first  = current_coord - dir;
        head_tail.second = current_coord + dir;
        if (head_tail_set.count(head_tail))
            continue;
        current_pattern = board.get_piece(head_tail.first);
        for (int pattern_length = 0; pattern_length < 5; pattern_length++)
        {
            if (board.get_piece(current_coord) == player_color)
                head_tail_set.insert(head_tail);
            else if (board.get_piece(current_coord) != Gomoku::EMPTY)
                break;
            current_pattern  <<= 2;
            current_pattern  |= board.get_piece(current_coord);
            current_coord    += dir;
            head_tail.first  += dir;
            head_tail.second += dir;
        }
        if (board.get_piece(current_coord) == GET_OPPONENT(player_color))
            tail_block = true;
        head_pattern = current_pattern;
        tail_pattern = ((current_pattern & FIVE_MASK) << 2) | board.get_piece(current_coord);
        if (tail_block)
        {
            if (attack_patterns.count(tail_pattern))
                score += attack_patterns.at(tail_pattern);
        }
        else
            if (attack_patterns.count(head_pattern))
                score += attack_patterns.at(head_pattern);
    }
    return score;
}

int64_t Gomoku::evaluate_board(t_board &board, t_piece player_color)
{
    int64_t                                 score;
    uint64_t                                line;
    t_coord                                 piece_coord;
    t_piece                                 current_player;
    std::set<std::pair<t_coord, t_coord>>   head_tail_set;

    score = GET_CAPTURE(board, player_color) * Gomoku::CAPTURE_SCORE;
    score -= GET_CAPTURE(board, GET_OPPONENT(player_color)) * Gomoku::CAPTURE_SCORE;

    for (piece_coord.y = 0; piece_coord.y < board.size; piece_coord.y++)
    {
        line = board.data[piece_coord.y];
        do {
            if (line == 0)
                break;
            piece_coord.x = (__builtin_ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            current_player = board.get_piece(piece_coord);
            if (current_player == player_color)
                score += evaluate_pattern(board, piece_coord, current_player, head_tail_set);
            if (current_player == GET_OPPONENT(player_color))
                score -= evaluate_pattern(board, piece_coord, current_player, head_tail_set);
        } while (piece_coord.x < board.size);
    }
    return (score);
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
        if (pattern_eval >= Gomoku::FIVE_SCORE ||\
            (GET_CAPTURE(board, piece) + scored_update.cupture_count) >= MAX_CAPTURE)
            scored_update.move.winning = true;
        scored_update.move.score += pattern_eval;
    }
    board.remove_piece(move);
    if (pattern_eval == Gomoku::ILLEGAL_SCORE)
        scored_update.updates.clear();
    else
        scored_update.updates.push_back(t_move_update{move, piece, Gomoku::ADD});
}

Gomoku::t_sorted_updates Gomoku::generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece, TTable::t_TTEntry& entry, uint8_t depth)
{
    t_sorted_updates    sorted_updates;
    t_scored_update     scored_move;

    for (const auto& move: moveset)
    {
        scored_move = {0};
        scored_move.move.coord = move;
        scored_move.move.winning = false;
        this->generate_scored_update(board, move, piece, scored_move);
        if (scored_move.updates.empty())
            continue;
        if (entry.depth > 0 && board.hash == entry.hash && t_coord{entry.best_move} == move)
            scored_move.move.score = INTMAX_MAX;
        if (this->_current_depth == depth && this->_last_best == move)
            scored_move.move.score = INTMAX_MAX;
        sorted_updates.insert(scored_move);
    }
    int64_t best_score = (*sorted_updates.begin()).move.score;
    for (const auto& update: sorted_updates)
    {
        if (update.move.score < INTMAX_MAX)
        {
            best_score = update.move.score;
            break;
        }
    }
    if (best_score != INTMAX_MAX && best_score >= Gomoku::FIVE_BLOCK_SCORE)
    {
        for (auto it{sorted_updates.begin()}, end{sorted_updates.end()}; it != end; ){
            if (it->move.score < Gomoku::THREE_SCORE)
               sorted_updates.erase(it++);
            else
                it++;
        }
    }
    return (sorted_updates);
}


void Gomoku::update_node_state(t_board &board, t_piece piece, t_moveset &added_moves, t_moveset &moveset, const t_scored_update& sorted_update)
{
    t_coord new_move;
    
    board.add_capture(piece, sorted_update.cupture_count);
    this->update_board(board, sorted_update.updates);
    for (const auto& updates: sorted_update.updates)
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

void Gomoku::revert_node_state(t_board &board, t_piece piece, t_moveset &added_moves, t_moveset &moveset, const t_scored_update& sorted_update)
{
    board.remove_capture(piece, sorted_update.cupture_count);
    this->revert_board_update(board, sorted_update.updates);
    for (const auto& move: added_moves)
        moveset.erase(move);
    for (const auto& updates: sorted_update.updates)
    {
        if (updates.type == Gomoku::REMOVE)
            moveset.erase(updates.coord);
        if (updates.type == Gomoku::ADD)
            moveset.insert(updates.coord);
    }
}

void Gomoku::update_ttable(t_board& board, t_scored_move& best_move, uint8_t depth, int64_t alpha, int64_t beta)
{
    // TTable::t_TTEntry   entry;
    // TTable::t_bound     bound;
    
    // entry = this->_ttable.get_entry(board.hash);
    // bound = TTable::EXACT;
    // if (best_move.score <= alpha)
    //     bound = TTable::UPPER_BOUND;
    // if (best_move.score >= beta)
    //     bound = TTable::LOWER_BOUND;
    // if (entry.bound == TTable::ERROR || entry.depth < depth)
    //     this->_ttable.add_entry(board.hash, depth, {best_move.coord.x, best_move.coord.y}, best_move.score, bound);
}

int Gomoku::distance_to_edge(t_board& board, t_coord position, t_coord direction)
{
    t_coord distance {board.size, board.size};
    
    if (direction.x != 0)
        distance.x = (direction.x > 0) ? board.size - 1 - position.x : position.x;
    if (direction.y != 0)
        distance.y = (direction.y > 0) ? board.size - 1 - position.y : position.y;
    return std::min(distance.x, distance.y);
}

Gomoku::t_piece Gomoku::is_final_state(t_board& board)
{
    t_coord         piece_coord;
    uint64_t        line;
    t_piece         current_player;
    static t_coord  coords[100];

    if (GET_CAPTURE(board, Gomoku::BLACK) >= MAX_CAPTURE)
        return (Gomoku::BLACK);
    if (GET_CAPTURE(board, Gomoku::WHITE) >= MAX_CAPTURE)
        return (Gomoku::WHITE);
    for (piece_coord.y = 0; piece_coord.y < board.size; piece_coord.y++)
    {
        line = board.data[piece_coord.y];
        do {
            if (line == 0)
                break;
            piece_coord.x = (__builtin_ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            current_player = board.get_piece(piece_coord);
            for (const auto &direction: Gomoku::_directions)
            {
                int distance = this->distance_to_edge(board, piece_coord, direction);
                if (distance < 4)
                    continue;
                int i = 0;
                for (;;)
                {
                    t_coord current_coord = piece_coord + direction * i;
                    if (board.get_piece(current_coord) != current_player)
                        break;
                    coords[i] = current_coord;
                    i++;
                }
                if (i >= 5)
                {
                    int sequence = 1;
                    for (int j = 1; j < i; j++)
                    {
                        for (auto &factor: Gomoku::_moveset_cells)
                        {
                            if (board.get_piece(coords[j] + factor) == current_player)
                            {
                                if (board.get_piece(coords[j] - factor) == GET_OPPONENT(current_player) &&\
                                    is_move_valid(board, coords[j] + (factor * 2), GET_OPPONENT(current_player)))
                                    sequence = 0;
                                if (board.get_piece(coords[j] + factor * 2) == GET_OPPONENT(current_player) &&\
                                    is_move_valid(board, coords[j] - factor , GET_OPPONENT(current_player)))
                                    sequence = 0;
                            }
                        }
                        if (sequence != 0)
                            sequence++;
                    }
                    if (sequence >= 5)
                        return (current_player);
                }
                memset(coords, 0, i * sizeof(t_coord));
            }
        } while (piece_coord.x < board.size);
    }
    return (Gomoku::ERROR);
}

// int ProbeHash(int depth, int alpha, int beta)

// {

//     HASHE * phashe = &hash_table[ZobristKey() % TableSize()];

 

//     if (phashe->key == ZobristKey()) {
//         if (phashe->depth >= depth) {
//             if (phashe->flags == hashfEXACT)
//                 return phashe->val;
//             if ((phashe->flags == hashfALPHA) &&

//                 (phashe->val <= alpha))
//                 return alpha;
//             if ((phashe->flags == hashfBETA) &&

//                 (phashe->val >= beta))
//                 return beta;
//         }
//         RememberBestMove();

//     }
//     return valUNKNOWN;

// }
Gomoku::t_scored_move Gomoku::negascout(t_moveset& moveset,
            t_board &board, uint8_t depth, t_prunner prunner, t_piece piece)
{
    t_moveset           added_moveset;
    t_scored_move       move_eval;
    t_scored_move       best_eval;
    int64_t             entry_score;
    int64_t             alpha = prunner.alpha;
    TTable::t_TTEntry   entry;

    entry = this->_ttable.get_entry(board.hash);
    if (depth != this->_current_depth && entry.depth >= depth)
    {
        if(board.hash == entry.hash && entry.piece == piece)
        {
            if (entry.bound == TTable::EXACT)
                return (t_scored_move{t_coord(entry.best_move), entry.score});
            if (entry.bound == TTable::LOWER_BOUND)
                prunner.alpha = std::max(prunner.alpha, entry.score);
            if (entry.bound == TTable::UPPER_BOUND)
                prunner.beta = std::min(prunner.beta, entry.score);
            if (prunner.alpha >= prunner.beta)
                return (t_scored_move{t_coord(entry.best_move), entry.score});
        }
    }
    if (depth == 0 || is_final_state(board) != Gomoku::ERROR)
        return (t_scored_move{Gomoku::_invalid_coord, static_cast<int64_t>(this->evaluate_board(board, piece) * (1 + (0.01 * depth)))});
    this->node_count++;
    best_eval = t_scored_move{Gomoku::_invalid_coord, -INTMAX_MAX};
    for (const auto& update: this->generate_sorted_updates(moveset, board, piece, entry, depth))
    {
        added_moveset.clear();
        this->update_node_state(board, piece, added_moveset, moveset, update);
        if (best_eval.score == INTMAX_MIN)
            move_eval = -this->negascout(moveset, board, depth - 1, FLIP_PRUNNER(prunner), GET_OPPONENT(piece));
        else
        {
            move_eval = -this->negascout(moveset, board, depth - 1, SW_PRUNNER(prunner), GET_OPPONENT(piece));
            if (prunner.alpha < move_eval.score  && move_eval.score < prunner.beta)
                move_eval = -this->negascout(moveset, board, depth - 1, t_prunner{-prunner.beta, -move_eval.score}, GET_OPPONENT(piece));
        }
        this->revert_node_state(board, piece, added_moveset, moveset, update);
        if (move_eval.score > best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.alpha = std::max(prunner.alpha, best_eval.score);
        if (prunner.alpha >= prunner.beta)
            break;
    }
    if (depth != this->_current_depth)
    {
        TTable::t_bound bound = TTable::EXACT;
        if (best_eval.score <= alpha)
            bound = TTable::UPPER_BOUND;
        if (best_eval.score >= prunner.beta)
            bound = TTable::LOWER_BOUND;
        this->_ttable.add_entry(board.hash, depth, {best_eval.coord.x, best_eval.coord.y}, piece, best_eval.score, bound);
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
            t_board &board, uint8_t depth, t_prunner prunner, t_piece piece)
{
    auto start = std::chrono::steady_clock::now();
    t_scored_move best_move;
    t_scored_move move_score;
    t_sorted_updates sorted_updates;

    this->_last_best = Gomoku::_invalid_coord;
    // sorted_updates = this->generate_sorted_updates(moveset, board, piece);
    for (uint8_t i_depth = 1; i_depth <= depth;)
    {
        auto end = std::chrono::steady_clock::now();
        this->_current_depth = i_depth;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= 450)
            break;
        move_score = this->negascout(moveset, board, i_depth, prunner, piece);
        // if (move_score.score <= prunner.alpha || move_score.score >= prunner.beta)
        // {
        //     prunner = INITIAL_PRUNNER;
        //     continue;
        // }
        // prunner.alpha = move_score.score - 10000;
        // prunner.beta = move_score.score + 10000;
        this->_last_best = move_score.coord;
        i_depth++;
    }
    return (this->_last_best);
}

Gomoku::t_coord Gomoku::ai_move(t_player& player, t_player &opponent, t_board& board)
{
    t_coord         best_move;
    t_moveset       current_moveset = this->_ai_moveset;

    if (_turn == 0)
        best_move = GET_BOARD_CENTER(board);
    else
    {
        if (_turn == 2 && this->_rule != Gomoku::STANDARD)
            current_moveset = this->generate_rule_moveset(player.piece, board);
        best_move = this->iterative_depth_search(current_moveset,
            board, this->_depth, t_prunner{-INTMAX_MAX, INTMAX_MAX}, player.piece);
    }
    return best_move;
}

Gomoku::t_coord Gomoku::human_move(t_player& player, t_player &opponent, t_board& board)
{
    t_coord coord;

    // std::thread
    for (;;)
    {
        try
        {
            if (this->_turn == 0  && this->_rule != Gomoku::STANDARD)
                return GET_BOARD_CENTER(board);
            switch (this->get_game_command())
            {
                case 'S':
                    PRINT_COORD(this->ai_move(player, opponent, board));
                    std::cout << "END SUGGESTION" << std::endl;
                    break;
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
    board.add_capture(player.piece, scored_update.cupture_count);
    this->_turn++;
}

Gomoku::t_sequence Gomoku::extract_winning_sequence(t_board &board, t_piece piece, t_coord start_coord)
{
    t_sequence  sequence;

    if (IS_CAPTURE_WIN(board))
        return (sequence);
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
    t_piece         winning_player;

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
        this->print_board(this->_board, opponent.piece);
        winning_player = this->is_final_state(this->_board);
        if (winning_player != Gomoku::ERROR)
        {
            PRINT_PLAYER_WIN(winning_player);
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
    {
        if (IS_GAME_OVER())
            break;
        this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
    }
        // this->_board.add_piece({9, 8}, Gomoku::BLACK);
        // this->_board.add_piece({9, 9}, Gomoku::BLACK);
        // this->_board.add_piece({9, 10}, Gomoku::BLACK);
        // this->_board.add_piece({9, 11}, Gomoku::BLACK);
        // this->_board.add_piece({9, 12}, Gomoku::BLACK);
        // this->_board.add_piece({9, 13}, Gomoku::BLACK);
        // std::cout << is_final_state(this->_board) << std::endl;
    //     // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
    //     // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
    //     // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
        // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
        // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
        // this->make_move(GET_CURRENT_PLAYER(), GET_OPPONENT_PLAYER(), this->_board);
    // }

    this->average_time /= this->_turn;
    std::cout << "Average time: " << this->average_time << std::endl;
    std::cout << "Hit count: " << this->hit_count << std::endl;
    std::cout << "Node count: " << this->node_count << std::endl;
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

    Gomoku game(19, p1_diff, p2_diff, p1_type, p2_type, Gomoku::STANDARD);

    game.start_game();
    return (0);
}
