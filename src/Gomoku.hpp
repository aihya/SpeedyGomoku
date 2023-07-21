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
#include <unordered_set>
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
#define IS_CAPTURE_WIN(board) (GET_CAPTURE(board, Gomoku::BLACK) >= MAX_CAPTURE || GET_CAPTURE(board, Gomoku::WHITE) >= MAX_CAPTURE)

#define PRINT_COORD(coord) std::cout << coord;
#define PRINT_CAPTURE_COUNT() std::cout << (int)GET_CAPTURE(board, this->_first_player.piece) << " " << (int)GET_CAPTURE(board, this->_second_player.piece) << std::endl
#define PRINT_PLAYER_WIN(player) std::cout << "Player " << player << " wins !" << std::endl
#define PRINT_PLAYER_FORFEIT(player) std::cout << "Player " << player << " forfeits !" << std::endl
#define PRINT_DELINEATION() std::cout << "-------------------------------------" << std::endl

#define MAX_CAPTURE 5U
#define LONG_PRO_SIZE 7
#define PRO_SIZE 5
#define MAX_BOARD_EVAL  INTMAX_MAX - 1000
#define MIN_BOARD_EVAL -INTMAX_MAX + 1000

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
            CAPTURE_SCORE          = 200000,
            FOUR_SCORE             = 10000,
            OPEN_THREE_SCORE       = 1000,
            OPEN_BLOCK_SCORE       = 1000,
            THREE_SCORE            = 100,
            OPEN_TWO_SCORE         = 100,
            TWO_SCORE              = 10,
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
            // overload of unary minus operator
            s_scored_move operator-() const
            {
                return (s_scored_move{this->coord, -this->score});
            }
        }                   t_scored_move;

        typedef struct      s_scored_update
        {
            uint8_t         cupture_count;
            t_scored_move   move;
            t_update_list   updates;
            inline bool operator> (const s_scored_update& s_update) const {
                return (this->move.score > s_update.move.score );
            }
        }                   t_scored_update;

        #define GET_CAPTURE(board, piece) ((piece == Gomoku::BLACK) ? board.capture_count.black_count : board.capture_count.white_count)
        typedef struct s_board
        {
            uint64_t        *data;
            uint8_t         size;
            uint64_t        hash;
            ZobristTable    *zobrist_table;
            union {
                struct {
                    uint8_t    black_count;
                    uint8_t    white_count;
                };
                uint16_t    capture_hash;
            } capture_count;

            s_board(uint8_t size) : size(size), hash(0), capture_count{0, 0}{
                this->data = new uint64_t[size];
                for (uint8_t i = 0; i < size; i++)
                    this->data[i] = 0;
                this->zobrist_table = new ZobristTable(size * size, 2);
            }

            ~s_board() {
                delete this->zobrist_table;
                delete this->data;
            }
            
            inline bool is_valid_coord(t_coord coord) const
            {
                return (coord.x >= 0 && coord.x < this->size && coord.y >= 0 && coord.y < this->size);
            }

            inline void add_piece(t_coord piece_coord, t_piece piece)
            {
                this->data[piece_coord.y] |= uint64_t(piece) << (piece_coord.x * 2);
                this->update_piece_hash(piece_coord, piece);
            }
            inline void add_capture(t_piece piece, uint8_t count)
            {
                if (piece == Gomoku::BLACK)
                    this->capture_count.black_count += count;
                else
                    this->capture_count.white_count += count;
                this->hash ^= this->capture_count.capture_hash;
            }

            inline void remove_capture(t_piece piece, uint8_t count)
            {
                this->hash ^= this->capture_count.capture_hash;
                if (piece == Gomoku::BLACK)
                    this->capture_count.black_count -= count;
                else
                    this->capture_count.white_count -= count;
            }

            inline void remove_piece(t_coord piece_coord)
            {
                this->update_piece_hash(piece_coord, this->get_piece(piece_coord));
                this->data[piece_coord.y] &= ~((uint64_t)(Gomoku::ERROR) << (piece_coord.x << 1));
            }
            
            inline t_piece get_piece(t_coord piece_coord)
            {
                if (!this->is_valid_coord(piece_coord))
                    return (Gomoku::ERROR);
                return (t_piece)((this->data[piece_coord.y] >> (piece_coord.x << 1)) & 3);
            }

            inline void update_piece_hash(t_coord piece_coord, t_piece piece)
            {
                this->hash ^= this->zobrist_table->get(piece >> 1, (piece_coord.y * this->size) + piece_coord.x);
            }
        }            t_board;
        typedef struct                  s_player
        {
            t_piece                     piece;
            t_coord (Gomoku::*move)(s_player&,s_player&, t_board&);
            t_difficulty                difficulty;
        }                               t_player;
        typedef struct      s_prunner
        {
            int64_t alpha;
            int64_t beta;
        }                   t_prunner;

        // instead of having and added moveset set for each node we can make the moveset know if it's been added or not
        typedef struct    s_move
        {
            t_coord         coord;
            uint8_t         dependency_count;

            s_move(t_coord coord, uint8_t dependency_count) : coord(coord), dependency_count(dependency_count) {}
            s_move(t_coord coord) : coord(coord), dependency_count(0) {}
            bool operator==(const s_move& lhs)
            {
                return (lhs.coord == coord && lhs.dependency_count == dependency_count);
            }
        }                 t_move;

    private:
        // Hash function for t_coord
        struct TCoordHash {
            std::size_t operator()(const t_coord& coord) const {
                std::size_t x_hash = std::hash<int>{}(coord.x);
                std::size_t y_hash = std::hash<int>{}(coord.y);
                return x_hash ^ y_hash;
            }
        };

        // Custom hash function for std::pair<t_coord, t_coord>
        struct PairHash {
            std::size_t operator()(const std::pair<t_coord, t_coord>& pair) const {
                std::size_t first_hash = TCoordHash{}(pair.first);
                std::size_t second_hash = TCoordHash{}(pair.second);
                return first_hash ^ (second_hash << 1);
            }
        };
        
        typedef std::map<uint16_t, t_scores>                               t_patterns;
        typedef std::map<Gomoku::e_piece, t_patterns>                      t_pattern_dict;
        typedef std::set<t_coord>                                          t_moveset;// <-- each time we add a move we increment the dependency count of the move it's generating
        typedef std::vector<t_coord>                                       t_sequence;
        typedef std::vector<t_scored_update>                               t_sorted_updates;
        typedef std::array<std::array<t_coord, 2>, 300>                    t_killer_move;
        typedef std::unordered_set<std::pair<t_coord, t_coord>, PairHash>  t_head_tail_set;

    private:


        const static std::array<t_coord, 4>     _directions;
        const static std::vector<t_coord>       _moveset_cells;

        const static t_pattern_dict             _attack_patterns;
        const static t_pattern_dict             _defense_patterns;
        const static t_pattern_dict             _illegal_patterns;
        const static t_pattern_dict             _capture_patterns;
        const static t_coord                    _invalid_coord;

        uint8_t                                 _depth;
        t_player                                _first_player;
        t_player                                _second_player;
        size_t                                  _turn;
        t_rule                                  _rule;
        bool                                    _game_over;
        TTable                                  _ttable;
        uint8_t                                 _current_depth;
        t_coord                                 _last_best;
        double                                  average_time;

        int                                     hit_count;
        int                                     node_count;
    public:

        t_board                                 _board;
        t_moveset                               _ai_moveset;
        t_killer_move                           _killer_moves;

    public:
                                Gomoku(uint8_t board_size, t_difficulty first_difficulty,
                                            t_difficulty second_difficulty, t_player_type first_player_type,
                                                t_player_type second_player_type, t_rule rule);
                                ~Gomoku();
        void                    start_game();
    private:
        t_coord                 iterative_depth_search(t_moveset& moveset, t_board &board, uint8_t depth, t_prunner prunner, t_piece piece);
        t_coord                 human_move(t_player& player, t_player& opponent, t_board & board);
        t_coord                 ai_move(t_player& player, t_player& opponent, t_board & board);
        t_moveset               generate_rule_moveset(t_piece piece, t_board &board);
        t_player                get_player(t_player_type player_type, t_piece player_color, t_difficulty difficulty);
        t_scored_move           negascout(t_moveset& moveset, t_board &board, uint8_t depth, t_prunner prunner, t_piece piece);
        // t_sorted_updates        generate_sorted_updates(t_moveset& moveset, t_board &board, t_piece piece, uint8_t depth = 0);
        void                    generate_sorted_updates(t_moveset& moveset, t_board &board, t_sorted_updates& sorted_updates, t_piece piece);
        t_sequence              extract_winning_sequence(t_board &board, t_piece piece, t_coord start_coord);
        int64_t                 evaluate_board(t_board &board, t_piece player_color);
        int32_t                 evaluate_move(t_board &board, t_coord piece_coord, t_piece piece, t_coord direction);
        // int64_t                 evaluate_pattern(t_board& board, t_coord start, t_piece player_color, std::set<std::pair<t_coord, t_coord>> &head_tail_set);
        int64_t                 evaluate_pattern(t_board& board, t_coord start, t_piece player_color, std::unordered_set<std::pair<t_coord, t_coord>, PairHash> &head_tail_set);
        void                    make_move(t_player& player, t_player& opponent, t_board& board);
        void                    generate_scored_update(t_board &board, t_coord move, t_piece piece, t_scored_update& scored_update);
        void                    update_game_state(t_board& board, t_player& player, t_coord current_move);
        void                    update_node_state(t_board &board, t_piece piece, t_moveset &added_moves, t_moveset &moveset, const t_scored_update& sorted_update);
        void                    revert_node_state(t_board &board, t_piece piece, t_moveset &added_moves, t_moveset &moveset, const t_scored_update& sorted_update);
        void                    extract_captured_stoned(t_board &board, t_update_list& update_list, t_coord move, t_coord dir, t_piece piece);
        void                    update_board(t_board &board, const t_update_list &update_list);
        void                    revert_board_update(t_board &board, const t_update_list &update_list);
        void                    print_board(t_board &board, t_piece current_piece);
        bool                    is_move_valid(t_board& board, t_coord piece_coord, t_piece piece);
        bool                    is_inside_square(t_board& board, t_coord piece_coord);
        char                    get_game_command();

        t_piece is_final_state(t_board& board);
        int  distance_to_edge(t_board& board, t_coord position, t_coord direction);

        t_scored_move           minimax_with_memory(t_moveset& moveset, t_board &board, uint8_t depth, t_prunner prunner, t_piece piece, bool max);
};
