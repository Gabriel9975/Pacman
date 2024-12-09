#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Taille d'une tuile et dimensions du labyrinthe
#define TILE_SIZE 32
#define ROWS 20
#define COLS 20

// Structure pour Pacman
typedef struct {
    int x, y;
    int direction;
    int lives;
    int score;
} Pacman;

// Structure pour les fantômes
typedef struct {
    int x, y;
    int direction;
    int type; // Pour differencier les types de fantomes plus tard si besoin
} Ghost;

// Structure pour les points
typedef struct {
    int x, y;
    bool collected;
} Point;

// Le labyrinthe
int labyrinth[ROWS][COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,2,1},
    {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1,2},
    {1,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Prototypes des fonctions
void initGame(Pacman *pacman, Ghost *ghosts, Point *points);
void handleKeyPress(Pacman *pacman, int keycode);
bool canMove(int x, int y);
void moveGhost(Ghost *ghost);
void checkCollisions(Pacman *pacman, Ghost *ghosts, Point *points);
void updateGame(Pacman *pacman, Ghost *ghosts, Point *points);
void drawGame(ALLEGRO_DISPLAY *display, Pacman *pacman, Ghost *ghosts, Point *points, ALLEGRO_FONT *font);
void resetPositions(Pacman *pacman, Ghost *ghosts);

int main() {
    // Initialisation d'Allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    // Installation du clavier
    if (!al_install_keyboard()) {
        fprintf(stderr, "Failed to install keyboard!\n");
        return -1;
    }

    // Initialisation des addons
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Creation de la fenetre
    ALLEGRO_DISPLAY *display = al_create_display(COLS * TILE_SIZE, ROWS * TILE_SIZE);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    // Chargement de la police
    ALLEGRO_FONT *font = al_load_ttf_font("assets/arial.ttf", 18, 0); // Remplacez par le chemin correct
    if (!font) {
        fprintf(stderr, "Could not load 'arial.ttf'.\n");
        al_destroy_display(display);
        return -1;
    }

    // Création de la file d'événements
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        al_destroy_font(font);
        al_destroy_display(display);
        return -1;
    }

    // Enregistrement des sources d'événements
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Initialisation du jeu
    Pacman pacman;
    Ghost ghosts[4];
    Point points[ROWS * COLS];

    initGame(&pacman, ghosts, points);

    // Boucle de jeu principale
    bool done = false;
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            handleKeyPress(&pacman, ev.keyboard.keycode);
        }

        updateGame(&pacman, ghosts, points);
        drawGame(display, &pacman, ghosts, points, font);

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    // Libération des ressources
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

// Initialise les positions de départ, les vies, etc.
void initGame(Pacman *pacman, Ghost *ghosts, Point *points) {
    pacman->x = 9;
    pacman->y = 8;
    pacman->direction = -1; // Initialement immobile
    pacman->lives = 3;
    pacman->score = 0;

    // Initialiser les positions des fantômes (exemple)
    ghosts[0].x = 8;
    ghosts[0].y = 7;
    ghosts[1].x = 9;
    ghosts[1].y = 7;
    ghosts[2].x = 10;
    ghosts[2].y = 7;
    ghosts[3].x = 9;
    ghosts[3].y = 6;

    // Initialiser les points
    int k = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (labyrinth[i][j] == 2) {
                points[k].x = j;
                points[k].y = i;
                points[k].collected = false;
                k++;
            }
        }
    }
}

// Gère les entrées clavier pour déplacer Pacman
void handleKeyPress(Pacman *pacman, int keycode) {
    switch (keycode) {
        case ALLEGRO_KEY_UP:
            pacman->direction = 0; // 0: haut, 1: bas, 2: gauche, 3: droite
            break;
        case ALLEGRO_KEY_DOWN:
            pacman->direction = 1;
            break;
        case ALLEGRO_KEY_LEFT:
            pacman->direction = 2;
            break;
        case ALLEGRO_KEY_RIGHT:
            pacman->direction = 3;
            break;
    }
}

// Vérifie si un déplacement est possible (pas de collision avec un mur)
bool canMove(int x, int y) {
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS || labyrinth[y][x] == 1) {
        return false;
    }
    return true;
}

// Déplacement simple et aléatoire des fantômes
void moveGhost(Ghost *ghost) {
    int direction = rand() % 4; // 0: haut, 1: bas, 2: gauche, 3: droite

    if (direction == 0 && canMove(ghost->x, ghost->y - 1)) {
        ghost->y--;
    } else if (direction == 1 && canMove(ghost->x, ghost->y + 1)) {
        ghost->y++;
    } else if (direction == 2 && canMove(ghost->x - 1, ghost->y)) {
        ghost->x--;
    } else if (direction == 3 && canMove(ghost->x + 1, ghost->y)) {
        ghost->x++;
    }
}

// Vérifie les collisions avec les points et les fantômes
void checkCollisions(Pacman *pacman, Ghost *ghosts, Point *points) {
    // Collision avec un point
    for (int i = 0; i < ROWS * COLS; i++) {
        if (points[i].x == pacman->x && points[i].y == pacman->y && !points[i].collected) {
            points[i].collected = true;
            pacman->score++;
        }
    }

    // Collision avec un fantôme
    for (int i = 0; i < 4; i++) {
        if (ghosts[i].x == pacman->x && ghosts[i].y == pacman->y) {
            pacman->lives--;
            resetPositions(pacman, ghosts);
        }
    }
}

// Met à jour les positions, vérifie les collisions, et gère la fin du jeu
void updateGame(Pacman *pacman, Ghost *ghosts, Point *points) {
    // Déplacement de Pacman
    if (pacman->direction == 0 && canMove(pacman->x, pacman->y - 1)) {
        pacman->y--;
    } else if (pacman->direction == 1 && canMove(pacman->x, pacman->y + 1)) {
        pacman->y++;
    } else if (pacman->direction == 2 && canMove(pacman->x - 1, pacman->y)) {
        pacman->x--;
    } else if (pacman->direction == 3 && canMove(pacman->x + 1, pacman->y)) {
        pacman->x++;
    }

    // Déplacement des fantômes
    for (int i = 0; i < 4; i++) {
        moveGhost(&ghosts[i]);
    }

    // Vérification des collisions
    checkCollisions(pacman, ghosts, points);

    // Vérification de la fin du jeu
    if (pacman->lives <= 0) {
        printf("Game Over! Score: %d\n", pacman->score);
        exit(0); // Quitter le jeu (vous pouvez afficher un écran de fin à la place)
    }

    bool allPointsCollected = true;
    for (int i = 0; i < ROWS * COLS; i++) {
        if (labyrinth[points[i].y][points[i].x] == 2 && !points[i].collected) {
            allPointsCollected = false;
            break;
        }
    }

    if (allPointsCollected) {
        printf("You Win! Score: %d\n", pacman->score);
        exit(0); // Quitter le jeu (vous pouvez passer au niveau suivant à la place)
    }
}

// Dessine le labyrinthe, Pacman, les fantômes, les points, le score et les vies
void drawGame(ALLEGRO_DISPLAY *display, Pacman *pacman, Ghost *ghosts, Point *points, ALLEGRO_FONT *font) {
    // Dessiner le labyrinthe
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (labyrinth[i][j] == 1) {
                al_draw_filled_rectangle(j * TILE_SIZE, i * TILE_SIZE, (j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE, al_map_rgb(0, 0, 255)); // Mur en bleu
            } else if (labyrinth[i][j] == 2) {
                // Dessiner un point si non collecté
                for(int k = 0; k < ROWS * COLS; k++){
                    if(points[k].x == j && points[k].y == i && !points[k].collected){
                         al_draw_filled_circle(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 8, al_map_rgb(255, 255, 255)); // Point en blanc
                    }
                }
            }
        }
    }

    // Dessiner Pacman (exemple simple : un cercle jaune)
    al_draw_filled_circle(pacman->x * TILE_SIZE + TILE_SIZE / 2, pacman->y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 2, al_map_rgb(255, 255, 0));

    // Dessiner les fantômes (exemple simple : un rectangle rouge)
    for (int i = 0; i < 4; i++) {
        al_draw_filled_rectangle(ghosts[i].x * TILE_SIZE, ghosts[i].y * TILE_SIZE, (ghosts[i].x + 1) * TILE_SIZE, (ghosts[i].y + 1) * TILE_SIZE, al_map_rgb(255, 0, 0));
    }

    // Afficher le score et les vies
    al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, ALLEGRO_ALIGN_LEFT, "Score: %d", pacman->score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), COLS * TILE_SIZE - 5, 5, ALLEGRO_ALIGN_RIGHT, "Lives: %d", pacman->lives);
}

void resetPositions(Pacman *pacman, Ghost *ghosts) {
    pacman->x = 9;
    pacman->y = 8;
    pacman->direction = -1; // Initialement immobile

    // Réinitialiser les positions des fantômes (exemple)
    ghosts[0].x = 8;
    ghosts[0].y = 7;
    ghosts[1].x = 9;
    ghosts[1].y = 7;
    ghosts[2].x = 10;
    ghosts[2].y = 7;
    ghosts[3].x = 9;
    ghosts[3].y = 6;
}
