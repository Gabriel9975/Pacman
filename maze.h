#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLS 20
#define TILE_SIZE 30

bool can_move(int x, int y, int labyrinthe[ROWS][COLS]);
void draw_maze(int labyrinthe[ROWS][COLS], BITMAP *wall, BITMAP *point);

#endif
