#ifndef UTILS_H
#define UTILS_H

// Définitions pour le labyrinthe
#define ROWS 25      // Nombre de lignes de la matrice du labyrinthe
#define COLS 25      // Nombre de colonnes de la matrice du labyrinthe
#define CELL_SIZE 32 // Taille d'une cellule en pixels (pour l'affichage)

// Valeurs pour représenter les éléments du labyrinthe
#define EMPTY 0 // Chemin libre
#define WALL 1  // Mur
#define DOT 2   // Point à collecter
#define BIGDOT 3 // Super point

// Structure pour représenter une entité (Pacman, fantômes)
typedef struct {
    int x, y;       // Position actuelle en cellules (pas en pixels)
    int direction;  // Direction de déplacement (0: haut, 1: bas, 2: gauche, 3: droite)
    int score;      // Score du joueur
    int lives;      // Nombre de vies restantes
} Entity;

// Définitions pour les directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Structure pour gérer le score et les vies
typedef struct {
    int score;
    int lives;
} GameState;

// Prototypes de fonctions utilitaires (à définir dans un fichier .c)
int clamp(int value, int min, int max);

#endif /* UTILS_H */
