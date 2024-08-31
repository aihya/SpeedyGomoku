#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include "Gomoku.utils.hpp"

class Gomoku
{

    private:

        typedef struct                  s_player
        {
            t_piece                     piece;
            uint8_t                     capture_count;
            t_coord (Gomoku::*move)(s_player&,s_player&, Board&);
            t_difficulty                difficulty;
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
        int64_t                 negascout(t_moveset& moveset, Board& board, uint8_t depth, t_prunner prunner);
        void                    make_move(t_player& player, t_player& opponent);
};
