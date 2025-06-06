#include "Game.hpp"

void Game::run()
{
    SpriteBuffer screen(147,41,'.'); // LARGURA , ALTURA
    FaseBasica fase1("Fase1", Sprite("rsc/background.img"));
    fase1.init();
    fase1.run(screen);
}