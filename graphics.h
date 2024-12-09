#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro.h>
#include "entity.h"

void draw_entity(BITMAP *sprite, int x, int y);
void draw_hud(Pacman *pacman);

#endif
