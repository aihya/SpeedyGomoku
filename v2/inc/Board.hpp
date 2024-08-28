#include <unistd.h>
#include <limits>
#include <memory>   // For std::unique_ptr
#include <cstring>
#include <stdexcept>
#include "Board.utils.hpp"

class  Board {
    typedef t_coord (Board::*position_func)(t_coord) const;
    typedef struct s_evaluation_edges {
        std::pair<int, int> x;
        std::pair<int, int> y;
    } t_evaluation_edges;

    public:
        uint64_t *original;
        uint8_t   size;
        t_evaluation_edges                        _evaluation_edges;

        const static t_patterns                 _attack_patterns;
        const static t_patterns                 _illegal_patterns;
        const static t_patterns                 _capture_patterns;

    public:
        Board(uint8_t size);
        ~Board();
        void validate_coord(t_coord position);
        void set_position(t_coord position, t_piece piece);
        inline t_piece get_piece(t_coord piece_coord, t_board_type type);
        inline void remove_piece(t_coord position);
        t_coord original_position(t_coord position) const;
        t_coord vertical_position(t_coord position) const;
        t_coord diagonal_position(t_coord position) const;
        int64_t evaluate_board(t_piece player_color);
        int64_t evaluate_position(t_coord pos, t_piece color, t_board_type type);

    private:
        void update_board(uint64_t *board, t_coord pos, t_piece piece);
};