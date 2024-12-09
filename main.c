#include <allegro.h>
#include <stdio.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "entities.h"
#include "utils.h"
#include "collision.h"

// Dimensions de l'écran
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

int main() {
    // Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    install_timer();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    // Mode graphique
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        allegro_message("Impossible d'initialiser le mode graphique : %s", allegro_error);
        return -1;
    }

    // Chargement des sprites
    BITMAP *pacman_sprite = load_bitmap("assets/sprites/pacman.bmp", NULL);
    BITMAP *ghost_sprites[4];
    for (int i = 0; i < 4; i++) {
        char ghost_path[50];
        sprintf(ghost_path, "assets/sprites/ghost%d.bmp", i + 1);
        ghost_sprites[i] = load_bitmap(ghost_path, NULL);
        if (!ghost_sprites[i]) {
            allegro_message("Erreur en chargeant le sprite : %s", ghost_path);
        }
    }

    // Chargement des sons
    SAMPLE *chomp_sound = load_sample("assets/sounds/pacman_chomp.wav");

    // Initialisation du jeu
    Game game;
    init_game(&game);
    load_level(&game, "assets/levels/level1.txt");

    // Boucle principale
    bool running = true;
    while (running) {
        // Entrées clavier
        if (keypressed()) {
            int key = readkey() >> 8;
            if (key == KEY_ESC) {
                running = false;
            } else {
                handle_input(&game, key);
            }
        }

        // Mise à jour
        update_game(&game);

        // Dessin
        clear_to_color(screen, makecol(0, 0, 0)); // Effacer l'écran en noir
        draw_maze(game.maze, screen);
        draw_entity(game.pacman, pacman_sprite, screen);
        for (int i = 0; i < 4; i++) {
            draw_entity(game.ghosts[i], ghost_sprites[i], screen);
        }
        draw_score(game.score, screen);

        rest(1000 / FPS); // Pause pour respecter le FPS
    }

    // Nettoyage
    destroy_bitmap(pacman_sprite);
    for (int i = 0; i < 4; i++) {
        destroy_bitmap(ghost_sprites[i]);
    }
    destroy_sample(chomp_sound);

    return 0;
}
END_OF_MAIN();
