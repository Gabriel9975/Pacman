#include <allegro.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 20
#define COLS 20
#define TILE_SIZE 30

typedef struct {
    int x, y;
    int direction;
    int lives;
    int score;
} Pacman;

typedef struct {
    int x, y;
    int direction;
} Ghost;

// Fonction pour vérifier si Pacman peut se déplacer
bool can_move(int x, int y, int labyrinthe[ROWS][COLS]) {
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return false;
    return labyrinthe[y][x] != 1;
}

// Fonction pour dessiner le labyrinthe
void draw_maze(int labyrinthe[ROWS][COLS], BITMAP *wall, BITMAP *point) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int tile = labyrinthe[row][col];
            if (tile == 1) {
                draw_sprite(screen, wall, col * TILE_SIZE, row * TILE_SIZE);
            }
            else if (tile == 2) {
                draw_sprite(screen, point, col * TILE_SIZE + (TILE_SIZE / 2 - point->w / 2),
                                     row * TILE_SIZE + (TILE_SIZE / 2 - point->h / 2));
            }
        }
    }
}

// Fonction pour dessiner une entité
void draw_entity(BITMAP *sprite, int x, int y) {
    draw_sprite(screen, sprite, x * TILE_SIZE, y * TILE_SIZE);
}

// Fonction de mouvement pour les fantômes (à implémenter)
void move_ghost(Ghost *ghost, int labyrinthe[ROWS][COLS]) {
    // Tentative de mouvement aléatoire
    int direction = rand() % 4; // 0: haut, 1: droite, 2: bas, 3: gauche

    switch (direction) {
        case 0: // Haut
            if (can_move(ghost->x, ghost->y - 1, labyrinthe)) {
                ghost->y--;
                ghost->direction = 0;
            }
            break;
        case 1: // Droite
            if (can_move(ghost->x + 1, ghost->y, labyrinthe)) {
                ghost->x++;
                ghost->direction = 1;
            }
            break;
        case 2: // Bas
            if (can_move(ghost->x, ghost->y + 1, labyrinthe)) {
                ghost->y++;
                ghost->direction = 2;
            }
            break;
        case 3: // Gauche
            if (can_move(ghost->x - 1, ghost->y, labyrinthe)) {
                ghost->x--;
                ghost->direction = 3;
            }
            break;
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    // Initialisation d'Allegro
    if (allegro_init() != 0) {
        fprintf(stderr, "Échec de l'initialisation d'Allegro.\n");
        return -1;
    }

    // Installation du clavier et de la souris (la souris n'est pas utilisée dans cet exemple)
    install_keyboard();
    install_mouse();

    // Initialisation du mode vidéo
    const int SCREEN_WIDTH = COLS * TILE_SIZE;
    const int SCREEN_HEIGHT = ROWS * TILE_SIZE + 50;
    set_color_depth(32); // Définir la profondeur de couleur
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        fprintf(stderr, "Échec de l'initialisation du mode graphique.\n");
        return -1;
    }

    // Chargement des images
    BITMAP *wall = load_bitmap("assets/images/wall.bmp", NULL);
    BITMAP *point = load_bitmap("assets/images/point.bmp", NULL);
    BITMAP *pacman_sprite = load_bitmap("assets/images/pacman.bmp", NULL);
    BITMAP *ghost_sprite = load_bitmap("assets/images/ghost.bmp", NULL);

    if (!wall || !point || !pacman_sprite || !ghost_sprite) {
        fprintf(stderr, "Échec du chargement des images.\n");
        return -1;
    }

    // Chargement des sons
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
    SAMPLE *eat_sound = load_sample("assets/sounds/eat.wav");
    SAMPLE *death_sound = load_sample("assets/sounds/death.wav");

    // Initialisation des polices
    FONT *font = load_font("assets/fonts/arial.pcx", NULL, NULL);
    if (!font) {
        allegro_message("Erreur lors du chargement de la police.");
    }

    // Définition du labyrinthe
    int labyrinthe[ROWS][COLS] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,1},
        {1,2,1,1,2,2,1,2,1,1,1,2,1,2,2,1,1,2,2,1},
        {1,2,1,1,2,2,1,2,1,1,1,2,1,2,2,1,1,2,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,1,2,1},
        {1,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Initialisation de Pacman
    Pacman pacman = {1, 1, 1, 3, 0};

    // Initialisation des Fantômes
    int num_ghosts = 4;
    Ghost ghosts[4] = {
        {18, 1, 3},
        {18, 18, 3},
        {1, 18, 1},
        {10, 10, 0}
    };

    // Boucle principale
    bool running = true;
    while (running) {
        // Gestion des entrées clavier
        if (keypressed()) {
            int key = readkey() >> 8;
            switch (key) {
                case KEY_UP:
                    if (can_move(pacman.x, pacman.y - 1, labyrinthe)) {
                        pacman.y -= 1;
                        pacman.direction = 0;
                        play_sample(eat_sound, 255, 128, 1000, FALSE);
                    }
                    break;
                case KEY_RIGHT:
                    if (can_move(pacman.x + 1, pacman.y, labyrinthe)) {
                        pacman.x += 1;
                        pacman.direction = 1;
                        play_sample(eat_sound, 255, 128, 1000, FALSE);
                    }
                    break;
                case KEY_DOWN:
                    if (can_move(pacman.x, pacman.y + 1, labyrinthe)) {
                        pacman.y += 1;
                        pacman.direction = 2;
                        play_sample(eat_sound, 255, 128, 1000, FALSE);
                    }
                    break;
                case KEY_LEFT:
                    if (can_move(pacman.x - 1, pacman.y, labyrinthe)) {
                        pacman.x -= 1;
                        pacman.direction = 3;
                        play_sample(eat_sound, 255, 128, 1000, FALSE);
                    }
                    break;
                case KEY_ESC:
                    running = false;
                    break;
            }
        }

        // Mise à jour des fantômes
        for (int i = 0; i < num_ghosts; i++) {
            move_ghost(&ghosts[i], labyrinthe);
        }

        // Vérification des collisions
        for (int i = 0; i < num_ghosts; i++) {
            if (pacman.x == ghosts[i].x && pacman.y == ghosts[i].y) {
                pacman.lives -= 1;
                play_sample(death_sound, 255, 128, 1000, FALSE);
                // Réinitialiser la position de Pacman
                pacman.x = 1;
                pacman.y = 1;
                if (pacman.lives <= 0) {
                    running = false;
                    textout_ex(screen, font, "Game Over! Score:", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
                    char score_str[20];
                    sprintf(score_str, "%d", pacman.score);
                    textout_ex(screen, font, score_str, SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
                    readkey();
                }
            }
        }

        // Collecte des points
        if (labyrinthe[pacman.y][pacman.x] == 2) {
            labyrinthe[pacman.y][pacman.x] = 0;
            pacman.score += 10;
        }

        // Vérifier la condition de victoire
        bool victoire = true;
        for (int row = 0; row < ROWS && victoire; row++) {
            for (int col = 0; col < COLS && victoire; col++) {
                if (labyrinthe[row][col] == 2)
                    victoire = false;
            }
        }
        if (victoire) {
            running = false;
            textout_ex(screen, font, "Vous avez gagné! Score:", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
            char score_str[20];
            sprintf(score_str, "%d", pacman.score);
            textout_ex(screen, font, score_str, SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
            readkey();
        }

        // Effacer l'écran
        clear_to_color(screen, makecol(0, 0, 0));

        // Dessiner le labyrinthe
        draw_maze(labyrinthe, wall, point);

        // Dessiner Pacman
        draw_entity(pacman_sprite, pacman.x, pacman.y);

        // Dessiner les fantômes
        for (int i = 0; i < num_ghosts; i++) {
            draw_entity(ghost_sprite, ghosts[i].x, ghosts[i].y);
        }

        // Dessiner le HUD
        char hud[50];
        sprintf(hud, "Score: %d   Vies: %d", pacman.score, pacman.lives);
        textout_ex(screen, font, hud, 10, ROWS * TILE_SIZE + 10, makecol(255, 255, 255), -1);

        // Mise à jour de l'affichage
        rest(1000 / 60); // Limiter à environ 60 FPS
    }

    // Nettoyage
    destroy_bitmap(wall);
    destroy_bitmap(point);
    destroy_bitmap(pacman_sprite);
    destroy_bitmap(ghost_sprite);
    destroy_sample(eat_sound);
    destroy_sample(death_sound);
    destroy_font(font);
    allegro_exit();

    return 0;
}
END_OF_MAIN()
