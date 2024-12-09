#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "maze.h"

typedef struct {
    int x, y;
    int direction;
    int lives;
    int score;
} Pacman;

typedef struct {
    int x, y;
    int direction;
} Ghost;

Pacman init_pacman();
void init_ghosts(Ghost ghosts[]);
void move_pacman(Pacman *pacman, int input, int labyrinthe[ROWS][COLS]);
void move_ghost(Ghost *ghost, int labyrinthe[ROWS][COLS]);

#endif
