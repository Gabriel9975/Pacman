#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// Prototypes des fonctions graphiques
void init_graphics();
void draw_maze(int maze[28][31]);
void draw_entity(Entity entity, ALLEGRO_BITMAP *sprite);
void draw_score(int score);
void cleanup_graphics();

#endif
