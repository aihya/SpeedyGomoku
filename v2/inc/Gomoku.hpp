#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <Board.hpp>
#include "Gomoku.utils.hpp"

class Gomoku
{

    private:

        typedef struct                  s_player
        {
            t_piece                     piece;
            uint8_t                     capture_count;
            t_difficulty                difficulty;
            t_moveset                   moveset;
            t_coord (Gomoku::*move)(s_player&,s_player&, Board&);
        }                               t_player;

        uint8_t                                 _depth;
        t_player                                _first_player;
        t_player                                _second_player;
        size_t                                  _turn;
        t_rule                                  _rule;
        bool                                    _game_over;
    public:

        Board                                   _board;

    public:
                                Gomoku(uint8_t size, t_difficulty first_difficulty,
                                            t_difficulty second_difficulty, t_player_type first_player_type,
                                                t_player_type second_player_type, t_rule rule);
                                ~Gomoku();
        void                    start_game();
    private:
        t_coord                 human_move(t_player& player, t_player& opponent, Board & board);
        t_coord                 ai_move(t_player& player, t_player& opponent, Board & board);
        t_moveset               generate_rule_moveset(t_piece piece, Board &board);
        t_coord                 negascout(t_moveset& moveset, Board &board, uint8_t depth, t_prunner prunner);
        t_coord*                extract_winning_sequence(Board &board, t_piece piece, t_coord start_coord);
        int64_t                 evaluate_board(Board &board, t_piece player_color);
        int32_t                 evaluate_move(Board &board, t_coord piece_coord, t_piece piece, t_coord direction);
        int64_t                 evaluate_pattern(Board& board, t_coord start, t_piece player_color);
        void                    make_move(t_player& player, t_player& opponent, Board& board);
        void                    update_board(Board &board, const t_update_list &update_list, bool flip);
        int64_t                 evaluate_position(t_coord pos, t_coord center, int size);
        bool                    is_winning_move(Board &board, t_moveset &moveset, t_piece piece, t_coord move, uint8_t capture_count);
        bool                    is_valid_move(Board &board, t_coord move, t_piece piece);
        void                    revert_node_state(Board &board, t_player &player, const t_update_list& update_list);
        t_update_list           update_moveset(Board &board, t_player& player, t_coord move);
        
};
