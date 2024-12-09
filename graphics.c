#include "graphics.h"

void draw_entity(BITMAP *sprite, int x, int y) {
    draw_sprite(screen, sprite, x * TILE_SIZE, y * TILE_SIZE);
}

void draw_hud(Pacman *pacman) {
    // Logique d'affichage du HUD.
}
