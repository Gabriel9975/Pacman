# Makefile

CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags allegro-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5`
LDFLAGS = `pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5`
OBJ = main.o game.o graphics.o input.o entities.o utils.o collision.o
EXEC = pacman

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

main.o: main.c game.h graphics.h input.h entities.h utils.h collision.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h entities.h collision.h
	$(CC) $(CFLAGS) -c game.c

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c graphics.c

input.o: input.c input.h game.h
	$(CC) $(CFLAGS) -c input.c

entities.o: entities.c entities.h
	$(CC) $(CFLAGS) -c entities.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

collision.o: collision.c collision.h
	$(CC) $(CFLAGS) -c collision.c

clean:
	rm -f $(OBJ) $(EXEC)
