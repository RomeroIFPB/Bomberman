#pragma once

class Bloco : public ObjetoDeJogo
{
    public:
        Bloco(int x, int y)
            : ObjetoDeJogo("Bloco", Sprite("rsc/bloco.img",COR::AZUL), x, y) {}
            
};