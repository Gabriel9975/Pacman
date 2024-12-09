#include "maze.h"
#include <allegro.h>

bool can_move(int x, int y, int labyrinthe[ROWS][COLS]) {
    return !(x < 0 || x >= COLS || y < 0 || y >= ROWS || labyrinthe[y][x] == 1);
}

void draw_maze(int labyrinthe[ROWS][COLS], BITMAP *wall, BITMAP *point) {
    // Logique de dessin du labyrinthe.
}
