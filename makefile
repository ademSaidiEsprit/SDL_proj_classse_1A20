all: main1

main1: theMain.o sauv_main.o sauv_menu.o sauve_button.o joueur.o menu.o main.o source.o main_principal.o menu_principal.o ryen_main.o menu_option.o enigme_main.o sous_menu_enigme.o
	gcc theMain.o sauv_main.o sauv_menu.o sauve_button.o joueur.o menu.o main.o source.o main_principal.o menu_principal.o ryen_main.o menu_option.o enigme_main.o sous_menu_enigme.o -o main1 `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf

theMain.o: theMain.c
	gcc -c theMain.c `sdl2-config --cflags`

sauv_main.o: sauv_main.c
	gcc -c sauv_main.c `sdl2-config --cflags`

sauv_menu.o: sauv_menu.c
	gcc -c sauv_menu.c `sdl2-config --cflags`

sauve_button.o: sauve_button.c
	gcc -c sauve_button.c `sdl2-config --cflags`

joueur.o: joueur.c
	gcc -c joueur.c `sdl2-config --cflags`

menu.o: menu.c
	gcc -c menu.c `sdl2-config --cflags`

main.o: main.c
	gcc -c main.c `sdl2-config --cflags`

source.o: source.c
	gcc -c source.c `sdl2-config --cflags`

main_principal.o: main_principal.c
	gcc -c main_principal.c `sdl2-config --cflags`

menu_principal.o: menu_principal.c
	gcc -c menu_principal.c `sdl2-config --cflags`

ryen_main.o: ryen_main.c
	gcc -c ryen_main.c `sdl2-config --cflags`

menu_option.o: menu_option.c
	gcc -c menu_option.c `sdl2-config --cflags`

enigme_main.o: enigme_main.c
	gcc -c enigme_main.c `sdl2-config --cflags`

sous_menu_enigme.o: sous_menu_enigme.c
	gcc -c sous_menu_enigme.c `sdl2-config --cflags`

clean:
	rm -f *.o

fclean: clean
	rm -f main1

re: fclean all
