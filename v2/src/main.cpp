#include "Gomoku.hpp"

int main(int argc, char **argv)
{
    t_coord new_move;
    t_player_type p1_type;
    t_player_type p2_type;
    t_difficulty p1_diff;
    t_difficulty p2_diff;

    p1_type = HUMAN;
    p2_type = HUMAN;
    p1_diff = EASY;
    p2_diff = EASY;

    for (int i = 1; i < argc; i++)
    {
        // Check player type
        if (!strcmp(argv[i], "--p1_type=human"))
            p1_type = HUMAN;
        else if (!strcmp(argv[i], "--p1_type=ai"))
            p1_type = AI;
        else if (!strcmp(argv[i], "--p2_type=human"))
            p2_type = HUMAN;
        else if (!strcmp(argv[i], "--p2_type=ai"))
            p2_type = AI;

        // Check difficulty
        else if (p1_type == AI)
        {
            if (!strcmp(argv[i], "--p1_diff=easy"))
                p1_diff = EASY;
            else if (!strcmp(argv[i], "--p1_diff=medium"))
                p1_diff = MEDIUM;
            else if (!strcmp(argv[i], "--p1_diff=hard"))
                p1_diff = HARD;
        }
        else if (p2_type == AI)
        {
            if (!strcmp(argv[i], "--p2_diff=easy"))
                p2_diff = EASY;
            else if (!strcmp(argv[i], "--p2_diff=medium"))
                p2_diff = MEDIUM;
            else if (!strcmp(argv[i], "--p2_diff=hard"))
                p2_diff = HARD;
        }
    }

    Gomoku game(19, p1_diff, p2_diff, p1_type, p2_type, STANDARD);

    game.start_game();

    return (0);
}