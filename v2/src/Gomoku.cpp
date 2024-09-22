#include "Gomoku.hpp"

const t_coord  Gomoku::_invalid_coord = t_coord{-1, -1};

Gomoku::Gomoku( uint8_t size,
                t_difficulty first_difficulty, t_difficulty second_difficulty,
                t_player_type first_player_type, t_player_type second_player_type,
                t_rule rule):
_board(size), _depth(0), _turn(0), _rule(rule), _game_over(false)
{
    _first_player.piece = BLACK;
    _second_player.piece = WHITE;
    _first_player.capture_count = 0;
    _second_player.capture_count = 0;
    _depth = 3;
    _first_player.difficulty = first_difficulty;
    _second_player.difficulty = second_difficulty;
    _first_player.move = (first_player_type == HUMAN) ? &Gomoku::human_move : &Gomoku::ai_move;
    _second_player.move = (second_player_type == HUMAN) ? &Gomoku::human_move : &Gomoku::ai_move;
    // _depth = (_first_player.difficulty == EASY) ? 3 : (_first_player.difficulty == MEDIUM) ? 5 : 7;
    _depth = 4;
}

Gomoku::~Gomoku() {
}

void Gomoku::make_move(t_player& player, t_player& opponent)
{
    t_coord         current_move;
    int64_t         score;

    current_move  = (this->*player.move)(player, opponent, this->_board);

    this->_board.make_move(current_move, player.piece, _updates_queue);
    if (current_move == Gomoku::_invalid_coord)
        PRINT_PLAYER_FORFEIT(player.piece);
    std::cout << 0.0 << std::endl;
    std::cout << current_move;
    std::cout << this->_board._capture_count[0] << " " << this->_board._capture_count[1] << std::endl;
    this->_board.print_board(player.piece);
    score = this->_board.evaluate_board(player.piece);
    if (score == WIN_SCORE || score == -WIN_SCORE)
    {
        if (score == WIN_SCORE)
            PRINT_PLAYER_WIN(player.piece);
        else
            PRINT_PLAYER_WIN(opponent.piece);
        this->_game_over = true;
    }
    PRINT_DELINEATION();
}


t_scored_coord Gomoku::negascout(t_ordered_moves& moveset, Board& board, t_piece curr_piece, uint8_t depth, t_prunner prunner) {
    if (moveset.empty())
        return {-WIN_SCORE, Gomoku::_invalid_coord};
    if (depth == 0) {
        int64_t score = board.evaluate_board(curr_piece);
        return {score, Gomoku::_invalid_coord};
    }

    t_scored_coord best_move = {-INTMAX_MAX, Gomoku::_invalid_coord};
    int64_t alpha = prunner.alpha;
    int64_t beta = prunner.beta;
    t_piece opposite_piece = GET_OPPOSITE_PIECE(curr_piece);

    for (size_t i = 0; i < moveset.size(); ++i) {
        auto& move = moveset[i];
        size_t added_updates = board.make_move(move.coord, curr_piece, _updates_queue);
        
        t_ordered_moves next_moveset = board.order_moves(opposite_piece);
        t_scored_coord result;

        if (i == 0) {
            // Full-width search for the first child
            result = negascout(next_moveset, board, opposite_piece, depth - 1, {-beta, -alpha});
        } else {
            // Null window search for the remaining children
            result = negascout(next_moveset, board, opposite_piece, depth - 1, {-alpha - 1, -alpha});
            
            if (alpha < -result.score && -result.score < beta) {
                // Re-search with full window if the null window search failed high
                result = negascout(next_moveset, board, opposite_piece, depth - 1, {-beta, -alpha});
            }
        }

        board.revert_updates(_updates_queue, added_updates);

        // We always negate the score, regardless of depth
        result.score = -result.score;
        
        if (result.score > best_move.score) {
            best_move = {result.score, move.coord};
            alpha = std::max(alpha, result.score);
            if (alpha >= beta) {
                break;  // Beta cutoff
            }
        }
    }

    return best_move;
}
void Gomoku::start_game() {
    t_player *current_player;
    t_player *opponent;
    t_coord move;

    while (!_game_over) {
    // for (int i = 0; i < 5; i++) {
        current_player = (_turn % 2 == 0) ? &_first_player : &_second_player;
        opponent = (_turn % 2 == 0) ? &_second_player : &_first_player;
        make_move(*current_player, *opponent);
        _turn++;
    }
    // }
}

t_coord Gomoku::ai_move(t_player& player, t_player& opponent, Board& board) {
    t_prunner prunner = INITIAL_PRUNNER;
    t_ordered_moves moveset = board.order_moves(player.piece);
    if (moveset.size() == 0)
        return GET_BOARD_CENTER(board);
    return negascout(moveset, board, player.piece ,_depth, prunner).coord;
}

t_coord Gomoku::human_move(t_player& player, t_player &opponent, Board& board)
{
 
    t_coord coord;
    char command = 'N';

    for (;;)
    {
        try
        {
            if (_turn == 0  && _rule != STANDARD)
                return GET_BOARD_CENTER(board);
            std::cin >> command;
            switch (command)
            {
                case 'S':
                    std::cout << ai_move(player, opponent, board);
                    std::cout << "END SUGGESTION" << std::endl;
                    break;
                case 'M':
                    std::cin >> coord.x >> coord.y;
                    try {
                        this->_board.validate_coord(coord, player.piece);
                        return coord;
                    }
                    catch(const std::exception& e) {
                        std::cout << "Illegal move" << std::endl;
                    }
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
