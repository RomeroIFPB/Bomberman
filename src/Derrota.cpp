#include "Derrota.hpp"
#include "../ASCII_Engine/input/Keyboard.hpp"

void Derrota::init() {
    Keyboard::setMode(Keyboard::NONBLOCKING);
}

unsigned Derrota::run(SpriteBuffer &screen) {
    screen.clear();
	draw(screen);
	system("clear");
	show(screen);
    while (true) 
    {
        char tecla = Keyboard::read();
		if (tecla == 'l' || tecla == 'L') 
		{
			return Fase::GAME_START;
		}
        else if (tecla == 'q' || tecla == 'Q')
        {
            return Fase::END_GAME;
        }
        screen.clear();
	    draw(screen);
	    system("clear");
	    show(screen);
        usleep(500000);
    }
}