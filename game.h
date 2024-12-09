#ifndef GAME_H
#define GAME_H

#include <allegro4/allegro.h>
#include "entities.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

// ... autres constantes

// Structure pour le jeu
typedef struct {
    int score;
    int lives;
    int level;
    int maze[28][31]; // Matrice du labyrinthe (ajustez la taille si besoin)
    Entity pacman;
    Entity ghosts[4]; // Tableau de 4 fantômes
    // ... autres variables globales du jeu
} Game;

// Prototypes des fonctions
void init_game(Game *game);
void update_game(Game *game);
void load_level(Game *game, const char *filename);
bool check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif
