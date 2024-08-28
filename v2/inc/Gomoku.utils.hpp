#include <unordered_set>

#define PRINT_COORD(coord) std::cout << coord;
#define GET_OPPONENT(piece) ((piece == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK)
#define FLIP_CAPTURE(capture) t_capture_count{capture.minimizer_count, capture.maximizer_count}
#define FLIP_PRUNNER(prunner) t_prunner{-prunner.beta, -prunner.alpha}
#define INITIAL_PRUNNER t_prunner{-INTMAX_MAX, INTMAX_MAX}
#define GET_CURRENT_PLAYER() ((this->_turn % 2 == 0) ? this->_first_player : this->_second_player)
#define GET_OPPONENT_PLAYER() ((this->_turn % 2 == 0) ? this->_second_player : this->_first_player)
#define GET_BOARD_CENTER(board) t_coord{((board.size / 2)), ((board.size / 2))}
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

typedef enum e_scores
{
    FIVE_SCORE             = 1000000, 
    CAPTURE_SCORE          = 100000,
    FOUR_SCORE             = 10000,      
    THREE_SCORE            = 100,       
    OPEN_TWO_SCORE         = 10,        
    TWO_SCORE              = 1,         
    ZERO_SCORE             = 0          
}           t_scores;

typedef enum        e_pattern_mask
{
    SIX_MASK   = 0b111111111111,
    FIVE_MASK  = 0b1111111111,
    FOUR_MASK  = 0b11111111,
    THREE_MASK = 0b111111,
    TWO_MASK   = 0b1111,
}                   t_pattern_mask;

typedef enum        e_update_type
{
    ADD,
    REMOVE
}                   t_update_type;

typedef struct      s_prunner
{
    int64_t alpha;
    int64_t beta;
}                   t_prunner;

typedef struct      t_move_update
{
    t_coord         coord;
    t_piece         piece;
    t_update_type   type;
}                   t_move_update;

typedef enum        e_player_type
{
    HUMAN,
    AI
}                   t_player_type;  

struct MoveUpdateHash {
    std::size_t operator()(const t_move_update& mu) const {
        std::size_t h1 = std::hash<int>{}(mu.coord.x);
        std::size_t h2 = std::hash<int>{}(mu.coord.y);

        return (h1 * 73856093) ^ (h2 * 19349663);
    }
};

struct CoordHash {
    std::size_t operator()(const t_coord& coord) const {
        std::size_t h1 = std::hash<int>{}(coord.x);
        std::size_t h2 = std::hash<int>{}(coord.y);

        return (h1 * 0x1f1f1f1f) ^ (h2 * 0x2f2f2f2f);
    }
};

// Define the unordered_moveset type
typedef std::unordered_set<t_coord, CoordHash> t_moveset;
typedef std::vector<t_move_update>      t_update_list;
