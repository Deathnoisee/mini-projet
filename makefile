all:
	gcc -Isrc/Include -Lsrc/lib -o main main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

run:
	./main
