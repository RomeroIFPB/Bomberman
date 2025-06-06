#include "ASCII_Engine/ObjetoDeJogo.hpp"

class PowerUpHandler : public ObjetoDeJogo
{
public:
    PowerUpHandler(const std::string &nome, const Sprite &sprite, int x, int y)
        : ObjetoDeJogo(nome, sprite, x, y) {}

    void SearchConsumidos();
    void recebeBlocosQuebrados();
    void LimpaConsumidos();
    
    void update();
    void draw(SpriteBase &screen, int x, int y);
};