#include "audio.h"

static SAMPLE *eat_sound;
static SAMPLE *death_sound;

void play_eat_sound() {
    play_sample(eat_sound, 255, 128, 1000, FALSE);
}

void play_death_sound() {
    play_sample(death_sound, 255, 128, 1000, FALSE);
}
