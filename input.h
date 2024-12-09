#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "utils.h"

// Prototypes de fonctions pour la gestion des entrées
void handle_keyboard_input(Entity *pacman, ALLEGRO_EVENT *event, int labyrinthe[ROWS][COLS]);
bool is_valid_move(int x, int y, int direction, int labyrinthe[ROWS][COLS]);
#endif /* INPUT_H */
