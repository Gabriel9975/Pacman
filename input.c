#include "input.h"
#include "game.h"

void handle_input(Game *game, ALLEGRO_KEYBOARD_STATE *key_state) {
    if (al_key_down(key_state, ALLEGRO_KEY_UP)) {
        game->pacman.direction = UP;
    } else if (al_key_down(key_state, ALLEGRO_KEY_DOWN)) {
        game->pacman.direction = DOWN;
    } else if (al_key_down(key_state, ALLEGRO_KEY_LEFT)) {
        game->pacman.direction = LEFT;
    } else if (al_key_down(key_state, ALLEGRO_KEY_RIGHT)) {
        game->pacman.direction = RIGHT;
    } else {
        game->pacman.direction = NONE;
    }
}
