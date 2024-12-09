#include "graphics.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void init_graphics() {
    // ... (initialisation si nécessaire)
}

void draw_maze(int maze[28][31]) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            if (maze[i][j] == 1) {
                // Mur
                al_draw_filled_rectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20, al_map_rgb(0, 0, 255));
            } else if (maze[i][j] == 2) {
                // Point
                al_draw_filled_circle(j * 20 + 10, i * 20 + 10, 5, al_map_rgb(255, 255, 255));
            }
        }
    }
}

void draw_entity(Entity entity, ALLEGRO_BITMAP *sprite) {
    if (sprite){
        al_draw_bitmap(sprite, entity.x, entity.y, 0);
    } else {
        al_draw_filled_rectangle(entity.x, entity.y, entity.x + entity.width, entity.y + entity.height, al_map_rgb(255, 255, 0));
    }
}

void draw_score(int score) {
    ALLEGRO_FONT *font = al_create_builtin_font();
    char score_str[20];
    sprintf(score_str, "Score: %d", score);
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, score_str);
    al_destroy_font(font);
}

void cleanup_graphics() {
    // ... (libération des ressources graphiques)
}
