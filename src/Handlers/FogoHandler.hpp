#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bomba.hpp"
#include "../Entidades/Fogo.hpp"

class FogoHandler : public ObjetoDeJogo
{
    public:
        FogoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}

        void getBlocosColididos();
        void getPersonagensColididos();
        void comunicaExplodidas(std::list<Bomba*> &explodidas);
        void searchAcabados();
        void LimpaPersonagensColididos();
        void LimpaBlocosColididos();
        void LimpaAcabados();
        void diminuiTempos();
        void update();
        void draw(SpriteBase &screen, int x, int y);
    private:
        void calcularExplosao(Bomba *bomba);
        std::list<Fogo*> fogos_ativos;
        std::list<Fogo*> fogos_acabados;
};