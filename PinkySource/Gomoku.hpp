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
            WINNING_SCORE = 10000000,
            FOUR_SCORE    = 100000,
            CAPTURE_SCORE = 10000,
            THREE_SCORE   = 1000,
            TWO_SCORE     = 100,
            ONE_SCORE     = 10,
        }                   t_scores;

        typedef struct      s_coord
        {
            short           x;
            short           y;
        }                   t_coord;
        typedef struct      s_move_score
        {
            t_coord         coord;
            uint64_t        score;
        }                   t_move_score;

        struct coordComparator {
            inline bool operator()(const t_coord& f_coord, const t_coord& s_coord) const {
                return  (f_coord.x == s_coord.x) ? f_coord.y < s_coord.y : f_coord.x < s_coord.x;
            }
        };
        struct moveComparator {
            inline bool operator()(const t_move_score& f_move, const t_move_score& s_move) const {
                if (f_move.score > s_move.score)
                    return (f_move.score > s_move.score);
                return  (f_move.coord.x == s_move.coord.x) ? f_move.coord.y < s_move.coord.y : f_move.coord.x < s_move.coord.x;
            }
        };

    private:

        typedef std::map< Gomoku::e_piece, std::map<uint16_t, t_scores> >       t_patterns;
        typedef std::set<t_coord, coordComparator>                              t_moveset;
        typedef std::set<t_move_score, moveComparator>                          t_sorted_moveset;

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
        t_coord                                 _best_move;
        size_t                                  _turn;

    public:
        std::list<uint64_t*>                    _move_history;
        t_moveset                               _ai_moveset;

    public:
        t_coord     &get_best_move();

    public:
                    Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty);
                    ~Gomoku();
        void        register_move(t_coord piece_coord, t_piece piece, uint64_t* board, t_moveset& moveset);
        void        print_board();
        void        make_move(t_coord piece_coord);
        int64_t     evaluate_board(uint64_t *board);
        bool        is_move_valid(t_coord piece_coord);
        bool        is_player_turn()
        {
            return (this->_player_color == ((this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK));
        }

    private:
        t_piece             get_piece(uint64_t *board, t_coord piece_coord);
        void                make_move();
        void                update_ai_moveset(uint64_t *board, t_moveset &possible_moves, t_coord piece_coord);
        void                update_board(uint64_t *board, t_coord piece_coord, t_piece piece);
        void                clear_board_cell(uint64_t* board, t_coord piece_coord);
        uint64_t            *copy_board(uint64_t *board);
        uint32_t            evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        uint32_t            evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece);
        int64_t             minimax(t_moveset& moveset, uint64_t* board, uint8_t depth, int64_t alpha, int64_t beta, bool max);
        uint64_t            *maximize(uint64_t *board, t_piece piece, size_t depth, size_t aplha);
        uint64_t            *minimize(uint64_t *board, t_piece piece, size_t depth, size_t beta);
        bool                is_winning_move(uint64_t* board, t_piece piece, t_coord move);
        void                get_new_moveset(uint64_t *board, t_moveset &possible_moves, t_moveset &old_moves, t_coord piece_coord);
        void                print_board(uint64_t *board, t_moveset& moveset);
        t_sorted_moveset    generate_sorted_moveset(t_moveset& moveset, uint64_t* board, t_piece piece);
};
