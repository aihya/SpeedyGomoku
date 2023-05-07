#include "Gomoku.hpp"

const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            { 0b0101010101, INT32_MAX },
            { 0b0001010101, 10000 },
            { 0b0101010100, 10000 },
            { 0b0000010101, 1000 },
            { 0b0001010100, 1000 },
            { 0b0101010000, 1000 },
            { 0b0000000101, 100 },
            { 0b0000010100, 100 },
            { 0b0001010000, 100 },
            { 0b0101000000, 100 },
            { 0b0000000001, 10 },
            { 0b0000000100, 10 },
            { 0b0000010000, 10 },
            { 0b0001000000, 10 },
            { 0b0100000000, 10 },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b1010101010, INT32_MAX },
            { 0b0010101010, 10000 },
            { 0b1010101000, 10000 },
            { 0b0000101010, 1000 },
            { 0b0010101000, 1000 },
            { 0b1010100000, 1000 },
            { 0b0000001010, 100 },
            { 0b0000101000, 100 },
            { 0b0010100000, 100 },
            { 0b1010000000, 100 },
            { 0b0000000010, 10 },
            { 0b0000001000, 10 },
            { 0b0000100000, 10 },
            { 0b0010000000, 10 },
            { 0b1000000000, 10 },
        },
    }
};


/**
 * @brief : Those are defence patterns but
 * we may not need them since we got minimax
 */

const Gomoku::t_patterns Gomoku::_defense_patterns = 
{
    {
        Gomoku::BLACK, {
            { 0b0110101010, 400000 },
            { 0b1001101010, 400000 },
            { 0b1010011010, 400000 },
            { 0b1010100110, 400000 },
            { 0b1010101001, 400000 },

            { 0b0110101000, 3200 },
            { 0b0001101010, 3200 },
            { 0b1010100100, 3200 },
            { 0b0010101001, 3200 },

            { 0b1010010000, 200 },
            { 0b0010100100, 200 },
            { 0b0000101001, 200 },
            { 0b0110100000, 200 },
            { 0b0001101000, 200 },
            { 0b0000011010, 200 },

            { 0b0000001001, 50 },
            { 0b0000100100, 50 },
            { 0b0010010000, 50 },
            { 0b1001000000, 50 },
            { 0b0110000000, 50 },
            { 0b0001100000, 50 },
            { 0b0000011000, 50 },
            { 0b0000000110, 50 },
        },
    },
    {
        Gomoku::WHITE, {
            { 0b1001010101, 400000 },
            { 0b0110010101, 400000 },
            { 0b0101100101, 400000 },
            { 0b0101011001, 400000 },
            { 0b0101010110, 400000 },

            { 0b1001010100, 3200 },
            { 0b0010010101, 3200 },
            { 0b0101011000, 3200 },
            { 0b0001010110, 3200 },

            { 0b0101100000, 200 },
            { 0b0001011000, 200 },
            { 0b0000010110, 200 },
            { 0b1001010000, 200 },
            { 0b0010010100, 200 },
            { 0b0000100101, 200 },

            { 0b0000000110, 50 },
            { 0b0000011000, 50 },
            { 0b0001100000, 50 },
            { 0b0110000000, 50 },
            { 0b1001000000, 50 },
            { 0b0010010000, 50 },
            { 0b0000100100, 50 },
            { 0b0000001001, 50 },
        }
    },
};

const std::array<Gomoku::t_coord, 4> Gomoku::_directions {{
    {0, -1},
    {-1, 0},
    {1, -1},
    {1, 1}
}};


uint64_t *Gomoku::copy_board(uint64_t *board)
{
    uint64_t *board_copy;

    board_copy = new uint64_t[this->_board_size]();
    for (short i = 0; i < this->_board_size; i++)
        board_copy[i] = board[i];
    return (board_copy);
}

void Gomoku::update_board(uint64_t *board, t_coord piece_coord, t_piece piece)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    board[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
#else
    board[piece_coord.y] |= uint64_t(piece) >> (piece_coord.x * 2);
# endif
}

void Gomoku::print_board()
{
    uint64_t *board = this->_move_history.front();
    t_moveset &moveset = this->_ai_moveset;
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
                    if (moveset.count((t_coord){x, y}))
                        std::cout << "\033[1;31m. \033[0m";
                    else
                        std::cout << ". ";
                    break;
                default:
                    std::cout << "? ";
                    break;
            }
        }
        if (y < 10) std::cout << "0";
        std::cout << y << " ";
        std::cout << std::endl;
    }
    for (short y = 0; y < this->_board_size; y++)
        std::cout << (char)('A' + y) << " ";
    std::cout << std::endl;
}

Gomoku::Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty):
    _player_color(player_color), _difficulty(difficulty), _turn(0), _board_size(board_size)
{

    if (board_size < 5 || board_size > 19)
        throw std::invalid_argument("Board size must be between 5 and 19");
    if (player_color != Gomoku::BLACK && player_color != Gomoku::WHITE)
        throw std::invalid_argument("Player color must be BLACK or WHITE");
   this->_move_history.push_front(new uint64_t[board_size]());
   this->_ai_color = (this->_player_color == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK;
   this->_depth = 4;
}

Gomoku::~Gomoku()
{
    for (auto board : this->_move_history)
        delete[] board;
}

Gomoku::t_piece Gomoku::get_piece(uint64_t *board, t_coord piece_coord)
{
    uint64_t piece;
    if (piece_coord.y < 0 || piece_coord.y >= this->_board_size
            || piece_coord.x < 0 || piece_coord.x >= this->_board_size)
        return (Gomoku::ERROR);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    piece = (board[piece_coord.y] >> (piece_coord.x * 2)) & 0b11;
#else
    piece = (board[piece_coord.y] << (piece_coord.x * 2)) & 0b11;
#endif
    return (t_piece(piece));
}

void Gomoku::update_ai_moveset(uint64_t *board, t_moveset &possible_moves, t_coord piece_coord)
{
    t_coord new_move;

    for (auto& direction : Gomoku::_directions)
    {
        for (auto& factor: {-1, 1})
        {
            new_move.x = piece_coord.x + factor * direction.x;
            new_move.y = piece_coord.y + factor * direction.y;
            if (this->get_piece(board, new_move) == Gomoku::EMPTY)
                possible_moves.insert(new_move);
        }
    }
}

bool    Gomoku::is_move_valid(t_coord piece_coord)
{
    if (this->get_piece(this->_move_history.front(), piece_coord) != Gomoku::EMPTY)
        return (false);
    return (true);
}

void    Gomoku::register_move(t_coord piece_coord, t_piece piece, uint64_t* board, t_moveset& moveset)
{
    this->update_board(board, piece_coord, piece);
    moveset.erase(piece_coord);
    this->update_ai_moveset(board, moveset, piece_coord);
}

uint64_t Gomoku::evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    uint32_t                            attack_score;
    uint16_t                            current_pattern;
    t_piece                             current_piece;
    t_coord                             pattern_position;
    t_piece                             opponent_piece = (piece == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK;
    bool                                valid_pattern;
    const std::map<uint16_t, uint32_t>  &attack_patterns  = Gomoku::_attack_patterns.at(piece);

    attack_score = 0;
    for (int i = 0; i < 5; i++)
    {
        current_pattern = 0;
        valid_pattern = true;
        pattern_position = piece_coord;
        for (int j = 0; j < 5; j++)
        {
            valid_pattern = false;
            current_pattern <<= 2;
            current_piece = this->get_piece(board, pattern_position);
            current_pattern |= current_piece;
            if (current_piece == Gomoku::ERROR || current_pattern == opponent_piece)
                break;
            pattern_position.y += direction.y;
            pattern_position.x += direction.x;
            valid_pattern = true;
        }
        if (valid_pattern && attack_patterns.contains(current_pattern))
            attack_score = std::max(attack_patterns.at(current_pattern), attack_score);
        piece_coord.y -= direction.y;
        piece_coord.x -= direction.x;
    }
    return (attack_score);
}

uint64_t Gomoku::evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    uint64_t score = 0;

    for (auto& dir: this->_directions)
        score = std::max(score, this->evaluate_dir(board, piece_coord, piece, dir));
    return (score);
}

int64_t Gomoku::evaluate_board(uint64_t *board)
{
    int64_t     score;
    t_coord     piece_coord;
    t_piece     piece;
    uint64_t    line;

    score = 0;
    for (piece_coord.y = 0; piece_coord.y < this->_board_size; piece_coord.y++)
    {
        line = board[piece_coord.y];
        do {
            if (line == 0)
                break;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            piece_coord.x = (ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
#else
            piece_coord.x = (ffsll(line) - 1) << 1;
            line &= ~((uint64_t)(Gomoku::ERROR) >> (piece_coord.x >> 1));
#endif
            piece = this->get_piece(board, piece_coord);
            if (piece == this->_ai_color)
                score += this->evaluate_move(board, piece_coord, this->_ai_color);
            else if (piece == this->_player_color)
                score -= this->evaluate_move(board, piece_coord, this->_player_color);
        } while (piece_coord.x < this->_board_size);
    }

    return (score);
}

bool Gomoku::is_winning_board(uint64_t* board, t_piece piece)
{
    t_coord     piece_coord;
    uint64_t    line;

    for (piece_coord.y = 0; piece_coord.y < this->_board_size; piece_coord.y++)
    {
        line = board[piece_coord.y];
        do {
            if (line == 0)
                break;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            piece_coord.x = (ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
#else
            piece_coord.x = (ffsll(line) - 1) << 1;
            line &= ~((uint64_t)(Gomoku::ERROR) >> (piece_coord.x >> 1));
#endif
            if (piece != this->get_piece(board, piece_coord))
                continue;
            if (this->evaluate_move(board, piece_coord, piece) == INT32_MAX)
                return (true);
        } while (piece_coord.x < this->_board_size);
    }
    return (false);
}

void    Gomoku::clear_board_cell(uint64_t* board, t_coord piece_coord)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    board[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
#else
    board[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) >> (piece_coord.x >> 1));
#endif
}

int64_t Gomoku::minimax(t_moveset& moveset, uint64_t* board, uint8_t depth,
                            int64_t alpha, int64_t beta, bool max)
{
    t_piece     op_color;
    t_piece     current_color;
    int64_t     move_eval;
    t_moveset   new_moveset;

    op_color = (max) ? this->_player_color : this->_ai_color;
    current_color = (max) ? this->_ai_color : this->_player_color;
    if (depth == 0 || (depth && this->is_winning_board(board, op_color)))
        return this->evaluate_board(board);
    if (max)
    {
        int64_t max_eval = INTMAX_MIN;
        for (auto& move: moveset)
        {
            new_moveset = moveset;
            this->update_board(board, move, current_color);
            new_moveset.erase(move);
            this->update_ai_moveset(board, new_moveset, move);
            move_eval = minimax(new_moveset, board, depth - 1, alpha, beta, false);
            this->clear_board_cell(board, move);
            if (move_eval > max_eval)
            {
                max_eval = move_eval;
                if (depth == this->_depth)
                    this->_best_move = move;
            }
            alpha = std::max(alpha, move_eval);
            if (beta <= alpha)
                break;
        }
        return max_eval;
    }
    else
    {
        int64_t min_eval = INTMAX_MAX;
        for (auto& move: moveset)
        {
            new_moveset = moveset;
            this->update_board(board, move, current_color);
            new_moveset.erase(move);
            this->update_ai_moveset(board, new_moveset, move);
            move_eval = minimax(new_moveset, board, depth - 1, alpha, beta, true);
            this->clear_board_cell(board, move);
            min_eval = std::min(min_eval, move_eval);
            beta = std::min(beta, move_eval);
            if (beta <= alpha)
                break;
        }
        return min_eval;
    }
}

// int64_t Gomoku::minimax(t_moveset& moveset, uint64_t* board, uint8_t depth,
//                             int64_t alpha, int64_t beta, bool max)
// {
//     t_piece     current_color;
//     t_piece     op_color;
//     t_moveset   new_moveset;
//     int64_t     move_eval;
//     uint64_t    *new_board;

//     current_color = (max) ? this->_ai_color : this->_player_color;
//     op_color = (max) ? this->_player_color : this->_ai_color;
//     if (depth == 0 || (depth && this->is_winning_board(board, op_color)))
//         return this->evaluate_board(board);
//     if (max)
//     {
//         int64_t max_eval = INTMAX_MIN;
//         for (auto& move: moveset)
//         {
//             new_board = this->copy_board(board);
//             new_moveset = t_moveset(moveset);
//             this->register_move(move, current_color, new_board, new_moveset);
//             move_eval = minimax(new_moveset, new_board, depth - 1, alpha, beta, false);
//             if (move_eval > max_eval)
//             {
//                 max_eval = move_eval;
//                 if (depth == this->_depth)
//                     this->_best_move = move;
//             }
//             delete [] new_board;
//             alpha = std::max(alpha, move_eval);
//             if (beta <= alpha)
//                 break;
//         }
//         return max_eval;
//     }
//     else
//     {
//         int64_t min_eval = INTMAX_MAX;
//         for (auto& move: moveset)
//         {
//             new_board = this->copy_board(board);
//             new_moveset = t_moveset(moveset);
//             this->register_move(move, current_color, new_board, new_moveset);
//             move_eval = minimax(new_moveset, new_board, depth - 1, alpha, beta, true);
//             min_eval = std::min(min_eval, move_eval);
//             beta = std::min(beta, move_eval);
//             delete [] new_board;
//             if (beta <= alpha)
//                 break;
//         }
//         return min_eval;
//     }
// }

#include <chrono>

void    Gomoku::make_move()
{
    uint64_t    *new_board;

    auto start = std::chrono::steady_clock::now();
    new_board = copy_board(this->_move_history.front());
    this->minimax(this->_ai_moveset, new_board, this->_depth, INTMAX_MIN, INTMAX_MAX, true);
    this->register_move(this->_best_move, this->_ai_color, new_board, this->_ai_moveset);
    this->_move_history.push_front(new_board);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "AI move took " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
}

void Gomoku::make_move(t_coord piece_coord)
{
    uint64_t    *new_board;
    t_piece     piece;

    piece = (this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK;
    if (piece == this->_ai_color)
        this->make_move();
    else
    {
        new_board = this->copy_board(this->_move_history.front());
        this->register_move(piece_coord, piece, new_board, this->_ai_moveset);
        this->_move_history.push_front(new_board);
    }
    if (this->is_winning_board(this->_move_history.front(), piece))
    {
        if (piece == this->_ai_color)
            std::cout << "AI wins!" << std::endl;
        else
            std::cout << "Player wins!" << std::endl;
        exit(1);
    }
    this->_turn++;
}

int main()
{
    int             row;
    char            col;
    Gomoku::t_coord new_move;

    Gomoku game(19, Gomoku::WHITE, Gomoku::EASY);
    for(;;)
    {
        game.print_board();
        std::cout << "-----------------------" << std::endl;
        if (game.is_player_turn())
        {
            try
            {
                std::cout << "Enter move: " << std::endl;
                std::cout << "-row (0 - 18): ";
                std::cin >> row;
                std::cout << "-col (A - S): ";
                std::cin >> col;
            }
            catch(const std::exception& e)
            {
                break;
            }
            if (row < 0 || row > 18 || col < 'A' || col > 'S')
                break;
            new_move.y = row;
            new_move.x = col - 'A';
            if (game.is_move_valid(new_move))
                game.make_move(new_move);
            else
                std::cout << "Invalid move." << std::endl;
        }
        else
            game.make_move(new_move);
    }
    std::cout << "Invalid move." << std::endl;
    return (0);
}