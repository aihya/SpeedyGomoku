#pragma once
#include <unistd.h>
#include <limits>
#include <memory>   // For std::unique_ptr
#include <cstring>
#include <stdexcept>
#include "Board.utils.hpp"
#include <algorithm>
#include <unordered_map>

class  Board {

    public:
        uint64_t                            *board;
        uint8_t                             size;
        const static std::array<t_coord, 4> _directions;
        const static std::vector<t_coord>   _moveset_cells;
        int                                 _capture_count[2];

    private:
        uint64_t*                           _illegal_boards[2] = {nullptr};
        t_moves                             _illegal_positions[2];
        t_moveset                           _moveset_positions[2];
        t_evaluation_edges                  _evaluation_edges;
        const static t_patterns             _attack_patterns;
        const static t_patterns             _illegal_patterns;
        const static t_patterns             _capture_patterns;
        const static t_patterns             _defense_patterns;

        static constexpr uint8_t            BLACK_CAPTURE_PATTERN = 0b01101001; // XOOX pattern for BLACK
        static constexpr uint8_t            WHITE_CAPTURE_PATTERN = ~BLACK_CAPTURE_PATTERN; // OXXO pattern for WHITE

    public:
                                    Board(uint8_t size);
                                    ~Board();
        void                        validate_coord(t_coord position, t_piece piece) const;
        int64_t                     evaluate_board(t_piece player_color) const;
        void                        print_board(t_piece curr_piece) const;
        size_t                      make_move(t_coord pos, t_piece piece, t_updates& updates_queue);
        t_ordered_moves             order_moves(t_piece color);
        void                        revert_updates(t_updates& updates, size_t count);
        DualColorPotential          position_potential(t_updates& updates_queue, t_coord pos, t_coord dir);
    private:
        inline void                 remove_piece(t_coord position);
        inline t_piece              get_piece(uint64_t *board, t_coord piece_coord) const;
        inline t_piece              get_piece(t_coord piece_coord) const;
        void                        set_position(t_coord position, t_piece piece);
        int64_t                     evaluate_position(t_coord pos, t_piece color, t_coord dir, const t_scores_map &patterns) const;
        void                        update_board(uint64_t *board, t_coord pos, t_piece piece);
        bool                        check_for_win(t_coord pos, t_piece color, t_coord dir) const;
        bool                        possible_capture(t_coord pos, t_piece color, t_coord dir) const;
        uint8_t                     capture_pattern(t_coord pos, t_coord dir, t_piece piece) const;
        void                        update_node(t_updates& updates_queue, t_coord curr_pos, t_piece curr_piece);
        bool                        evaluate_capture(t_coord pos, t_coord dir);
        void                        evaluate_new_move(t_updates &updates_queue, t_coord pos);
        void                        record_illegal_update(t_updates &updates_queue, t_coord pos, t_piece color, t_update_type type);
        void                        record_moveset_update(t_updates &updates_queue, t_coord pos, t_piece color, int64_t score, t_update_type type);
        void                        record_board_update(t_updates &updates_queue, t_coord pos, t_piece piece, t_update_type type);
        void                        revert_illegal_update(t_update& update);
        void                        revert_moveset_update(const t_update& update);
};
