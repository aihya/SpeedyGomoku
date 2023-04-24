#include "Gomoku.hpp"

const std::map< Gomoku::e_piece, std::vector<std::pair<uint16_t, uint16_t>> > Gomoku::_win_patterns = {
    {
        Gomoku::BLACK, {
            { 0b0101010101, INTMAX_MAX },
            { 0b0001010101, 4 },
            { 0b0101010100, 4 },
            { 0b0000010101, 3 },
            { 0b0001010100, 3 },
            { 0b0101010000, 3 },
            { 0b0000000101, 2 },
            { 0b0000010100, 2 },
            { 0b0001010000, 2 },
            { 0b0101000000, 2 },
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
            { 0b0000101010, 3 },
            { 0b0010101000, 3 },
            { 0b1010100000, 3 },
            { 0b0000001010, 2 },
            { 0b0000101000, 2 },
            { 0b0010100000, 2 },
            { 0b1010000000, 2 },
            { 0b0000000010, 1 },
            { 0b0000001000, 1 },
            { 0b0000100000, 1 },
            { 0b0010000000, 1 },
            { 0b0100000000, 1 },
            { 0b1000000000, 1 },
        },
    }
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

Gomoku::t_board *Gomoku::new_board(size_t board_size)
{
    t_board *board;
    size_t  bytes;

    board = new t_board;
    board->board_buffer = new uint64_t[board_size];
    board->board_width = board_size;
    board->next = NULL;
    board->prev = NULL;
    return (board);
}

Gomoku::t_board *Gomoku::copy_board(t_board *board)
{
    t_board *board_copy;

    board_copy = new_board(board->board_width);
    memcpy(board_copy->board_buffer, board->board_buffer,
            board->board_width * sizeof(uint64_t));
    return (board_copy);
}

Gomoku::t_board *Gomoku::update_board(t_board *board, t_coord piece_coord, t_piece piece)
{
    t_board *new_board;

    new_board = copy_board(board);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    new_board->board_buffer[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
#else
    new_board->board_buffer[piece_coord.y] |= uint64_t(piece) >> (piece_coord.x * 2);
# endif
    return (new_board);
}
void Gomoku::push_move(t_board *board)
{
    if (this->_move_history != NULL)
    {
        this->_move_history->next = board;
        board->prev = this->_move_history;
    }
    this->_move_history = board;
}

void Gomoku::print_board()
{
    t_board *board = this->_move_history;

    for (short y = 0; y < board->board_width; y++)
    {
        for (short x = 0; x < board->board_width; x++)
        {
            t_piece piece = this->get_piece(board, (t_coord){x, y});
            if (piece == Gomoku::BLACK)
                std::cout << "X ";
            else if (piece == Gomoku::WHITE)
                std::cout << "O ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

Gomoku::Gomoku(size_t board_size, t_piece ai_color, t_difficulty difficulty):
    _move_history(NULL), _ai_color(ai_color), _difficulty(difficulty), _turn(0)
{

    if (board_size < 5 || board_size > 19)
        throw std::invalid_argument("Board size must be between 5 and 19");
   this->push_move(this->new_board(board_size));
}

Gomoku::~Gomoku()
{
    for (t_board *board = this->_move_history; board != NULL;)
    {
        t_board *tmp = board->prev;
        delete[] board->board_buffer;
        delete board;
        board = tmp;
    }
}

Gomoku::t_piece Gomoku::get_piece(t_board *board, t_coord piece_coord)
{
    uint64_t piece;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    piece = (board->board_buffer[piece_coord.y] >> (piece_coord.x * 2)) & 0b11;
#else
    piece = (board->board_buffer[piece_coord.y] << (piece_coord.x * 2)) & 0b11;
#endif
    switch (piece)
    {
        case Gomoku::BLACK:
            return (Gomoku::BLACK);
        case Gomoku::WHITE:
            return (Gomoku::WHITE);
        default:
            return (Gomoku::EMPTY);
    }
}

void    Gomoku::register_move(t_coord piece_coord, t_piece piece)
{
    this->push_move(this->update_board(this->_move_history, piece_coord, piece));
    this->_turn++;
}

uint64_t Gomoku::evaluate_dir(t_board *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    uint64_t    score = 0;
    uint16_t    current_pattern;
    t_coord     current_position;

    current_pattern = 0;
    current_position = piece_coord;
    do
    {
        if (current_position.x < 0 || current_position.x >= board->board_width)
            break;
        current_position.y = piece_coord.y;
        do
        {
            if (current_position.y < 0 || current_position.y >= board->board_width)
                break;
            current_pattern <<= 2;
            current_pattern |= board->board_buffer[current_position.y] >> current_position.x * 2;
            for (auto& x: _win_patterns.at(piece))
                if (current_pattern == x.first && x.second > score)
                    score = x.second;
            current_position.y += direction.y;
        } while(direction.y && std::abs(piece_coord.y - current_position.y) < 5);
        current_position.x += direction.x;
    } while(direction.x && std::abs(piece_coord.x - current_position.x) < 5);
    return (score);
}

#include <vector>

uint64_t Gomoku::evaluate_move(t_board *board, t_coord piece_coord, t_piece piece)
{
    uint64_t score = 0;

    for (auto& x: _directions)
        score += this->evaluate_dir(board, piece_coord, piece, x);
    return (score);
}


// uint64_t Gomoku::evaluate_move(t_board *board, t_coord piece_coord, t_piece piece)
// {
//     uint64_t score = 0;
//     uint16_t mask = 0b1111111111;
//     uint16_t current_pattern;

//     current_pattern = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         current_pattern =  (board->board_buffer[piece_coord.y] << (i * 2)) >> (piece_coord.x * 2) & mask;
//         for (auto& x: _win_patterns.at(piece))
//             if (current_pattern == x.first && x.second > score)
//                 score = x.second;
//     }
//     current_pattern = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         if (piece_coord.y + i == board->board_width)
//             break;
//         for (int j = 0; j < 5; j++)
//         {
//             if (piece_coord.y - j < 0)
//                 break;
//             current_pattern <<= 2;
//             current_pattern |= (board->board_buffer[piece_coord.y + i - j] >> (piece_coord.x * 2));
//             for (auto& x: _win_patterns.at(piece))
//                 if (current_pattern == x.first && x.second > score)
//                     score = x.second;
//         }
//     }
//     current_pattern = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         if (piece_coord.y + i == board->board_width)
//             break;
//         for (int j = 0; j < 5; j++)
//         {
//             if (piece_coord.y - j < 0)
//                 break;
//             current_pattern |= (board->board_buffer[piece_coord.y + i - j] >> (piece_coord.x * 2));
//             current_pattern <<= 2;
//         }
//         for (auto& x: _win_patterns.at(piece))
//             if (current_pattern == x.first && x.second > score)
//                 score = x.second;
//     }
//     return (score);
// }

int main()
{
    Gomoku game(19, Gomoku::BLACK, Gomoku::EASY);
    game.register_move((Gomoku::t_coord){18, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history, (Gomoku::t_coord){18, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){16, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history, (Gomoku::t_coord){16, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){18, 17}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history, (Gomoku::t_coord){18, 17},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    game.register_move((Gomoku::t_coord){17, 18}, Gomoku::WHITE);
    std::cout << game.evaluate_move(game._move_history, (Gomoku::t_coord){17, 18},  Gomoku::WHITE) << std::endl;
    game.print_board();
    std::cout << "-----------------------" << std::endl;
    return (0);
}