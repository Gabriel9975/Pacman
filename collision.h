#ifndef COLLISION_H
#define COLLISION_H

#include <allegro.h>

// Structure pour représenter une entité (Pacman ou fantôme)
typedef struct {
    int x, y;        // Position actuelle
    int direction;   // Direction de déplacement (0: haut, 1: droite, 2: bas, 3: gauche)
    int lives;       // Nombre de vies (pour Pacman)
    int speed;       // Vitesse de déplacement
    BITMAP *sprite;  // Image de l'entité
} Entity;

// Structure pour représenter un point à collecter
typedef struct {
    int x, y;        // Position
    int collected;   // 0: non collecté, 1: collecté
} Point;

// Fonction pour vérifier la collision entre une entité et un mur du labyrinthe
int is_wall_collision(int x, int y, int **labyrinth, int rows, int cols);

// Fonction pour vérifier la collision entre Pacman et un fantôme
int is_ghost_collision(Entity pacman, Entity ghost);

// Fonction pour vérifier la collision entre Pacman et un point
int is_point_collision(Entity pacman, Point *point);

// Fonction pour gérer la collision entre Pacman et un point (mise à jour du score, etc.)
void handle_point_collision(Entity *pacman, Point *point, int *score);

// Fonction pour gérer la collision entre Pacman et un fantôme (perte de vie, etc.)
void handle_ghost_collision(Entity *pacman, Entity *ghost);

#endif
