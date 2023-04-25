#include "Gomoku.hpp"

const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            { 0b0101010101, INTMAX_MAX },
            { 0b0001010101, 4 },
            { 0b0101010100, 4 },
            { 0b0000010101, 300 },
            { 0b0001010100, 300 },
            { 0b0101010000, 300 },
            { 0b0000000101, 100 },
            { 0b0000010100, 100 },
            { 0b0001010000, 100 },
            { 0b0101000000, 100 },
            { 0b0000000001, 1 },
            { 0b0000000100, 1 },
            { 0b0000010000, 1 },
            { 0b0001000000, 1 },
            { 0b0010000000, 1 },
            { 0b0100000000, 1 },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b1010101010, INTMAX_MAX },
            { 0b0010101010, 4 },
            { 0b1010101000, 4 },
            { 0b0000101010, 300 },
            { 0b0010101000, 300 },
            { 0b1010100000, 300 },
            { 0b0000001010, 200 },
            { 0b0000101000, 200 },
            { 0b0010100000, 200 },
            { 0b1010000000, 200 },
            { 0b0000000010, 1 },
            { 0b0000001000, 1 },
            { 0b0000100000, 1 },
            { 0b0010000000, 1 },
            { 0b0100000000, 1 },
            { 0b1000000000, 1 },
        },
    }
};

const Gomoku::t_patterns Gomoku::_defense_patterns = 
{
    {
        Gomoku::BLACK, {
            { 0b0110101010, INTMAX_MAX },
            { 0b1001101010, INTMAX_MAX },
            { 0b1010011010, INTMAX_MAX },
            { 0b1010100110, INTMAX_MAX },
            { 0b1010101001, INTMAX_MAX },
            /**
             * @brief TODO: Add more patterns
             * The logic here is to catch any patterns that can be used to attack
             */
        },
    },
    {
        Gomoku::WHITE, {
            { 0b1001010101, INTMAX_MAX },
            { 0b0110010101, INTMAX_MAX },
            { 0b0101100101, INTMAX_MAX },
            { 0b0101011001, INTMAX_MAX },
            { 0b0101010110, INTMAX_MAX },
            /**
             * @brief TODO: Add more patterns
             * The logic here is to catch any patterns that can be used to attack
             */
        }
    },
};

const std::vector<Gomoku::t_coord> Gomoku::_directions = {
    {0, 1},
    {0,-1},
    {1, 0},
    {-1,0},
    {-1,1},
    {-1,-1},
    {1,-1},
    {1, 1}
};


uint64_t *Gomoku::copy_board(uint64_t *board)
{
    uint64_t *board_copy;

    board_copy = new uint64_t[this->_board_size]();
    for (short i = 0; i < this->_board_size; i++)
        board_copy[i] = board[i];
    return (board_copy);
}

uint64_t *Gomoku::update_board(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    uint64_t *new_board;

    new_board = copy_board(board);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    new_board[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
#else
    new_board[piece_coord.y] |= uint64_t(piece) >> (piece_coord.x * 2);
# endif
    return (new_board);
}

void Gomoku::print_board()
{
    uint64_t *board = this->_move_history.front();

    for (short y = 0; y < this->_board_size; y++)
    {
        for (short x = 0; x < this->_board_size; x++)
        {
            t_piece piece = this->get_piece(board, (t_coord){x, y});
            switch (piece)
            {
                case Gomoku::BLACK:
                    std::cout << "X ";
                    break;
                case Gomoku::WHITE:
                    std::cout << "O ";
                    break;
                case Gomoku::EMPTY:
                    std::cout << ". ";
                    break;
                default:
                    std::cout << "? ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

Gomoku::Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty):
    _player_color(player_color), _difficulty(difficulty), _turn(0), _board_size(board_size)
{

    if (board_size < 5 || board_size > 19)
        throw std::invalid_argument("Board size must be between 5 and 19");
   this->_move_history.push_front(new uint64_t[board_size]());
   this->_ai_color = (this->_player_color == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK;
}

Gomoku::~Gomoku()
{
    for (auto board : this->_move_history)
        delete[] board;
}

Gomoku::t_piece Gomoku::get_piece(uint64_t *board, t_coord piece_coord)
{
    uint64_t piece;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    piece = (board[piece_coord.y] >> (piece_coord.x * 2)) & 0b11;
#else
    piece = (board[piece_coord.y] << (piece_coord.x * 2)) & 0b11;
#endif
    return (t_piece(piece));
}

void    Gomoku::register_move(t_coord piece_coord, t_piece piece)
{
    this->_move_history.push_front(this->update_board(this->_move_history.front(), piece_coord, piece));
    this->_turn++;
}

uint64_t Gomoku::evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    uint32_t    score;
    uint16_t    current_pattern;
    t_coord     current_position;
    const std::map<uint16_t, uint32_t> &attack_patterns = Gomoku::_attack_patterns.at(piece);
    const std::map<uint16_t, uint32_t> &defense_patterns = Gomoku::_defense_patterns.at(piece);

    score = 0;
    current_pattern = 0;
    current_position = piece_coord;
    do
    {
        if (current_position.x < 0 || current_position.x >= this->_board_size)
            break;
        current_position.y = piece_coord.y;
        do
        {
            if (current_position.y < 0 || current_position.y >= this->_board_size)
                break;
            current_pattern <<= 2;
            current_pattern |= this->get_piece(board, current_position);
            if (attack_patterns.contains(current_pattern))
                score = std::max(attack_patterns.at(current_pattern), score);
            else
                break;
            current_position.y += direction.y;
        } while(direction.y && std::abs(piece_coord.y - current_position.y) < 5);
        current_position.x += direction.x;
    } while(direction.x && std::abs(piece_coord.x - current_position.x) < 5);
    return (score);
}


uint64_t Gomoku::evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    uint64_t score = 0;

    for (auto& x: _directions)
        score += this->evaluate_dir(board, piece_coord, piece, x);
    return (score);
}


uint64_t Gomoku::test_evaluate_board(t_piece piece)
{
    uint64_t score = 0;
    uint64_t *board = this->_move_history.front();

    for (int i = 0;  i < 9320; i ++)
    {
        for (short y = 0; y < this->_board_size; y++)
            for (short x = 0; x < this->_board_size; x++)
                score += this->evaluate_move(board, (t_coord){x, y}, piece);
    }
    return (score);
}

int main()
{
    Gomoku game(19, Gomoku::BLACK, Gomoku::EASY);
    game.register_move((Gomoku::t_coord){18, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history.front(), (Gomoku::t_coord){18, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){16, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history.front(), (Gomoku::t_coord){16, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){18, 17}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history.front(), (Gomoku::t_coord){18, 17},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){17, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history.front(), (Gomoku::t_coord){17, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    // game.test_evaluate_board(Gomoku::WHITE);

    return (0);
}