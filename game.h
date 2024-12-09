#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "maze.h"

#define NUM_GHOSTS 4

void init_game();
void game_loop(Pacman *pacman, Ghost ghosts[], int labyrinthe[ROWS][COLS]);
void cleanup_game();

#endif
