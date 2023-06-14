#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <string.h>
#include <chrono>
#include <array>
/**
 * @brief Game class
 * This game is a simple implementation of the gomoku game using minimax algorithm.
 * The player 1 is the black player and the player 2 is the white player.
 * The pieces are represented by a 2 bits, 01 (1) for black and 10 (2) for white.
 * The board is represented by an array of ints
 * 
 * NB: The same concept is working for an array of char, i tried it but we will stick
 * to ints for now because of readability, we may change it later for performance.
 */


class Gomoku
{

#define GET_OPPONENT(piece) ((piece == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK)
#define IS_CAPTURE(board, move, dir) (this->get_piece(board, move + dir) == GET_OPPONENT(piece)\
                                        && this->get_piece(board, move + (dir * 2)) == GET_OPPONENT(piece)\
                                            && this->get_piece(board, move + (dir * 3)) == piece)

#define FLIP_CAPTURE(capture) t_capture_count{capture.minimizer_count, capture.maximizer_count}

#define GET_CURRENT_PLAYER() ((this->_turn % 2 == 0) ? this->_first_player : this->_second_player)
#define GET_OPPONENT_PLAYER() ((this->_turn % 2 == 0) ? this->_second_player : this->_first_player)
#define GET_BOARD_CENTER() t_coord{((this->_board_size / 2)), ((this->_board_size / 2))}

#define PRINT_COORD(coord) std::cout << coord;
#define PRINT_CAPTURE_COUNT() std::cout << (int)this->_first_player.capture_count << " " << (int)this->_second_player.capture_count << std::endl
#define PRINT_PLAYER_WIN(player) std::cout << "Player " << player << " wins !" << std::endl
#define PRINT_PLAYER_FORFEIT(player) std::cout << "Player " << player << " forfeits !" << std::endl
#define PRINT_DELINEATION() std::cout << "-------------------------------------" << std::endl

#define MAX_CAPTURE 5U
#define LONG_PRO_SIZE 7
#define PRO_SIZE 5

    public:
        typedef enum        e_piece
        {
            EMPTY = 0b00,
            BLACK = 0b01,
            WHITE = 0b10,
            ERROR = 0b11,
        }                   t_piece;

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
            PLAYER,
            EASY,
            MEDIUM,
            HARD
        }                   t_difficulty;

        typedef enum        e_scores
        {
            ILLEGAL_SCORE          = -10000000,
            WINNING_SCORE          = 1000000,
            WIN_BLOCK_SCORE        = 500000,
            CAPTURE_SCORE          = 100000,
            FREE_FOUR_SCORE        = 20000,
            FREE_BLOCK_SCORE       = 2000,
            FREE_SCORE             = 2000,
            FOUR_SCORE             = 1000,
            THREE_SCORE            = 100,
            TWO_SCORE              = 10,
            ONE_SCORE              = 1,
            ZERO_SCORE             = 0
        }                   t_scores;

        typedef enum        e_pattern_mask
        {
            SIX_MASK  = 0b111111111111,
            FIVE_MASK = 0b1111111111,
            FOUR_MASK = 0b11111111,
        }                   t_pattern_mask;

        typedef enum        e_update_type
        {
            ADD,
            REMOVE
        }                   t_update_type;

        struct      s_coord
        {
            int x;
            int y;

            s_coord() : x(0), y(0) {}
            s_coord(int x, int y) : x(x), y(y) {}
            s_coord(const s_coord& coord) : x(coord.x), y(coord.y) {}
            s_coord& operator=(const s_coord& rhs)
            {
                this->x = rhs.x;
                this->y = rhs.y;
                return (*this);
            }
            bool operator==(const s_coord& rhs) const
            {
                return (this->x == rhs.x && this->y == rhs.y);
            }
            
            s_coord operator+(const s_coord& rhs) const
            {
                return (s_coord{this->x + rhs.x, this->y + rhs.y});
            }

            s_coord operator-(const s_coord& rhs) const
            {
                return (s_coord{this->x - rhs.x, this->y - rhs.y});
            }

            s_coord operator*(const s_coord& rhs) const
            {
                return (s_coord{this->x * rhs.x, this->y * rhs.y});
            }

            s_coord operator*(const int& rhs) const
            {
                return (s_coord{this->x * rhs, this->y * rhs});
            }

            void operator+= (const s_coord& rhs)
            {
                this->x += rhs.x;
                this->y += rhs.y;
            }

            void operator-= (const s_coord& rhs)
            {
                this->x -= rhs.x;
                this->y -= rhs.y;
            }

            bool operator< (const s_coord& rhs) const
            {
                return (this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y));
            }
            friend std::ostream& operator<<(std::ostream& os, const s_coord& coord)
            {
                return (os << coord.x << " " << coord.y << std::endl);
            }
        };

        typedef struct      s_coord t_coord;

        typedef struct                  s_player
        {
            t_piece                     piece;
            uint8_t                     capture_count;
            t_coord (Gomoku::*move)(s_player&,s_player&);
            t_difficulty                difficulty;
        }                               t_player;

        typedef struct      t_move_update
        {
            t_coord         coord;
            t_piece         piece;
            t_update_type   type;
        }                   t_move_update;

        typedef std::vector<t_move_update> t_update_list;
        typedef struct      s_scored_move
        {
            t_coord         coord;
            int64_t         score;
        }                   t_scored_move;

        typedef struct      s_scored_update
        {
            uint8_t         cupture_count;
            t_scored_move   move;
            t_update_list   updates;
        }                   t_scored_update;

        typedef struct      s_prunner
        {
            int64_t alpha;
            int64_t beta;
        }                   t_prunner;

        typedef struct      s_capture_count
        {
            uint8_t         maximizer_count;
            uint8_t         minimizer_count;
        }                   t_capture_count;

        struct moveComparator {
            inline bool operator()(const t_scored_update& f_update, const t_scored_update& s_update) const {
                if (f_update.move.score > s_update.move.score)
                    return (f_update.move.score > s_update.move.score);
                return (f_update.move.coord < s_update.move.coord);
            }
        };

    private:

        typedef std::map< Gomoku::e_piece, std::map<uint16_t, t_scores> >       t_patterns;
        typedef std::set<t_coord>                                               t_moveset;
        typedef std::set<t_scored_update, moveComparator>                       t_sorted_updates;

    private:


        const static std::array<t_coord, 4>     _directions;
        const static std::vector<t_coord>       _moveset_cells;

        const static t_patterns                 _attack_patterns;
        const static t_patterns                 _defense_patterns;
        const static t_patterns                 _illegal_patterns;
        const static t_patterns                 _capture_patterns;
        const static t_coord                    _invalid_coord;

        uint8_t                                 _board_size;
        uint8_t                                 _depth;
        t_player                                _first_player;
        t_player                                _second_player;
        t_capture_count                         _capture_count;
        size_t                                  _turn;
        t_rule                                  _rule;

    public:
        uint64_t*                               _board;
        t_moveset                               _ai_moveset;

    public:
                                Gomoku(uint8_t board_size, t_difficulty first_difficulty,
                                            t_difficulty second_difficulty, t_player_type first_player_type,
                                                t_player_type second_player_type, t_rule rule);
                                ~Gomoku();
        void                    start_game();
    private:
        t_piece                 get_piece(uint64_t *board, t_coord piece_coord);
        t_coord                 ai_move(t_player& player, t_player& opponent);
        t_moveset               generate_rule_moveset(t_piece piece);
        t_player                get_player(t_player_type player_type, t_piece player_color, t_difficulty difficulty);
        t_coord                 human_move(t_player& player, t_player& opponent);
        t_scored_move           minimizer(t_moveset& moveset, uint64_t* board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece);
        t_scored_move           maximizer(t_moveset& moveset, uint64_t* board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece);
        t_sorted_updates        generate_sorted_updates(t_moveset& moveset, uint64_t* board, t_piece piece);
        int64_t                 evaluate_board(uint64_t *board, t_piece player_color, t_capture_count capture_count);
        int32_t                 evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction, bool capture = false);
        int32_t                 evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece);
        void                    make_move(t_player& player, t_player& opponent);
        void                    generate_scored_update(uint64_t* board, t_coord move, t_piece piece, t_scored_update& scored_update);
        void                    update_game_state(t_coord current_move, t_player& player);
        void                    update_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    revert_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    extract_captured_stoned(uint64_t *board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece);
        void                    add_board_piece(uint64_t *board, t_coord piece_coord, t_piece piece);
        void                    remove_board_piece(uint64_t* board, t_coord piece_coord);
        void                    update_board(uint64_t *board, const t_update_list &update_list);
        void                    revert_board_update(uint64_t *board, const t_update_list &update_list);
        void                    print_board(t_piece current_piece);
        void                    print_patterns(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        bool                    is_move_valid(t_coord piece_coord, t_piece piece);
        bool                    is_winning_move(uint64_t* board, t_piece piece, t_coord move, uint8_t capture_count);
        bool                    is_inside_square(t_coord piece_coord);
        char                    get_game_command();
};
