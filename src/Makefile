#Variables
SRC = $(wildcard graphisme/*.c)
SRC2 = $(wildcard moteur_jeu/*.c)
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
EXEC = awale
CC = gcc
CFLAGS = -O2 -Wall -pedantic -Werror `sdl-config --cflags` -g
LDFLAGS = -lSDL2 -lSDL2_image `sdl-config --libs` -lm -lSDL2_ttf -g


#Exécution du projet :
run : all
	./$(EXEC) &

#Construction du projet :
all : $(EXEC)

#Edition de liens
$(EXEC) : $(OBJ) $(OBJ2)
	$(CC) $^ -o $@ $(LDFLAGS)

#Compilation séparée
%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

graphisme.o : graphisme.h

#Suppression de fichier généré
clean :
	rm -f graphisme/*.o
	rm -f moteur_jeu/*.o
	rm -f $(EXEC)

#Installation de la librairie SDL2 et extensions
install:
	sudo apt-get install -y libsdl2-dev
	sudo apt-get install -y libsdl2-image-dev
	sudo apt-get install -y libsdl2-ttf-dev
