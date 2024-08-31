#include "Board.patterns.cpp"
#include <iostream>
#include <random>

const std::array<t_coord, 4> Board::_directions {{
    {0, 1},
    {1, 0},
    {-1, 1},
    {1, 1}
}};

const std::vector<t_coord> Board::_moveset_cells {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
    {1, -1},
    {-1, 1},
    {1, 1},
    {-1, -1},
};


Board::Board(uint8_t size) {
    if (size > 19)
        throw std::logic_error("Boards cannot be bigger than 19");
    this->size = size;
    board = new uint64_t[size];
    _illegal_boards[0] = new uint64_t[size];
    _illegal_boards[1] = new uint64_t[size];

    std::memset(board, 0, sizeof(uint64_t) * size);
    std::memset(_illegal_boards[0], 0, sizeof(uint64_t) * size);
    std::memset(_illegal_boards[1], 0, sizeof(uint64_t) * size);
    std::memset(_capture_count, 0, sizeof(uint8_t) * 2);

    _evaluation_edges = {
        {0, size - 1},
        {0, size - 1}
    };
}

Board::~Board() {
    delete[] board;
    delete[] _illegal_boards[0];
    delete[] _illegal_boards[1];
}

inline void Board::validate_coord(t_coord position, t_piece piece) const {
    if (position.x < 0 || position.x >= size || position.y < 0 || position.y >= size)
        throw std::logic_error("Position out of range");
    if ((_illegal_boards[piece - 1][position.y] >> (position.x << 1)) & 3)
        throw std::logic_error("Illegal move");
}

inline t_piece Board::get_piece(t_coord piece_coord) const {
    if (piece_coord.x < 0 || piece_coord.x >= size || piece_coord.y < 0 || piece_coord.y >= size)
        return ERROR;
    return (t_piece)((board[piece_coord.y] >> (piece_coord.x << 1)) & 3);
}

inline t_piece Board::get_piece(uint64_t *board, t_coord piece_coord) const{
    if (piece_coord.x < 0 || piece_coord.x >= size || piece_coord.y < 0 || piece_coord.y >= size)
        return ERROR;
    return (t_piece)((board[piece_coord.y] >> (piece_coord.x << 1)) & 3);
}

void Board::update_board(uint64_t *board, t_coord pos, t_piece piece) {
    uint64_t mask = ~(uint64_t(3) << pos.x * 2);
    board[pos.y] = (board[pos.y] & mask) | (uint64_t(piece) << (pos.x) * 2);
}

void Board::set_position(t_coord position, t_piece piece) {
    _evaluation_edges = {
        {std::min(position.x, _evaluation_edges.x.first), std::max(position.x, _evaluation_edges.x.second)},
        {std::min(position.y, _evaluation_edges.y.first), std::max(position.y, _evaluation_edges.y.second)}
    };
    update_board(board, position, piece);
}

void Board::remove_piece(t_coord position) {
    set_position(position, EMPTY);
}

DualColorPotential Board::position_potential(t_coord pos, t_coord dir)
{
    DualColorPotential result = {0, 0};
    const t_piece colors[2] = {BLACK, WHITE};

    for (int color_index = 0; color_index < 2; color_index++)
    {
        t_piece color = colors[color_index];
        int32_t attack_score = 0;
        int32_t defense_score = 0;
        int32_t capture_score = 0;
        t_piece current_piece;
        uint16_t current_pattern;
        t_coord pattern_position;
        uint8_t capture_count;

        const t_scores_map &attack_patterns = Board::_attack_patterns.at(color);
        const t_scores_map &capture_patterns = Board::_capture_patterns.at(color);
        const t_scores_map &illegal_patterns = Board::_illegal_patterns.at(color);
        const t_scores_map &defense_patterns = Board::_defense_patterns.at(color);

        capture_count = _capture_count[color - 1];
        current_pattern = color;
        pattern_position = pos + dir;
        for (int j = 0; j < 5; j++)
        {
            current_piece = get_piece(pos);
            if (current_piece == EMPTY)
                current_piece = get_piece(_illegal_boards[color_index], pattern_position);
            current_pattern <<= 2;
            current_pattern |= get_piece(pattern_position);
            pattern_position += dir;
        }
        for (int i = 0; i < 6; i++)
        {
            current_piece = get_piece(pos);
            if (current_piece == EMPTY)
            {
                current_piece = get_piece(_illegal_boards[color_index], pattern_position);
                if (current_piece)
                    break;
            }
            current_pattern = ((uint16_t)(current_piece) << 10 | current_pattern);
            if (illegal_patterns.count(current_pattern))
            {
                if (color == BLACK)
                    result.black_potential = ILLEGAL_SCORE;
                else
                    result.white_potential = ILLEGAL_SCORE;
                return result;
            }
            if (capture_patterns.count(current_pattern))
                capture_score += CAPTURE_SCORE * (capture_count + 1);
            if (attack_patterns.count(current_pattern))
                attack_score = std::max(int32_t(attack_patterns.at(current_pattern)), attack_score);
            if (defense_patterns.count(current_pattern))
                defense_score = std::max(int32_t(defense_patterns.at(current_pattern)), attack_score);
            pos -= dir;
            current_pattern >>= 2;
        }
        
        int64_t total_score = attack_score + defense_score + capture_score;
        if (color == BLACK)
            result.black_potential = total_score;
        else
            result.white_potential = total_score;
    }
    
    return result;
}

uint8_t Board::capture_pattern(t_coord pos, t_coord dir, t_piece piece) const {
    uint8_t pattern = 0;
    uint8_t empty_c = 0;
    uint8_t piece_c = 0;

    for (int i = 0; i < 4; ++i) {
        t_coord check_pos = pos + dir * (i - 1);
        t_piece curr_piece = get_piece(check_pos);
        
        if (curr_piece == ERROR || 
            (curr_piece == EMPTY && (empty_c++ || get_piece(_illegal_boards[piece - 1], check_pos))) ||
            (curr_piece == piece && piece_c++ > 1)) {
            return 0;
        }
        pattern |= (curr_piece == EMPTY ? piece : curr_piece) << (i << 1);
    }
    return pattern;
}

bool Board::possible_capture(t_coord pos, t_piece color, t_coord dir) const {
    for (auto& curr_dir : _directions) {
        if (curr_dir == dir)
            continue;
        for (auto& curr_dir : {curr_dir, t_coord{-curr_dir.x, -curr_dir.y}}) {
            uint8_t pattern = capture_pattern(pos, curr_dir, color);
            if ((color == BLACK) ? pattern == BLACK_CAPTURE_PATTERN: pattern == WHITE_CAPTURE_PATTERN)
                return true;
        }
    };
    return false;
}

bool Board::check_for_win(t_coord pos, t_piece color, t_coord dir) const {
    uint64_t combo = 0;
    t_piece piece;

    for (;;) {
        if (combo == 5)
            return true;
        piece = get_piece(pos);
        if (piece != color)
            break;
        if (possible_capture(pos, GET_OPPOSITE_PIECE(color), dir))
            combo = 0;
        else
            combo++;
        pos += dir;
    }
    return false;
}

int64_t Board::evaluate_position(t_coord pos, t_piece color, t_coord dir, const t_scores_map &patterns) {
    uint16_t pattern = 0xFFF;
    t_piece piece;
    t_coord current_pos = pos;

    current_pos -= dir;
    for (int i = 0; i < 6; i++) {
        piece = get_piece(current_pos);
        if (i == 0 && piece == color)
            return 0;
        if (i != 0 && piece == GET_OPPOSITE_PIECE(color))
            break;
        pattern = (pattern << 2) | piece;
        current_pos += dir;
    }
    auto it = patterns.find(pattern & 0xFFF);
    t_scores score = (it != patterns.end()) ? it->second : static_cast<t_scores>(0);
    if (score == FIVE_SCORE ){
        if (check_for_win(pos, color, dir))
            return WIN_SCORE;
}
    return (it != patterns.end()) ? it->second : 0;
}

bool Board::evaluate_capture(t_coord pos, t_coord dir)
{
    t_piece check_piece = get_piece(pos);

    for (auto& factor: {1, -1}) {
        t_coord check_pos = pos + dir * factor;
        uint8_t pattern = check_piece;

        for (int i = 1; i < 4; i++) {
            t_piece curr_piece = get_piece(check_pos);
            if (curr_piece == ERROR || curr_piece == EMPTY || (i < 2 && curr_piece == check_piece))
                return false;
            pattern = pattern << 2 | get_piece(check_pos);
            check_pos += dir;        
        }
        if ((check_piece == BLACK) ? pattern == BLACK_CAPTURE_PATTERN: pattern == WHITE_CAPTURE_PATTERN)
            return true;
    }
    return false;
}

void Board::evaluate_position(t_coord pos) {
    static const t_piece colors[2] = {BLACK, WHITE};
    
    _moveset_positions[0][pos].score = 0;
    for (auto& dir: _directions) {
        DualColorPotential potentials = position_potential(pos, dir);
        
        for (int i = 0; i < 2; ++i) {
            t_piece color = colors[i];
            int64_t score = (color == BLACK) ? potentials.black_potential : potentials.white_potential;
            int color_index = color - 1;

            if (score == ILLEGAL_SCORE) {
                ++_illegal_positions[color_index][pos];
                _moveset_positions[color_index][pos].blocked = true;
            } else {
                --_illegal_positions[color_index][pos];
                ++_moveset_positions[color_index][pos].count;
                _moveset_positions[color_index][pos].score += score;
            }
        }
    }
    if (!_illegal_positions[0][pos]) update_board(_illegal_boards[0], pos, EMPTY);
    if (!_illegal_positions[1][pos]) update_board(_illegal_boards[1], pos, EMPTY);

}
void Board::update_node(t_board_update_queue& updates_queue, const t_board_update& curr_update) {
    t_coord pos = curr_update.pos;
    t_piece piece = curr_update.piece;

    for (const auto& dir : _moveset_cells) {
        if (evaluate_capture(pos, dir)) {
            t_coord capture_pos = pos + dir;
            for (int i = 0; i < 2; ++i) {
                updates_queue.emplace_back(capture_pos, piece, REMOVE);
                remove_piece(capture_pos);
                for (const auto& update_dir : _moveset_cells) {
                    --_moveset_positions[BLACK - 1][capture_pos + update_dir].count;
                    --_moveset_positions[WHITE - 1][capture_pos + update_dir].count;
                }
                capture_pos += dir;
            }
        }
        t_coord next_pos = pos + dir;
        if (get_piece(next_pos) == EMPTY)
            evaluate_position(next_pos);
    }
}

void Board::update_board(t_board_update_queue& updates_queue) {
    static const t_piece colors[2] = {BLACK, WHITE};
    for (const auto& update : updates_queue) {
        if (update.type == ADD) {
            set_position(update.pos, update.piece);
            update_node(updates_queue, update);
        }
        else {
            for (int i = 0; i < 2; ++i) {
                t_piece color = colors[i];
                _moveset_positions[i][update.pos].blocked = false;
                evaluate_position(update.pos);
            }
        }
    }
}

void Board::make_move(t_coord pos, t_piece piece) {
    t_board_update_queue updates_queue;
    updates_queue.emplace_back(pos, piece, ADD);
    update_board(updates_queue);
}

int64_t Board::evaluate_board(t_piece player_color) {
    int64_t             score = 0;
    const t_scores_map& p_att_patterns = Board::_attack_patterns.at(player_color);
    const t_scores_map& op_att_patterns = Board::_attack_patterns.at(GET_OPPOSITE_PIECE(player_color));
    const t_piece       opposite_color = GET_OPPOSITE_PIECE(player_color);

    if (_capture_count[player_color - 1] == 5)
        return WIN_SCORE;
    if (_capture_count[opposite_color - 1] == 5)
        return -WIN_SCORE;
    for (int y = _evaluation_edges.y.first; y <= _evaluation_edges.y.second; ++y) {
        uint64_t row = board[y];
        if (!row)
            continue;
        int x = _evaluation_edges.x.first;
        while (row) {
            int bit_pos = __builtin_ctzll(row);
            x = bit_pos >> 1;

            if (x > _evaluation_edges.x.second)
                break;

            t_piece piece = (t_piece)((row >> (x * 2)) & 3);
            if (piece != EMPTY) {
                t_coord             pos = {x, y};
                const t_scores_map& att_patterns = (piece == player_color) ? p_att_patterns : op_att_patterns;
                int64_t             position_score = 0;
                for (const auto& dir : _directions)
                {
                    int64_t score = evaluate_position(pos, piece, dir, att_patterns);
                    if (score == WIN_SCORE)
                        return (piece == player_color) ? WIN_SCORE : -WIN_SCORE;
                    position_score += score;
                }
                score += (piece == player_color) ? position_score : -position_score;
            }
            row &= ~(3ULL << bit_pos);
        }
    }

    return score;
}

void Board::print_board(t_piece curr_piece) const{
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            t_piece piece = t_piece(get_piece(t_coord{x, y}) | get_piece(_illegal_boards[piece - 1], t_coord{x, y}));
            std::cout << piece << " ";
        }
        std::cout << std::endl;
    }
}
