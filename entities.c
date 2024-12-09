#include "entities.h"

void move_pacman(Entity *pacman, int maze[28][31], Direction dir) {
    int next_x = pacman->x;
    int next_y = pacman->y;

    switch (dir) {
        case UP:    next_y -= pacman->speed; break;
        case DOWN:  next_y += pacman->speed; break;
        case LEFT:  next_x -= pacman->speed; break;
        case RIGHT: next_x += pacman->speed; break;
        case NONE:
        default:
            break;
    }

    // Vérification des collisions avec les murs (utiliser une fonction de collision plus précise si nécessaire)
    int tile_next_x = next_x / 20;
    int tile_next_y = next_y / 20;
    int tile_next_x2 = (next_x + pacman->width - 1) / 20;
    int tile_next_y2 = (next_y + pacman->height - 1) / 20;

    if (next_x >= 0 && next_x + pacman->width <= 31 * 20 &&
        next_y >= 0 && next_y + pacman->height <= 28 * 20 &&
        maze[tile_next_y][tile_next_x] != 1 &&
        maze[tile_next_y2][tile_next_x] != 1 &&
        maze[tile_next_y][tile_next_x2] != 1 &&
        maze[tile_next_y2][tile_next_x2] != 1) {
        pacman->x = next_x;
        pacman->y = next_y;
    }
}

void move_ghost(Entity *ghost, int maze[28][31]) {
    // Implémentation simple : mouvement aléatoire
    int dir = rand() % 4; // 0: UP, 1: DOWN, 2: LEFT, 3: RIGHT
    int next_x = ghost->x;
    int next_y = ghost->y;

    switch (dir) {
        case 0: next_y -= ghost->speed; break;
        case 1: next_y += ghost->speed; break;
        case 2: next_x -= ghost->speed; break;
        case 3: next_x += ghost->speed; break;
    }

    // Vérification des collisions (basique)
    int tile_next_x = next_x / 20;
    int tile_next_y = next_y / 20;
    int tile_next_x2 = (next_x + ghost->width - 1) / 20;
    int tile_next_y2 = (next_y + ghost->height - 1) / 20;

    if (next_x >= 0 && next_x + ghost->width <= 31 * 20 &&
        next_y >= 0 && next_y + ghost->height <= 28 * 20 &&
        maze[tile_next_y][tile_next_x] != 1 &&
        maze[tile_next_y2][tile_next_x] != 1 &&
        maze[tile_next_y][tile_next_x2] != 1 &&
        maze[tile_next_y2][tile_next_x2] != 1) {
        ghost->x = next_x;
        ghost->y = next_y;
    }
}
void init_entity(Entity *entity, int x, int y, int width, int height, float speed, ALLEGRO_BITMAP *sprite){
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->speed = speed;
    entity->sprite = sprite;
    entity->direction = NONE;
}
