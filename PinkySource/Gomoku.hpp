#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <string.h>
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

        typedef struct      s_coord
        {
            short           x;
            short           y;
        }                   t_coord;
        struct coordComparator {
            inline bool operator()(const t_coord& f_coord, const t_coord& s_coord) const {
                return  (f_coord.x == s_coord.x) ? f_coord.y < s_coord.y : f_coord.x < s_coord.x;
            }
        };

    private:

        typedef std::map< Gomoku::e_piece, std::map<uint16_t, uint32_t> >    t_patterns;
        typedef std::set<t_coord, coordComparator>                          t_moveset;

        const static std::array<t_coord, 4>     _directions;
        const static t_patterns                 _attack_patterns;
        const static t_patterns                 _defense_patterns;
        const static t_patterns                 _illegal_patterns;
        const static t_patterns                 _capture_patterns;

        uint8_t                                 _board_size;
        uint8_t                                 _depth;
        t_moveset                               _ai_moveset;
        t_piece                                 _ai_color;
        t_piece                                 _player_color;
        t_difficulty                            _difficulty;
        t_coord                                 _best_move;
        size_t                                  _turn;

    public:
        std::list<uint64_t*>                    _move_history;

    public:
        t_coord     &get_best_move();

    public:
                    Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty);
                    ~Gomoku();
        void        register_move(t_coord piece_coord, t_piece piece, uint64_t* board, t_moveset& moveset);
        void        print_board();
        void        print_board(uint64_t *board, t_moveset &moveset);
        void        make_move(t_coord piece_coord);
        int64_t     evaluate_board(uint64_t *board);
        uint64_t    evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece);
        bool        is_move_valid(t_coord piece_coord);
        bool        is_player_turn()
        {
            return (this->_player_color == ((this->_turn % 2 == 0) ? Gomoku::WHITE : Gomoku::BLACK));
        }

    private:
        t_piece     get_piece(uint64_t *board, t_coord piece_coord);
        void        make_move();
        void        update_ai_moveset(uint64_t *board, t_moveset &possible_moves, t_coord piece_coord);
        void        update_board(uint64_t *board, t_coord piece_coord, t_piece piece);
        uint64_t    *copy_board(uint64_t *board);
        uint64_t    evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        int64_t     minimax(t_moveset& moveset, uint64_t* board, uint8_t depth,
                                int64_t alpha, int64_t beta, bool max);
        uint64_t    *maximize(uint64_t *board, t_piece piece, size_t depth, size_t aplha);
        uint64_t    *minimize(uint64_t *board, t_piece piece, size_t depth, size_t beta);

};
