#include <stdio.h>
#include <allegro4/allegro.h>
#include <allegro4/allegro_image.h>
#include <allegro4/allegro_primitives.h>
#include <allegro4/allegro_audio.h>
#include <allegro4/allegro_acodec.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "entities.h"
#include "utils.h"
#include "collision.h"

int main() {
    // Initialisation d'Allegro
    if (!al_init()) {
        fprintf(stderr, "Erreur lors de l'initialisation d'Allegro.\n");
        return -1;
    }

    // Initialisation des addons
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(10); // Réserver de la place pour les effets sonores

    // Création de la fenêtre
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre.\n");
        return -1;
    }

    // Initialisation du timer
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "Erreur lors de la création du timer.\n");
        return -1;
    }

    // File d'événements
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Erreur lors de la création de la file d'événements.\n");
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // Initialisation du jeu
    Game game;
    init_game(&game);
    load_level(&game, "assets/levels/level1.txt");

    // Chargement des sprites
    game.pacman.sprite = al_load_bitmap("assets/sprites/pacman.png");
    for(int i = 0; i < 4; i++){
        char ghost_path[50];
        sprintf(ghost_path, "assets/sprites/ghost%d.png", i + 1);
        game.ghosts[i].sprite = al_load_bitmap(ghost_path);
    }

    // Initialisation des sons
    ALLEGRO_SAMPLE *chomp_sound = al_load_sample("assets/sounds/pacman_chomp.wav");
    // ... (charger d'autres sons)

    // Boucle principale
    bool running = true;
    bool redraw = true;
    al_start_timer(timer);
    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Logique du jeu (mise à jour)
            update_game(&game);
            redraw = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Gestion des entrées clavier
            handle_input(&game, ev.keyboard.keycode);
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            // Dessin
            al_clear_to_color(al_map_rgb(0, 0, 0)); // Effacer l'écran en noir
            draw_maze(game.maze);
            draw_entity(game.pacman, game.pacman.sprite);
            for (int i = 0; i < 4; i++) {
                draw_entity(game.ghosts[i], game.ghosts[i].sprite);
            }
            draw_score(game.score);
            al_flip_display();
        }
    }

    // Nettoyage
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(game.pacman.sprite);
    for(int i = 0; i < 4; i++){
        al_destroy_bitmap(game.ghosts[i].sprite);
    }
    al_destroy_sample(chomp_sound);
    // ... (libérer les autres ressources)

    return 0;
}
