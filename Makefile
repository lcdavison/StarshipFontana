fedora:
	g++ -c src/*.cpp -I /usr/include/SDL2/
	g++ -o starship *.o -lSDL2 -lSDL2_image -lSDL2_ttf
raspbian:
	g++ -c src/*.cpp -I /usr/local/include/SDL2/
	g++ -o starship *.o -lSDL2 -lSDL2_image -lSDL2_ttf
