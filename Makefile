LINK=g++ -o starship *.o -lSDL2 -lSDL2_image -lSDL2_ttf

fedora:
	g++ -c src/*.cpp -I /usr/include/SDL2/
	$(LINK)
raspbian:
	g++ -c src/*.cpp -I /usr/local/include/SDL2/
	$(LINK)
