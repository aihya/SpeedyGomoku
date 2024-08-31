#include <unordered_set>
#include <Board.hpp>

#define FLIP_CAPTURE(capture) t_capture_count{capture.minimizer_count, capture.maximizer_count}
#define FLIP_PRUNNER(prunner) t_prunner{-prunner.beta, -prunner.alpha}
#define INITIAL_PRUNNER t_prunner{-INTMAX_MAX, INTMAX_MAX} // ??
#define GET_CURRENT_PLAYER() ((this->_turn % 2 == 0) ? this->_first_player : this->_second_player)
#define GET_OPPONENT_PLAYER() ((this->_turn % 2 == 0) ? this->_second_player : this->_first_player)
#define GET_BOARD_CENTER(board) t_coord{((board.size / 2)), ((board.size / 2))}
#define PRINT_PLAYER_WIN(player) std::cout << "Player " << player << " wins !" << std::endl
#define PRINT_PLAYER_FORFEIT(player) std::cout << "Player " << player << " forfeits !" << std::endl
#define PRINT_DELINEATION() std::cout << "-------------------------------------" << std::endl
#define PRINT_CAPTURE_COUNT() std::cout << (int)this->_first_player.capture_count << " " << (int)this->_second_player.capture_count << std::endl
#define MAX_CAPTURE 5U
#define LONG_PRO_SIZE 7
#define PRO_SIZE 5

typedef enum        e_rule
{
    STANDARD,
    LONG_PRO,
    PRO,
}                   t_rule;

typedef enum        e_game_state
{
    ONGOING,
    WIN,
    DRAW
}                   t_game_state;

typedef enum        e_player_type
{
    HUMAN,
    AI
}                   t_player_type;

typedef enum        e_difficulty
{
    EASY,
    MEDIUM,
    HARD
}                   t_difficulty;

typedef struct      s_prunner
{
    int64_t alpha;
    int64_t beta;
}                   t_prunner;

typedef std::vector<t_board_update>             t_update_list;
