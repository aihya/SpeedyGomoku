#pragma once

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <string.h>
#include <chrono>
#include <array>
#include "TTable.hpp"
#include "ZobristTable.hpp"
#include <thread>
#include <atomic>
#include <unistd.h>
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

#define GET_OPPONENT(piece) ((piece == Gomoku::BLACK) ? Gomoku::WHITE : Gomoku::BLACK)
#define IS_CAPTURE(board, move, dir) (board.get_piece(move + dir) == GET_OPPONENT(piece)\
                                        && board.get_piece(move + (dir * 2)) == GET_OPPONENT(piece)\
                                            && board.get_piece(move + (dir * 3)) == piece)

#define FLIP_CAPTURE(capture) t_capture_count{capture.minimizer_count, capture.maximizer_count}
#define FLIP_PRUNNER(prunner) t_prunner{-prunner.beta, -prunner.alpha}
#define SW_PRUNNER(prunner) t_prunner{-prunner.alpha - 1, -prunner.alpha}
#define INITIAL_PRUNNER t_prunner{-INTMAX_MAX, INTMAX_MAX}

#define GET_CURRENT_PLAYER() ((this->_turn % 2 == 0) ? this->_first_player : this->_second_player)
#define GET_OPPONENT_PLAYER() ((this->_turn % 2 == 0) ? this->_second_player : this->_first_player)
#define GET_BOARD_CENTER(board) t_coord{((board.size / 2)), ((board.size / 2))}
#define STOP_GAME() this->_game_over = true
#define IS_GAME_OVER() this->_game_over


#define PRINT_COORD(coord) std::cout << coord;
#define PRINT_CAPTURE_COUNT() std::cout << (int)this->_first_player.capture_count << " " << (int)this->_second_player.capture_count << std::endl
#define PRINT_PLAYER_WIN(player) std::cout << "Player " << player << " wins !" << std::endl
#define PRINT_PLAYER_FORFEIT(player) std::cout << "Player " << player << " forfeits !" << std::endl
#define PRINT_DELINEATION() std::cout << "-------------------------------------" << std::endl

#define MAX_CAPTURE 5U
#define LONG_PRO_SIZE 7
#define PRO_SIZE 5

    public:
        typedef enum        e_piece
        {
            EMPTY = 0b00,
            BLACK = 0b01,
            WHITE = 0b10,
            ERROR = 0b11,
        }                   t_piece;

        typedef enum        e_rule
        {
            STANDARD,
            LONG_PRO,
            PRO,
        }                   t_rule;

        typedef enum        e_game_state
        {
            ONGOING,
            WIN,
            DRAW
        }                   t_game_state;

        typedef enum        e_player_type
        {
            HUMAN,
            AI
        }                   t_player_type;     
        typedef enum        e_difficulty
        {
            PLAYER,
            EASY,
            MEDIUM,
            HARD
        }                   t_difficulty;

        typedef enum        e_scores
        {
            ILLEGAL_SCORE          = -1,

            FIVE_SCORE             = 1000001,
            OPEN_FOUR_SCORE        = 1000000,
            FIVE_BLOCK_SCORE       = 1000000,
            CAPTURE_SCORE          = 20000,
            FOUR_SCORE             = 1000,
            OPEN_THREE_SCORE       = 100,
            OPEN_BLOCK_SCORE       = 100,
            THREE_SCORE            = 10,
            OPEN_TWO_SCORE         = 10,
            TWO_SCORE              = 1,
            ZERO_SCORE             = 0
        }                   t_scores;

        typedef enum        e_pattern_mask
        {
            SIX_MASK  = 0b111111111111,
            FIVE_MASK = 0b1111111111,
            FOUR_MASK = 0b11111111,
            THREE_MASK = 0b111111,
            TWO_MASK = 0b1111,
        }                   t_pattern_mask;

        typedef enum        e_update_type
        {
            ADD,
            REMOVE
        }                   t_update_type;

        struct      s_coord
        {
            int x;
            int y;

            s_coord() : x(0), y(0) {}
            s_coord(int x, int y) : x(x), y(y) {}
            s_coord(const s_coord& coord) : x(coord.x), y(coord.y) {}
            s_coord(std::pair<int, int> coord) : x(coord.first), y(coord.second) {}
            s_coord& operator=(const s_coord& rhs)
            {
                this->x = rhs.x;
                this->y = rhs.y;
                return (*this);
            }
            bool operator==(const s_coord& rhs) const
            {
                return (this->x == rhs.x && this->y == rhs.y);
            }
            
            bool operator!=(const s_coord& rhs) const
            {
                return (this->x != rhs.x || this->y != rhs.y);
            }

            s_coord operator+(const s_coord& rhs) const
            {
                return (s_coord{this->x + rhs.x, this->y + rhs.y});
            }

            s_coord operator-(const s_coord& rhs) const
            {
                return (s_coord{this->x - rhs.x, this->y - rhs.y});
            }

            s_coord operator*(const s_coord& rhs) const
            {
                return (s_coord{this->x * rhs.x, this->y * rhs.y});
            }

            s_coord operator*(const int& rhs) const
            {
                return (s_coord{this->x * rhs, this->y * rhs});
            }

            void operator+= (const s_coord& rhs)
            {
                this->x += rhs.x;
                this->y += rhs.y;
            }

            void operator-= (const s_coord& rhs)
            {
                this->x -= rhs.x;
                this->y -= rhs.y;
            }

            bool operator< (const s_coord& rhs) const
            {
                return (this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y));
            }
            friend std::ostream& operator<<(std::ostream& os, const s_coord& coord)
            {
                return (os << coord.x << " " << coord.y << std::endl);
            }
        };

        typedef struct      s_coord t_coord;


        typedef struct      t_move_update
        {
            t_coord         coord;
            t_piece         piece;
            t_update_type   type;
        }                   t_move_update;

        typedef std::vector<t_move_update> t_update_list;
        typedef struct      s_scored_move
        {
            t_coord         coord;
            int64_t         score;
            bool            winning;

            // overload of unary minus operator
            s_scored_move operator-() const
            {
                return (s_scored_move{this->coord, -this->score, this->winning});
            }
        }                   t_scored_move;

        typedef struct      s_scored_update
        {
            uint8_t         cupture_count;
            t_scored_move   move;
            t_update_list   updates;
            inline bool operator< (const s_scored_update& s_update) const {
                return (this->move.score > s_update.move.score || (this->move.coord < s_update.move.coord));
            }
        }                   t_scored_update;
        typedef struct s_board
        {
            uint64_t        *data;
            uint8_t         size;
            uint64_t        hash;
            ZobristTable    *zobrist_table;

            s_board(uint8_t size) : size(size), hash(0) {
                this->data = new uint64_t[size];
                for (uint8_t i = 0; i < size; i++)
                    this->data[i] = 0;
                this->zobrist_table = new ZobristTable(size * size, 2);
            }

            ~s_board() {
                delete this->zobrist_table;
                delete this->data;
            }
            
            inline void add_piece(t_coord piece_coord, t_piece piece)
            {
                this->data[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
                this->update_hash(piece_coord, piece);
            }

            inline void remove_piece(t_coord piece_coord)
            {
                this->update_hash(piece_coord, this->get_piece(piece_coord));
                this->data[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            }
            
            inline t_piece get_piece(t_coord piece_coord)
            {
                if (piece_coord.x >= this->size || piece_coord.y >= this->size)
                    return (Gomoku::ERROR);
                if (piece_coord.x < 0 || piece_coord.y < 0)
                    return (Gomoku::ERROR);
                return (t_piece)((this->data[piece_coord.y] >> (piece_coord.x << 1)) & 3);
            }

            inline uint64_t get_cell_value(t_coord piece_coord, t_piece piece)
            {
                return (this->zobrist_table->get(piece % 2, piece_coord.y * this->size + piece_coord.x));
            }

            inline void update_hash(t_coord piece_coord, t_piece piece)
            {
                this->hash ^= this->get_cell_value(piece_coord, piece);
            }
        }            t_board;
        typedef struct                  s_player
        {
            t_piece                     piece;
            uint8_t                     capture_count;
            t_coord (Gomoku::*move)(s_player&,s_player&, t_board&);
            t_difficulty                difficulty;
        }                               t_player;
        typedef struct      s_prunner
        {
            int64_t alpha;
            int64_t beta;
        }                   t_prunner;

        typedef struct      s_capture_count
        {
            uint8_t         maximizer_count;
            uint8_t         minimizer_count;
        }                   t_capture_count;

        typedef struct      s_move_occurence
        {
            t_coord         coord;
            uint8_t         occurence;

            bool operator< (const s_move_occurence& rhs) const
            {
                return (this->coord < rhs.coord);
            }
        }                   t_move_occurence;

        // instead of having and added moveset set for each node we can make the moveset know if it's been added or not
        typedef struct    s_move
        {
            t_coord         coord;
            uint8_t         dependency_count;

            s_move(t_coord coord, uint8_t dependency_count) : coord(coord), dependency_count(dependency_count) {}
            s_move(t_coord coord) : coord(coord), dependency_count(0) {}
        }                 t_move;
    private:

        typedef std::map< Gomoku::e_piece, std::map<uint16_t, t_scores> >       t_patterns;
        // typedef std::map<t_coord, int>                                          t_moveset;
        typedef std::set<t_coord>                                               t_moveset;// <-- each time we add a move we increment the dependency count of the move it's generating
        typedef std::vector<t_coord>                                            t_sequence;
        typedef std::set<t_scored_update>                                       t_sorted_updates;

    private:


        const static std::array<t_coord, 4>     _directions;
        const static std::vector<t_coord>       _moveset_cells;

        const static t_patterns                 _attack_patterns;
        const static t_patterns                 _defense_patterns;
        const static t_patterns                 _illegal_patterns;
        const static t_patterns                 _capture_patterns;
        const static t_coord                    _invalid_coord;

        uint8_t                                 _depth;
        t_player                                _first_player;
        t_player                                _second_player;
        t_capture_count                         _capture_count;
        size_t                                  _turn;
        t_rule                                  _rule;
        bool                                    _game_over;
        TTable                                  _ttable;
        uint8_t                                 _current_depth;
        t_coord                                 _last_best;
        double                                  average_time;
    public:

        t_board                                 _board;
        t_moveset                               _ai_moveset;

    public:
                                Gomoku(uint8_t board_size, t_difficulty first_difficulty,
                                            t_difficulty second_difficulty, t_player_type first_player_type,
                                                t_player_type second_player_type, t_rule rule);
                                ~Gomoku();
        void                    start_game();
    private:
        t_coord                 iterative_depth_search(t_moveset& moveset, t_board &board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece);
        t_coord                 human_move(t_player& player, t_player& opponent, t_board & board);
        t_coord                 ai_move(t_player& player, t_player& opponent, t_board & board);
        t_moveset               generate_rule_moveset(t_piece piece, t_board &board);
        t_player                get_player(t_player_type player_type, t_piece player_color, t_difficulty difficulty);
        t_scored_move           negascout(t_moveset& moveset, t_board &board, uint8_t depth, t_prunner prunner, t_capture_count count, t_piece piece);
        // t_sorted_updates        generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece);
        t_sorted_updates        generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece, uint8_t depth = 0);
        t_sequence              extract_winning_sequence(t_board &board, t_piece piece, t_coord start_coord);
        int64_t                 evaluate_board(t_board &board, t_piece player_color, t_capture_count capture_count);
        int32_t                 evaluate_move(t_board &board, t_coord piece_coord, t_piece piece, t_coord direction);
        int64_t                 evaluate_pattern(t_board& board, t_coord start, t_piece player_color, std::set<std::pair<t_coord, t_coord>> &head_tail_set);
        void                    make_move(t_player& player, t_player& opponent, t_board& board);
        void                    update_ttable(t_board& board, t_scored_move& best_move, uint8_t depth, int64_t alpha, int64_t beta);
        void                    generate_scored_update(t_board &board, t_coord move, t_piece piece, t_scored_update& scored_update);
        void                    update_game_state(t_board& board, t_player& player, t_coord current_move);
        void                    update_node_state(t_board &board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    revert_node_state(t_board &board, t_moveset &added_moves, t_moveset &moveset, const t_update_list& update_list);
        void                    extract_captured_stoned(t_board &board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece);
        void                    update_board(t_board &board, const t_update_list &update_list);
        void                    revert_board_update(t_board &board, const t_update_list &update_list);
        void                    print_board(t_board &board, t_piece current_piece);
        bool                    is_move_valid(t_board& board, t_coord piece_coord, t_piece piece);
        bool                    is_winning_move(t_board &board, t_moveset &moveset, t_piece piece, t_coord move, uint8_t capture_count);
        bool                    is_inside_square(t_board& board, t_coord piece_coord);
        char                    get_game_command();

        bool                    is_game_finished(t_board& board, t_capture_count capture_count);
};
