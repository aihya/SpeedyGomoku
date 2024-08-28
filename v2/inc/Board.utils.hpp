#define POSITION_WEIGHT 10000
#define CENTER_BONUS 5000
#define EDGE_PENALTY -3000
#define GET_OPPOSITE_PIECE(piece) (piece == BLACK ? WHITE : BLACK)
#include <iostream>
#include <map>

typedef enum        e_piece
{
    EMPTY = 0b00,
    BLACK = 0b01,
    WHITE = 0b10,
    ERROR = 0b11
}                   t_piece;

typedef enum        e_board_type
{
    ORIGINAL,
    VERTICAL,
    DIAGONAL
}                   t_board_type;

typedef enum        e_scores
{
    ILLEGAL_SCORE          = -1,

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


typedef std::map< t_piece, std::unordered_map<uint16_t, t_scores> >       t_patterns;

// add overload of << to print piece
std::ostream& operator<<(std::ostream& os, const t_piece& piece)
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
            os << "_";
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

    void operator+= (const s_coord& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
    }

    void operator-= (const s_coord& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const s_coord& coord)
    {
        return (os << coord.x << " " << coord.y << std::endl);
    }
}                    t_coord;

typedef t_coord (position_func)(t_coord);

