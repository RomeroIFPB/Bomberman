#include "Game.hpp"
#include "Vitoria.hpp"
#include "Derrota.hpp"
#include "FaseMenu.hpp"

void Game::run()
{
    SpriteBuffer screen(147,46,' '); // LARGURA , ALTURA
    


    while (true)
    {
        Menu faseMenu("Menu", SpriteAnimado("rsc/menu.img",5));
        faseMenu.init();
        unsigned resultadomenu = faseMenu.run(screen);
        
        unsigned resultadojogo;
        unsigned opcaofinal;
        if (resultadomenu == Fase::END_GAME) {
            return; // Encerrar o jogo
        } else if (resultadomenu == Fase::GAME_START) {
            FaseBasica fase1("Fase1", Sprite("rsc/background.img"));
            fase1.init();
            resultadojogo = fase1.run(screen);
        }

        if (resultadojogo == Fase::GAME_WIN) {
            Vitoria fasevitoria("Vitoria", Sprite("rsc/gamewin.img"));
            fasevitoria.init();
            opcaofinal = fasevitoria.run(screen);
        } else if (resultadojogo == Fase::GAME_OVER) {
            Derrota fasederrota("Derrota", Sprite("rsc/gameover.img"));
            fasederrota.init();
            opcaofinal = fasederrota.run(screen);
        }
        else if (resultadojogo == Fase::MENU) {
            continue;
        }

        if (opcaofinal == Fase::GAME_START) {
            continue;
        } else if (opcaofinal == Fase::END_GAME) {
            return;
        }
        
    }

}