#include <unistd.h>
#include <limits>
#include <memory>   // For std::unique_ptr
#include <cstring>
#include <stdexcept>
#include "Board.utils.hpp"

class  Board {

    public:
        uint64_t                            *board;
        uint8_t                             size;
        const static std::array<t_coord, 4> _directions;
        const static std::vector<t_coord>   _moveset_cells;

    private:
        uint64_t*                           _illegal_boards[2] = {nullptr};
        uint8_t                             _capture_count[2];
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
        void            validate_coord(t_coord position, t_piece piece) const;
        void            set_position(t_coord position, t_piece piece);
        inline t_piece  get_piece(t_coord piece_coord) const;
        inline t_piece  get_piece(uint64_t *board, t_coord piece_coord) const;
        inline void     remove_piece(t_coord position);
        int64_t         evaluate_board(t_piece player_color);
        int64_t         evaluate_position(t_coord pos, t_piece color, t_coord dir, const t_scores_map &patterns);
        void            print_board(t_piece curr_piece) const;
        void            make_move(t_coord pos, t_piece piece);

    private:
        void            update_board(uint64_t *board, t_coord pos, t_piece piece);
        bool            check_for_win(t_coord pos, t_piece color, t_coord dir) const;
        bool            possible_capture(t_coord pos, t_piece color, t_coord dir) const;
        uint8_t         capture_pattern(t_coord pos, t_coord dir, t_piece piece) const;
        void            update_node(t_board_update_queue& updates_queue, const t_board_update& curr_update);
        void            update_board(t_board_update_queue& updates_queue);
        bool            evaluate_capture(t_coord pos, t_coord dir);
        DualColorPotential  position_potential(t_coord pos, t_coord dir);
        void                evaluate_position(t_coord pos);
};