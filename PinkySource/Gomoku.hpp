#pragma once

#include <iostream>
#include <limits>
#include <map>
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
            WHITE = 0b10
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
        typedef struct      s_board
        {
            uint64_t        *board_buffer;
            uint8_t         board_size;
            struct s_board  *next;
            struct s_board  *prev;
        }                   t_board;

    private:
        typedef std::map< Gomoku::e_piece, std::map<uint16_t, uint16_t> > t_patterns;
        const static std::vector<t_coord>   _directions;
        const static t_patterns             _attack_patterns;
        const static t_patterns             _defense_patterns;
    
    private:
        t_board         *_move_history;
        t_piece         _ai_color;
        t_piece         _player_color;
        t_difficulty    _difficulty;
        size_t          _turn;

    public:
                Gomoku(uint8_t board_size, t_piece player_color, t_difficulty difficulty);
                ~Gomoku();
        void    register_move(t_coord piece_coord, t_piece piece);
        void        print_board();
        uint64_t    test_evaluate_board(t_piece piece);

    private:
        t_board     *update_board(t_board *board, t_coord piece_coord, t_piece piece);
        t_board     *new_board(size_t board_size);
        t_board     *copy_board(t_board *board);
        t_piece     get_piece(t_board *board, t_coord piece_coord);
        void        push_move(t_board *board);
        t_board     *minimax(t_board *board, t_piece piece, size_t depth);
        t_board     *maximize(t_board *board, t_piece piece, size_t depth, size_t aplha);
        t_board     *minimize(t_board *board, t_piece piece, size_t depth, size_t beta);
        uint64_t    evaluate_move(t_board *board, t_coord piece_coord, t_piece piece);
        uint64_t    evaluate_dir(t_board *board, t_coord piece_coord, t_piece piece, t_coord direction);

};
