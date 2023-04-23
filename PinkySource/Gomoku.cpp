#include "Gomoku.hpp"

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
            board->byte_board_size * sizeof(uint64_t));
    return (board_copy);
}

Gomoku::t_board *Gomoku::update_board(t_board *board, t_coord piece_coord, t_piece piece)
{
    t_board *new_board;

    new_board = copy_board(board);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    new_board->board_buffer[piece_coord.y] |= piece << (piece_coord.x * 2);
#else
    new_board->board_buffer[piece_coord.y] |= piece >> (piece_coord.x * 2);
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

    for (size_t y = 0; y < board->board_width; y++)
    {
        for (size_t x = 0; x < board->board_width * 2; x += 2)
        {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            int piece = (board->board_buffer[y] >> x) & 0b11;
#else
            int piece = (board->board_buffer[y] << x) & 0b11;;
#endif
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
    _ai_color(ai_color), _difficulty(difficulty), _turn(0),_move_history(NULL)
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

int main()
{
    Gomoku game(19, Gomoku::BLACK, Gomoku::EASY);
    game.print_board();
    game.register_move((Gomoku::t_coord){0, 18}, Gomoku::WHITE);
    std::cout << "-----------------------" << std::endl;
    game.print_board();
    return (0);
}