#include <string>
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class PowerUp : public ObjetoDeJogo
{

public:
    PowerUp(const Sprite &s, int x, int y, std::string tipo)
        : ObjetoDeJogo("PowerUp", s, x, y), tipo(tipo) {}
    ~PowerUp() {}

    std::string getTipo() const { return tipo; }
private:
    std::string tipo;
};