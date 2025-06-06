#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "../ASCII_Engine/SpriteBuffer.hpp"
#include "FaseBasica.hpp"

class Game
{
    public:
        Game(){};
        ~Game(){};
        static void run();
};

#endif // GAME_HPP