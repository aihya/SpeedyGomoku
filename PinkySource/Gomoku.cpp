#include "Gomoku.hpp"


const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            { 0b0101010101, Gomoku::WINNING_SCORE},
            { 0b0001010101, Gomoku::FOUR_SCORE },
            { 0b0101010100, Gomoku::FOUR_SCORE },
            { 0b0000010101, Gomoku::THREE_SCORE },
            { 0b0001010100, Gomoku::THREE_SCORE },
            { 0b0101010000, Gomoku::THREE_SCORE },
            { 0b0000000101, Gomoku::TWO_SCORE },
            { 0b0000010100, Gomoku::TWO_SCORE },
            { 0b0001010000, Gomoku::TWO_SCORE },
            { 0b0101000000, Gomoku::TWO_SCORE },
            { 0b0000000001, Gomoku::ONE_SCORE },
            { 0b0000000100, Gomoku::ONE_SCORE },
            { 0b0000010000, Gomoku::ONE_SCORE },
            { 0b0001000000, Gomoku::ONE_SCORE },
            { 0b0100000000, Gomoku::ONE_SCORE },
        }
    },
    {
        Gomoku::WHITE, {
            { 0b1010101010, Gomoku::WINNING_SCORE },
            { 0b0010101010, Gomoku::FOUR_SCORE },
            { 0b1010101000, Gomoku::FOUR_SCORE },
            { 0b0000101010, Gomoku::THREE_SCORE },
            { 0b0010101000, Gomoku::THREE_SCORE },
            { 0b1010100000, Gomoku::THREE_SCORE },
            { 0b0000001010, Gomoku::TWO_SCORE },
            { 0b0000101000, Gomoku::TWO_SCORE },
            { 0b0010100000, Gomoku::TWO_SCORE },
            { 0b1010000000, Gomoku::TWO_SCORE },
            { 0b0000000010, Gomoku::ONE_SCORE },
            { 0b0000001000, Gomoku::ONE_SCORE },
            { 0b0000100000, Gomoku::ONE_SCORE },
            { 0b0010000000, Gomoku::ONE_SCORE },
            { 0b1000000000, Gomoku::ONE_SCORE },
        },
    }
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

inline void Gomoku::update_board(uint64_t *board, t_coord piece_coord, t_piece piece)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    board[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
#else
    board[piece_coord.y] |= uint64_t(piece) >> (piece_coord.x * 2);
# endif
}

void Gomoku::print_board()
{
    this->print_board(this->_move_history.front(), this->_ai_moveset);
}

void Gomoku::print_board(uint64_t *board, t_moveset &moveset)
{
    for (short y = 0; y < this->_board_size; y++)
    {
        for (short x = 0; x < this->_board_size; x++)
        {
            t_coord current_move = {x, y};
            t_piece piece = this->get_piece(board, current_move);
            switch (piece)
            {
                case Gomoku::BLACK:
                    if (current_move.x == this->_best_move.x && current_move.y == this->_best_move.y)
                        std::cout << "\033[1;32mX \033[0m";
                    else
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
   this->_depth = 6;
}

Gomoku::~Gomoku()
{
    for (auto board : this->_move_history)
        delete[] board;
}

inline Gomoku::t_piece Gomoku::get_piece(uint64_t *board, t_coord piece_coord)
{
    t_piece piece;
    if (piece_coord.y < 0 || piece_coord.y >= this->_board_size
            || piece_coord.x < 0 || piece_coord.x >= this->_board_size)
        return (Gomoku::ERROR);
    piece = t_piece((board[piece_coord.y] >> (piece_coord.x * 2)) & 0b11);
    return (piece);
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

void Gomoku::get_new_moveset(uint64_t *board, t_moveset &possible_moves, t_moveset &old_moveset, t_coord piece_coord)
{
    t_coord new_move;

    for (auto& direction : Gomoku::_directions)
    {
        for (auto& factor: {-1, 1})
        {
            new_move.x = piece_coord.x + factor * direction.x;
            new_move.y = piece_coord.y + factor * direction.y;
            if (this->get_piece(board, new_move) == Gomoku::EMPTY)
                if (old_moveset.count(new_move) == 0)
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

uint32_t Gomoku::evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    uint32_t                            attack_score;
    uint16_t                            current_pattern;
    t_piece                             current_piece;
    t_coord                             pattern_position;
    const std::map<uint16_t, t_scores>  &attack_patterns  = Gomoku::_attack_patterns.at(piece);

    attack_score = 0;
    for (int i = 0; i < 5; i++)
    {
        current_pattern = 0;
        pattern_position = piece_coord;
        current_piece = this->get_piece(board, pattern_position);
        for (int j = 0; j < 5; j++)
        {
            current_pattern <<= 2;
            current_piece = this->get_piece(board, pattern_position);
            current_pattern |= current_piece;
            if (current_piece != Gomoku::EMPTY && current_piece != piece)
                break;
            pattern_position.y += direction.y;
            pattern_position.x += direction.x;
        }
        if (attack_patterns.contains(current_pattern))
            attack_score = std::max(uint32_t(attack_patterns.at(current_pattern)), attack_score);
        piece_coord.y -= direction.y;
        piece_coord.x -= direction.x;
    }
    return (attack_score);
}

uint32_t Gomoku::evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    uint32_t score = 0;

    for (auto& dir: this->_directions)
        score += this->evaluate_dir(board, piece_coord, piece, dir);
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
            piece_coord.x = (ffsll(line) - 1) >> 1;
            line &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            piece = this->get_piece(board, piece_coord);
            if (piece == this->_ai_color)
                score += this->evaluate_move(board, piece_coord, this->_ai_color);
            else if (piece == this->_player_color)
                score -= this->evaluate_move(board, piece_coord, this->_player_color);
        } while (piece_coord.x < this->_board_size);
    }

    return (score);
}

bool Gomoku::is_winning_move(uint64_t* board, t_piece piece, t_coord move)
{
    return (this->evaluate_move(board, move, piece) >= Gomoku::WINNING_SCORE);
}

inline void    Gomoku::clear_board_cell(uint64_t* board, t_coord piece_coord)
{
    board[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
}

Gomoku::t_sorted_moveset Gomoku::generate_sorted_moveset(t_moveset& moveset, uint64_t* board, t_piece piece)
{
    t_sorted_moveset    sorted_moveset;
    uint32_t            pattern_eval;

    for (auto& move: moveset)
    {
        this->update_board(board, move, piece);
        pattern_eval = this->evaluate_move(board, move, piece);
        sorted_moveset.insert(t_move_score{move, pattern_eval});
        this->clear_board_cell(board, move);
        if (pattern_eval >= Gomoku::WINNING_SCORE)
            break;
    }
    return (sorted_moveset);
}


int64_t Gomoku::minimax(t_moveset& moveset, uint64_t* board, uint8_t depth,
                            int64_t alpha, int64_t beta, bool max)
{
    int64_t             move_eval;
    uint64_t            pattern_eval;
    int64_t             best_eval;
    t_moveset           new_moveset;
    t_sorted_moveset    move_score_set;

    if (depth == 0)
        return this->evaluate_board(board);
    if (max)
    {
        best_eval = INTMAX_MIN;
        move_score_set = this->generate_sorted_moveset(moveset, board, this->_ai_color);
        for (auto& move: move_score_set)
        {
            if (move.score < Gomoku::WINNING_SCORE)
            {
                this->update_board(board, move.coord, this->_ai_color);
                new_moveset.clear();
                moveset.erase(move.coord);
                this->get_new_moveset(board, new_moveset, moveset, move.coord);
                moveset.insert(new_moveset.begin(), new_moveset.end());
                move_eval = minimax(moveset, board, depth - 1, alpha, beta, false);
                this->clear_board_cell(board, move.coord);
                for (auto& new_move: new_moveset)
                    moveset.erase(new_move);
                moveset.insert(move.coord);
                if (move_eval > best_eval)
                {
                    best_eval = move_eval;
                    if (depth == this->_depth)
                        this->_best_move = move.coord;
                }
                alpha = std::max(alpha, move_eval);
                if (beta <= alpha)
                    break;
            }
            else
            {
                if (depth == this->_depth)
                    this->_best_move = move.coord;
                return INTMAX_MAX;
            }
        }
    }
    else
    {
        best_eval = INTMAX_MAX;
        move_score_set = this->generate_sorted_moveset(moveset, board, this->_player_color);
        for (auto& move: move_score_set)
        {
            if (move.score >= Gomoku::WINNING_SCORE)
                return INTMAX_MIN;
            this->update_board(board, move.coord, this->_player_color);
            new_moveset.clear();
            moveset.erase(move.coord);
            this->get_new_moveset(board, new_moveset, moveset, move.coord);
            moveset.insert(new_moveset.begin(), new_moveset.end());
            move_eval = minimax(moveset, board, depth - 1, alpha, beta, true);
            this->clear_board_cell(board, move.coord);
            for (auto& new_move: new_moveset)
                moveset.erase(new_move);
            moveset.insert(move.coord);
            best_eval = std::min(best_eval, move_eval);
            beta = std::min(beta, move_eval);
            if (beta <= alpha)
                break;
        }
    }
    return best_eval;
}

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
    std::cout << "AI move: " << this->_best_move.x << " " << this->_best_move.y << std::endl;
}

void Gomoku::make_move(t_coord piece_coord)
{
    uint64_t    *new_board;
    t_piece     piece;

    piece = (this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK;
    if (piece == this->_ai_color)
    {
        this->make_move();
        piece_coord = this->_best_move;
    }
    else
    {
        new_board = this->copy_board(this->_move_history.front());
        this->register_move(piece_coord, piece, new_board, this->_ai_moveset);
        this->_move_history.push_front(new_board);
    }
    if (this->is_winning_move(this->_move_history.front(), piece, piece_coord))
    {
        this->print_board();
        std::cout << "-----------------------" << std::endl;
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