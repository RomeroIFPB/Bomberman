#include "Fogo.hpp"

Fogo::Fogo(int x, int y) 
    : ObjetoDeJogo("Fogo", Sprite("rsc/fogo.img",COR::LARANJA), x, y), tempoRestante(3) {}

Fogo::~Fogo() {
    // Destructor logic if needed
}