#ifndef ENTITIES_H
#define ENTITIES_H

// Types de direction
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} Direction;

// Structure pour les entités (Pacman, fantômes, etc.)
typedef struct {
    int x, y;           // Position
    int width, height;  // Dimensions
    Direction direction; // Direction actuelle
    float speed;         // Vitesse de déplacement
    ALLEGRO_BITMAP *sprite;
} Entity;

// Prototypes des fonctions
void move_pacman(Entity *pacman, int maze[28][31], Direction dir);
void move_ghost(Entity *ghost, int maze[28][31]);
void init_entity(Entity *entity, int x, int y, int width, int height, float speed, ALLEGRO_BITMAP *sprite);
#endif
