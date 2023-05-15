#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <string.h>
#include <chrono>
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

#define GET_OPPONENT(piece) ((piece == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK)

class Gomoku
{
    public:
        typedef enum        e_piece
        {
            EMPTY = 0b00,
            BLACK = 0b01,
            WHITE = 0b10,
            ERROR = 0b11,
        }                   t_piece;
        
        typedef enum        e_difficulty
        {
            EASY,
            MEDIUM,
            HARD
        }                   t_difficulty;

        typedef enum        e_scores
        {
            ILLEGAL_SCORE = -1000000,
            WINNING_SCORE = 10000000,
            FOUR_SCORE    = 100000,
            CAPTURE_SCORE = 5000,
            THREE_SCORE   = 1000,
            TWO_SCORE     = 100,
            ONE_SCORE     = 10,
            ZERO_SCORE    = 0
        }                   t_scores;

        typedef enum        e_pattern_size
        {   
            SIX  = 6,
            FIVE = 5,
            FOUR = 4
        }                   t_pattern_size;

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

        typedef struct      s_coord
        {
            short           x;
            short           y;
        }                   t_coord;

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

        struct coordComparator {
            inline bool operator()(const t_coord& f_coord, const t_coord& s_coord) const {
                return  (f_coord.x == s_coord.x) ? f_coord.y < s_coord.y : f_coord.x < s_coord.x;
            }
        };
        struct moveComparator {
            inline bool operator()(const t_scored_update& f_update, const t_scored_update& s_update) const {
                if (f_update.move.score > s_update.move.score)
                    return (f_update.move.score > s_update.move.score);
                return  (f_update.move.coord.x == s_update.move.coord.x) ? f_update.move.coord.y < s_update.move.coord.y : f_update.move.coord.x < s_update.move.coord.x;
            }
        };

    private:

        typedef std::map< Gomoku::e_piece, std::map<uint16_t, t_scores> >       t_patterns;
        typedef std::set<t_coord, coordComparator>                              t_moveset;
        typedef std::set<t_scored_update, moveComparator>                       t_sorted_updates;

    private:


        const static std::array<t_coord, 4>     _directions;

        const static t_patterns                 _attack_patterns;
        const static t_patterns                 _defense_patterns;
        const static t_patterns                 _illegal_patterns;
        const static t_patterns                 _capture_patterns;

        uint8_t                                 _board_size;
        uint8_t                                 _depth;
        t_piece                                 _ai_color;
        t_piece                                 _player_color;
        t_difficulty                            _difficulty;
        t_coord                                 _last_move;
        size_t                                  _turn;

    public:
        std::list<uint64_t*>                    _move_history;
        t_moveset                               _ai_moveset;

    public:
                    Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty);
                    ~Gomoku();
        void        register_move(t_coord piece_coord, t_piece piece, uint64_t* board, t_moveset& moveset);
        void        print_board();
        void        make_move(t_coord piece_coord);
        bool        is_move_valid(t_coord piece_coord, t_piece piece);
        bool        is_player_turn()
        {
            return (this->_player_color == ((this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK));
        }
        t_piece        get_current_piece()
        {
            return (((this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK));
        };
    private:
        int64_t                 evaluate_board(uint64_t *board);
        t_piece                 get_piece(uint64_t *board, t_coord piece_coord);
        t_coord                 get_bot_move();
        void                    update_ai_moveset(uint64_t *board, t_moveset &possible_moves, t_coord piece_coord);
        // void                    update_board(uint64_t *board, t_coord piece_coord, t_piece piece);
        void                    clear_board_cell(uint64_t* board, t_coord piece_coord);
        uint64_t                *copy_board(uint64_t *board);
        // int32_t                 evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        int32_t                 evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        int32_t                 evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece);
        t_scored_move            minimax(t_moveset& moveset, uint64_t* board, uint8_t depth, int64_t alpha, int64_t beta, bool max);
        t_scored_move            minimizer(t_moveset& moveset, uint64_t* board, uint8_t depth, t_prunner prunner, t_piece piece);
        t_scored_move            maximizer(t_moveset& moveset, uint64_t* board, uint8_t depth, t_prunner prunner, t_piece piece);
        bool                    is_winning_move(uint64_t* board, t_piece piece, t_coord move);
        void                    get_new_moveset(uint64_t *board, t_moveset &possible_moves, t_moveset &old_moves, t_coord piece_coord);
        void                    print_board(uint64_t *board, t_moveset& moveset);
        t_sorted_updates        generate_sorted_updates(t_moveset& moveset, uint64_t* board, t_piece piece);
        void                    generate_update_list(uint64_t* board, t_coord move, t_piece piece, t_update_list& update_list);
        void                    extract_captured_stoned(uint64_t *board, t_coord move, t_piece piece, t_update_list& update_list);
        void                    get_new_moveset(uint64_t *board, t_moveset &possible_moves, t_moveset &old_moveset, t_update_list& update_list);
        void                    update_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    revert_node_state(uint64_t *board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    extract_captured_stoned(uint64_t *board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece);
        uint16_t                extract_pattern(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction, uint8_t pattern_size);
        t_scores                check_pattern_chunck(uint16_t pattern, t_pattern_mask mask, t_piece piece, const t_patterns &pattern_map);
        bool                    is_pattern_illegal(uint16_t pattern, t_piece piece);


        void                    add_board_piece(uint64_t *board, t_coord piece_coord, t_piece piece);
        void                    remove_board_piece(uint64_t* board, t_coord piece_coord);
        void                    update_board(uint64_t *board, const t_update_list &update_list);
        void                    revert_board_update(uint64_t *board, const t_update_list &update_list);

        t_scored_update         generate_move_update(uint64_t* board, t_piece piece, t_coord move);
        void                    update_game_state(uint64_t *board, t_moveset &moveset, const t_update_list& update_list);
        int32_t                evaluate_special_pattern(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
};
