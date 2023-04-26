#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <algorithm>
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

    private:
        typedef std::map< Gomoku::e_piece, std::map<uint16_t, uint32_t> > t_patterns;
        const static std::vector<t_coord>   _directions;
        const static t_patterns             _attack_patterns;
        const static t_patterns             _defense_patterns;
    
    public:
        uint8_t                 _board_size;
        std::list<uint64_t*>    _move_history;
        t_piece                 _ai_color;
        t_piece                 _player_color;
        t_difficulty            _difficulty;
        size_t                  _turn;

    public:
                    Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty);
                    ~Gomoku();
        void        register_move(t_coord piece_coord, t_piece piece);
        void        print_board();
        uint64_t    test_evaluate_board(t_piece piece);
        uint64_t    evaluate_move(uint64_t *board, t_coord piece_coord, t_piece piece);

    private:
        t_piece     get_piece(uint64_t *board, t_coord piece_coord);
        uint64_t    *copy_board(uint64_t *board);
        uint64_t    *update_board(uint64_t *board, t_coord piece_coord, t_piece piece);
        uint64_t    evaluate_dir(uint64_t *board, t_coord piece_coord, t_piece piece, t_coord direction);
        uint64_t    *minimax(uint64_t *board, size_t depth);
        uint64_t    *maximize(uint64_t *board, t_piece piece, size_t depth, size_t aplha);
        uint64_t    *minimize(uint64_t *board, t_piece piece, size_t depth, size_t beta);

};
