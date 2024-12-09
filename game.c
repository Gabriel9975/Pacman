#include "game.h"
#include "graphics.h"
#include "audio.h"

void init_game() {
    allegro_init();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
    srand(time(NULL));
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, COLS * TILE_SIZE, ROWS * TILE_SIZE + 50, 0, 0);
}

void game_loop(Pacman *pacman, Ghost ghosts[], int labyrinthe[ROWS][COLS]) {
    bool running = true;
    while (running) {
        // Gestion des entrées, mise à jour des entités, collisions, et rendu
    }
}

void cleanup_game() {
    allegro_exit();
}
