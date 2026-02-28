# Nom du compilateur
CC = gcc

# Nom du fichier exécutable
TARGET = jeu

# Fichiers source
SRC = game.c menu.c

# Flags SDL2 et extensions
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Règle par défaut
all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Nettoyage
clean:
	rm -f $(TARGET) *.o
