all:
	g++ -std=c++11 -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf src/*.cpp -o main

run:
	./main


