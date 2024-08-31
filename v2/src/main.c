#include "Gomoku.hpp"

int main() {
    Gomoku game(19, EASY, EASY, HUMAN, HUMAN, STANDARD);
    game.start_game();
    return 0;
}