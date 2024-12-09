#include "game.h"
#include "graphics.h"
#include "audio.h"
#include "maze.h"
#include "entity.h"

int main() {
    init_game(); // Initialise Allegro et les ressources.

    Pacman pacman = init_pacman();
    Ghost ghosts[NUM_GHOSTS];
    init_ghosts(ghosts);

    int labyrinthe[ROWS][COLS] = {
        // Labyrinthe initial ici
    };

    game_loop(&pacman, ghosts, labyrinthe);

    cleanup_game(); // Libère les ressources et termine proprement.
    return 0;
}

