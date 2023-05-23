#include "Gomoku.hpp"



const Gomoku::t_patterns Gomoku::_attack_patterns = {
    {
        Gomoku::BLACK, {
            { 0b0101010101, Gomoku::WINNING_SCORE},
            { 0b0001010101, Gomoku::FOUR_SCORE },
            { 0b0101010100, Gomoku::FOUR_SCORE },
            { 0b0000010101, Gomoku::THREE_SCORE },
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
            { 0b0001010100, Gomoku::ILLEGAL_SCORE },
            { 0b10010110, Gomoku::ILLEGAL_SCORE },
            { 0b000100010100, Gomoku::ILLEGAL_SCORE},
            { 0b000101000100, Gomoku::ILLEGAL_SCORE}
        }
    },
    {
        Gomoku::WHITE, {
            { 0b0010101000, Gomoku::ILLEGAL_SCORE },
            { 0b01101001, Gomoku::ILLEGAL_SCORE },
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

uint64_t *Gomoku::copy_board(uint64_t *board)
{
    uint64_t *board_copy;

    board_copy = new uint64_t[this->_board_size]();
    for (short i = 0; i < this->_board_size; i++)
        board_copy[i] = board[i];
    return (board_copy);
}

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
                    if (current_move.x == this->_last_move.x && current_move.y == this->_last_move.y)
                        std::cout << "\033[1;32mX \033[0m";
                    else
                        std::cout << "X ";
                    break;
                case Gomoku::WHITE:
                    if (current_move.x == this->_last_move.x && current_move.y == this->_last_move.y)
                        std::cout << "\033[1;32mO \033[0m";
                    else
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
        if (y < 10) std::cout << "0";
        std::cout << y << " ";
        std::cout << std::endl;
    }
    for (short y = 0; y < this->_board_size; y++)
        std::cout << (char)('A' + y) << " ";
    std::cout << std::endl;
}

// Gomoku::Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty):
//     _second_player(player_color), _difficulty(difficulty), _turn(0), _board_size(board_size)
// {

//     if (board_size < 5 || board_size > 19)
//         throw std::invalid_argument("Board size must be between 5 and 19");
//     if (player_color != Gomoku::BLACK && player_color != Gomoku::WHITE)
//         throw std::invalid_argument("Player color must be BLACK or WHITE");
//    this->_move_history.push_front(new uint64_t[board_size]());
//    this->_first_player = (this->_second_player == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK;
//    this->_depth = 5;
// }

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
    t_difficulty second_difficulty, t_player_type first_player_type, t_player_type second_player_type)
{
    if (board_size < 5 || board_size > 19)
        throw std::invalid_argument("Board size must be between 5 and 19");
    this->_board_size = board_size;
    this->_turn = 0;
    this->_move_history.push_front(new uint64_t[board_size]());
    this->_first_player  = get_player(first_player_type, Gomoku::BLACK, first_difficulty);
    this->_second_player = get_player(second_player_type, Gomoku::WHITE, second_difficulty);
    this->_depth = 5;
}

Gomoku::~Gomoku()
{
    for (auto board : this->_move_history)
        delete[] board;
}

inline Gomoku::t_piece Gomoku::get_piece(uint64_t *board, t_coord piece_coord)
{
    if (piece_coord.y < 0 || piece_coord.y >= this->_board_size
            || piece_coord.x < 0 || piece_coord.x >= this->_board_size)
        return (Gomoku::ERROR);
    return (t_piece((board[piece_coord.y] >> (piece_coord.x * 2)) & 0b11));
}

bool    Gomoku::is_move_valid(t_coord piece_coord, t_piece piece)
{
    uint64_t *board = this->_move_history.front();
    int32_t score = 0;

    if (this->get_piece(board, piece_coord) != Gomoku::EMPTY)
        return (false);
    this->add_board_piece(board, piece_coord, piece);
    for (auto &dir: Gomoku::_directions)
    {
        score = this->evaluate_special_pattern(board, piece_coord, piece, dir);
        if (score == Gomoku::ILLEGAL_SCORE)
            break;
    }
    this->remove_board_piece(board, piece_coord);
    return (score != Gomoku::ILLEGAL_SCORE);
}

int32_t Gomoku::evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    int32_t                             attack_score;
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
        if (current_piece != Gomoku::EMPTY && current_piece != piece)
            break;
        for (int j = 0; j < 5; j++)
        {
            current_pattern <<= 2;
            current_piece = this->get_piece(board, pattern_position);
            current_pattern |= current_piece;
            if (current_piece != Gomoku::EMPTY && current_piece != piece)
                break;
            pattern_position += direction;
        }
        if (attack_patterns.contains(current_pattern))
            attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
        piece_coord -= direction;
    }
    return (attack_score);
}

int32_t Gomoku::evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece)
{
    int32_t score = 0;

    for (auto& dir: this->_directions)
        score += this->evaluate_dir(board, piece_coord, piece, dir);
    return (score);
}

int64_t Gomoku::evaluate_board(uint64_t *board, t_piece player_color)
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
            if (piece == player_color)
                score += this->evaluate_move(board, piece_coord, player_color);
            else if (piece == GET_OPPONENT(player_color))
                score -= this->evaluate_move(board, piece_coord, GET_OPPONENT(player_color));
        } while (piece_coord.x < this->_board_size);
    }

    return (score);
}

bool Gomoku::is_winning_move(uint64_t* board, t_piece piece, t_coord move)
{
    return (this->evaluate_move(board, move, piece) >= Gomoku::WINNING_SCORE);
}

void Gomoku::extract_captured_stoned(uint64_t *board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece)
{
    t_coord        current_pos;
    t_coord        move_dir;
    uint16_t       current_pattern;

    for (auto& factor: {-1, 1})
    {
        move_dir = dir * factor;
        if (this->get_piece(board, move + move_dir) == GET_OPPONENT(piece) &&
            this->get_piece(board, move + (move_dir * 2)) == GET_OPPONENT(piece) &&
            this->get_piece(board, move + (move_dir * 3)) == piece)
        {
            update_list.push_back(t_move_update{move + move_dir, GET_OPPONENT(piece), Gomoku::REMOVE});
            update_list.push_back(t_move_update{move + move_dir * 2, GET_OPPONENT(piece), Gomoku::REMOVE});
        }
    }
}

int32_t Gomoku::evaluate_special_pattern(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction)
{
    int32_t                             pattern_score;
    uint16_t                            current_pattern;
    t_piece                             current_piece;
    t_coord                             pattern_position;
    
    const std::map<uint16_t, t_scores>  &illegal_patterns  = Gomoku::_illegal_patterns.at(piece);
    const std::map<uint16_t, t_scores>  &capture_patterns  = Gomoku::_capture_patterns.at(piece);

    pattern_score = Gomoku::ZERO_SCORE;
    for (int i = 0; i < 6; i++)
    {
        current_pattern = 0;
        pattern_position = piece_coord;
        for (int j = 0; j < 6; j++)
        {
            current_pattern <<= 2;
            current_pattern |= this->get_piece(board, pattern_position);
            pattern_position += direction;
        }
        if (illegal_patterns.contains(current_pattern & FIVE_MASK) || illegal_patterns.contains(current_pattern & SIX_MASK))
            return (Gomoku::ILLEGAL_SCORE);
        if (capture_patterns.contains(current_pattern & FOUR_MASK))
            pattern_score = Gomoku::CAPTURE_SCORE;
        piece_coord -= direction;
    }
    return (pattern_score);
}


void Gomoku::generate_update_list(uint64_t* board, t_coord move, t_piece piece, t_update_list& update_list)
{
    int32_t         pattern_eval;
    uint16_t        current_pattern;

    this->add_board_piece(board, move, piece);
    for (auto& dir: this->_directions)
    {
        pattern_eval = this->evaluate_special_pattern(board, move, piece, dir);
        if (pattern_eval == Gomoku::ILLEGAL_SCORE)
            break;
        if (pattern_eval == Gomoku::CAPTURE_SCORE)
            this->extract_captured_stoned(board, update_list, move, dir, piece);
    }
    this->remove_board_piece(board, move);
    if (pattern_eval == Gomoku::ILLEGAL_SCORE)
        update_list.clear();
    else
        update_list.push_back(t_move_update{move, piece, Gomoku::ADD});
}

Gomoku::t_sorted_updates Gomoku::generate_sorted_updates(t_moveset& moveset, uint64_t* board, t_piece piece)
{
    t_sorted_updates    sorted_updates;
    t_scored_update     scored_move;

    for (auto& move: moveset)
    {
        scored_move = {0};
        scored_move.move.coord = move;
        this->generate_update_list(board, move, piece, scored_move.updates);
        if (scored_move.updates.empty())
            continue;
        this->update_board(board, scored_move.updates);
        for (auto& update: scored_move.updates)
        {
            if (update.type == Gomoku::REMOVE)
            {
                scored_move.move.score += Gomoku::CAPTURE_SCORE;
                scored_move.cupture_count++;
            }
        }
        scored_move.move.score += this->evaluate_move(board, move, piece);
        this->revert_board_update(board, scored_move.updates);
        sorted_updates.insert(scored_move);
        if (scored_move.move.score >= Gomoku::WINNING_SCORE)
            break;
    }
    return (sorted_updates);
}

void Gomoku::update_game_state(uint64_t *board, t_moveset &moveset, const t_update_list& update_list)
{
    t_coord new_move;

    this->update_board(board, update_list);
    for (auto& updates: update_list)
    {
        if (updates.type == Gomoku::ADD)
        {
            moveset.erase(updates.coord);
            for (auto& factor : Gomoku::_moveset_cells)
            {
                new_move = updates.coord + factor;
                if (this->get_piece(board, new_move) == Gomoku::EMPTY)
                    moveset.insert(new_move);
            }
        }
        if (updates.type == Gomoku::REMOVE)
            moveset.insert(updates.coord);
    }    
}
void Gomoku::update_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
{
    t_coord new_move;

    this->update_board(board, update_list);
    for (auto& updates: update_list)
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
    moveset.insert(added_moves.begin(), added_moves.end());
}

void Gomoku::revert_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list)
{
    this->revert_board_update(board, update_list);
    for (auto& move: added_moves)
        moveset.erase(move);
    for (auto& updates: update_list)
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

    if (depth == 0)
        return (t_scored_move{t_coord{}, this->evaluate_board(board, piece)});
    best_eval = t_scored_move{t_coord{}, INTMAX_MIN};
    for (auto& update: this->generate_sorted_updates(moveset, board, piece))
    {
        count.maximizer_count += update.cupture_count;
        if (update.move.score >= Gomoku::WINNING_SCORE)
            return (t_scored_move{update.move.coord, INTMAX_MAX});
        if (count.maximizer_count >= MAX_CAPTURE)
            return (t_scored_move{update.move.coord, INTMAX_MAX});
        added_moveset.clear();
        this->update_node_state(board, added_moveset, moveset, update.updates);
        move_eval = this->minimizer(moveset, board, depth - 1, prunner, count, GET_OPPONENT(piece));
        this->revert_node_state(board, added_moveset, moveset, update.updates);
        if (move_eval.score > best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.alpha = std::max(prunner.alpha, best_eval.score);
        if (prunner.beta <= prunner.alpha)
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

    if (depth == 0)
        return (t_scored_move{t_coord{}, this->evaluate_board(board, GET_OPPONENT(piece))});
    best_eval = t_scored_move{t_coord{}, INTMAX_MAX};
    for (auto& update: this->generate_sorted_updates(moveset, board, piece))
    {
        count.minimizer_count += update.cupture_count;
        if (update.move.score >= Gomoku::WINNING_SCORE)
            return (t_scored_move{update.move.coord, INTMAX_MIN});
        if (count.maximizer_count >= MAX_CAPTURE)
            return (t_scored_move{update.move.coord, INTMAX_MAX});
        added_moveset.clear();
        this->update_node_state(board, added_moveset, moveset, update.updates);
        move_eval = this->maximizer(moveset, board, depth - 1, prunner, count, GET_OPPONENT(piece));
        this->revert_node_state(board, added_moveset, moveset, update.updates);
        if (move_eval.score < best_eval.score)
            best_eval = t_scored_move{update.move.coord, move_eval.score};
        prunner.beta = std::min(prunner.beta, best_eval.score);
        if (prunner.beta <= prunner.alpha)
            break;
    }
    return (best_eval);
}

Gomoku::t_coord    Gomoku::get_bot_move()
{
    uint64_t        *new_board;
    t_scored_move    best_move;

    new_board = this->copy_board(this->_move_history.front());
    auto start = std::chrono::steady_clock::now();
    best_move = this->maximizer(this->_ai_moveset, new_board, this->_depth, t_prunner{INTMAX_MIN, INTMAX_MAX}, _capture_count, this->_first_player.piece);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "AI move took " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return best_move.coord;
}

Gomoku::t_coord Gomoku::ai_move(t_player& player, t_player &opponent)
{
    uint64_t        *new_board;
    t_scored_move    best_move;

    new_board = this->copy_board(this->_move_history.front());
    auto start = std::chrono::steady_clock::now();
    best_move = this->maximizer(this->_ai_moveset,
        new_board, this->_depth,
        t_prunner{INTMAX_MIN, INTMAX_MAX},
        _capture_count, player.piece);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "AI move took " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
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
            std::cin >> coord.x >> coord.y;
            if (this->is_move_valid(coord, player.piece))
                break;
            else
                std::cout << "Illegal move" << std::endl;
            std::cin.clear();
        }
        catch(const std::exception& e)
        {
            std::cout << "Invalid move" << '\n';
        }
        
    }
    return (coord);
}

void Gomoku::make_move(t_player& player, t_player& opponent)
{
    uint64_t        *new_board;
    t_update_list   update;
    t_coord         piece_coord;

    piece_coord = (this->*player.move)(player, opponent);
    new_board = this->copy_board(this->_move_history.front());
    this->generate_update_list(new_board, piece_coord, player.piece, update);
    this->update_game_state(new_board, this->_ai_moveset, update);
    this->_move_history.push_front(new_board);
    this->_last_move = piece_coord;
    this->print_board();
    if (this->is_winning_move(this->_move_history.front(), player.piece, piece_coord))
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Player " << player.piece << " wins!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        exit(1);
    }
    this->_turn++;
}

void Gomoku::start_game()
{
    for (;;)
    {
        this->make_move(this->_first_player, this->_second_player);
        this->make_move(this->_second_player, this->_first_player);
    }
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

    Gomoku game(19, p1_diff, p2_diff, p1_type, p2_type);
    game.start_game();

    return (0);
}