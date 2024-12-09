#include "entity.h"

Pacman init_pacman() {
    return (Pacman){1, 1, 0, 3, 0};
}

void init_ghosts(Ghost ghosts[]) {
    ghosts[0] = (Ghost){18, 1, 3};
    ghosts[1] = (Ghost){18, 18, 3};
    ghosts[2] = (Ghost){1, 18, 1};
    ghosts[3] = (Ghost){10, 10, 0};
}

void move_pacman(Pacman *pacman, int input, int labyrinthe[ROWS][COLS]) {
    // Logique pour déplacer Pacman.
}

void move_ghost(Ghost *ghost, int labyrinthe[ROWS][COLS]) {
    // Logique pour déplacer un fantôme.
}
