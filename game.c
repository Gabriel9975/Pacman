#include "game.h"
#include "entities.h"
#include "collision.h"
#include <stdio.h>
#include <allegro5/allegro_audio.h>

void init_game(Game *game) {
    game->score = 0;
    game->lives = 3;
    game->level = 1;
    // Initialisation de Pacman
    init_entity(&game->pacman, 100, 100, 20, 20, 4.0, NULL); 
    // Initialisation des fantômes
    for (int i = 0; i < 4; i++) {
        init_entity(&game->ghosts[i], 200 + i * 50, 200, 20, 20, 2.0, NULL);
    }
}

void load_level(Game *game, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de niveau : %s\n", filename);
        return;
    }
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            fscanf(file, "%d", &game->maze[i][j]);
        }
    }
    fclose(file);
}

void update_game(Game *game) {
    // Mettre à jour la position de Pacman
    move_pacman(&game->pacman, game->maze, game->pacman.direction);

    // Mettre à jour la position des fantômes
    for (int i = 0; i < 4; i++) {
        move_ghost(&game->ghosts[i], game->maze);
    }

    // Vérifier les collisions
    for (int i = 0; i < 4; i++) {
        if (check_collision(game->pacman.x, game->pacman.y, game->pacman.width, game->pacman.height,
                            game->ghosts[i].x, game->ghosts[i].y, game->ghosts[i].width, game->ghosts[i].height)) {
            game->lives--;
            // Réinitialiser les positions de Pacman et des fantômes
            init_entity(&game->pacman, 100, 100, 20, 20, 4.0, game->pacman.sprite);
            for (int j = 0; j < 4; j++) {
                init_entity(&game->ghosts[j], 200 + j * 50, 200, 20, 20, 2.0, game->ghosts[j].sprite);
            }
            if (game->lives == 0) {
                // Game over
            }
        }
    }

    // Vérifier si Pacman mange un point
    int tile_x = game->pacman.x / 20; 
    int tile_y = game->pacman.y / 20;
    if (tile_x >= 0 && tile_x < 31 && tile_y >= 0 && tile_y < 28 && game->maze[tile_y][tile_x] == 2) {
        game->maze[tile_y][tile_x] = 0; 
        game->score += 10; 
    }
}
