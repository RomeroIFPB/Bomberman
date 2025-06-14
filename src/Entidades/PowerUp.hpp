#include <string>
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class PowerUp : public ObjetoDeJogo
{

public:
    PowerUp(int x, int y)
        : ObjetoDeJogo("PowerUp", Sprite("rsc/bomba_powerup.img"), x, y), tipo("bomba_extra") {}

private:
    std::string tipo;
};