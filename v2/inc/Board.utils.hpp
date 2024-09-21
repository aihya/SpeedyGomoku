#pragma once
#define POSITION_WEIGHT 10000
#define CENTER_BONUS 5000
#define EDGE_PENALTY -3000
#define GET_OPPOSITE_PIECE(piece) (piece == BLACK ? WHITE : BLACK)
#include <iostream>
#include <cstdint>
#include <deque>
#include <map>
#include <set>

typedef enum        e_piece
{
    EMPTY = 0b00,
    BLACK = 0b01,
    WHITE = 0b10,
    ERROR = 0b11
}                   t_piece;

typedef enum        e_scores
{
    ILLEGAL_SCORE          = -1,

    WIN_SCORE              = INT64_MAX,
    FIVE_SCORE             = 2000000,
    OPEN_FOUR_SCORE        = 1000000,
    FIVE_BLOCK_SCORE       = 1000000,
    CAPTURE_SCORE          = 5000,
    FOUR_SCORE             = 10000,
    OPEN_THREE_SCORE       = 1000,
    OPEN_BLOCK_SCORE       = 1000,
    THREE_SCORE            = 100,
    OPEN_TWO_SCORE         = 10,
    TWO_SCORE              = 10,
    ZERO_SCORE             = 0
}                   t_scores;


typedef std::map< t_piece, std::unordered_map<uint16_t, t_scores> > t_patterns;
typedef std::unordered_map<uint16_t, t_scores>      t_scores_map;

// typedef std::unordered_map<t_piece, coord_hash> t_board;

// add overload of << to print piece
inline std::ostream& operator<<(std::ostream& os, const t_piece& piece)
{
    switch (piece)
    {
        case EMPTY:
            os << ".";
            break;
        case BLACK:
            os << "X";
            break;
        case WHITE:
            os << "O";
            break;
        case ERROR:
            os << "*";
            break;
    }
    return os;
};

typedef struct      s_coord
{
    int x;
    int y;

    s_coord() : x(0), y(0) {}
    s_coord(int x, int y) : x(x), y(y) {}
    s_coord(const s_coord& coord) : x(coord.x), y(coord.y) {}
    s_coord& operator=(const s_coord& rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        return (*this);
    }

    bool operator==(const s_coord& rhs) const {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    s_coord operator+(const s_coord& rhs) const {
        return (s_coord{this->x + rhs.x, this->y + rhs.y});
    }

    s_coord operator-(const s_coord& rhs) const {
        return (s_coord{this->x - rhs.x, this->y - rhs.y});
    }

    s_coord operator*(const int& rhs) const {
        return (s_coord{this->x * rhs, this->y * rhs});
    }

    void operator+= (const s_coord& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
    }

    void operator-= (const s_coord& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
    }

    bool operator != (const s_coord& rhs) {
        return (this->x != rhs.x || this->y != rhs.y);
    }

    bool operator < (const s_coord& rhs) const {
        return (this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y));
    }

    friend std::ostream& operator<<(std::ostream& os, const s_coord& coord)
    {
        return (os << coord.x << " " << coord.y << std::endl);
    }

}                    t_coord;
// hash function for unordered set
struct coord_hash {
    std::size_t operator()(const t_coord& coord) const {
        return (coord.x * coord.x + 3 * coord.x + 2 * coord.x * coord.y + coord.y * coord.y) / 2;
    }
};

typedef struct  s_evaluation_edges {
    std::pair<int, int> x;
    std::pair<int, int> y;
}               t_evaluation_edges;

typedef enum    e_update_target {
    ILLEGAL,
    MOVESET,
    BOARD,
}               t_update_target;

inline std::ostream& operator<<(std::ostream& os, const t_update_target& target) {
    switch (target)
    {
        case ILLEGAL:
            os << "ILLEGAL";
            break;
        case MOVESET:
            os << "MOVESET";
            break;
        case BOARD:
            os << "BOARD";
            break;
    }
    return os;
};

typedef enum    e_update_type {
    ADD,
    REMOVE
}               t_update_type;

inline std::ostream& operator<<(std::ostream& os, const t_update_type& type) {
    switch (type)
    {
        case ADD:
            os << "ADD";
            break;
        case REMOVE:
            os << "REMOVE";
            break;
    }
    return os;
};

typedef struct s_scored_coord {
    int64_t score;
    t_coord coord;

    bool operator < (const s_scored_coord& rhs) const {
        return (this->score < rhs.score);
    }
    
    // add operator -  to multiply score by -1
    s_scored_coord operator-() const {
        return s_scored_coord{-this->score, this->coord};
    }
}               t_scored_coord;
typedef struct s_scored_moveset {
    int64_t     score;
    uint64_t    count;
    bool        blocked;
}               t_scored_moveset;
typedef struct  s_moveset_update {
    t_scored_moveset    old_moveset;
    t_scored_moveset    new_moveset;
}               t_moveset_update;

typedef struct  s_board_update {
    t_piece     piece;
}               t_board_update;

typedef struct  s_update {
    t_update_target                 target;
    t_update_type                   type;
    t_coord                         pos;
    t_piece                         piece;
    t_moveset_update                moveset_update[2];
}               t_update;


struct DualColorPotential {
    int64_t black_potential;
    int64_t white_potential;
};

typedef std::unordered_map<t_coord, uint16_t, coord_hash>           t_moves;
typedef std::unordered_map<t_coord, s_scored_moveset, coord_hash>   t_moveset;
typedef std::deque<t_update>                                        t_updates;
typedef std::vector<s_scored_coord>                                 t_ordered_moves;