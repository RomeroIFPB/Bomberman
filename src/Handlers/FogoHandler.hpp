#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bomba.hpp"
#include "../Entidades/Fogo.hpp"
#include "../Entidades/Bloco.hpp"
#include "../Entidades/Personagem.hpp"
class FogoHandler : public ObjetoDeJogo
{
    public:
        FogoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}

        std::list<Bloco*>& getBlocosColididos() { return blocos_colididos; }
        void getPersonagensColididos();
        void comunicaExplodidas(std::list<Bomba*> &explodidas);
        void checarColisaoBloco(std::list<Bloco*> &b);
        void checarColisaoPersonagem(std::list<Personagem*> &p);
        void searchAcabados();
        void LimpaPersonagensColididos();
        void LimpaBlocosColididos();
        void LimpaAcabados();
        void diminuiTempos();
        void calcularExplosao(Bomba *bomba);
        void update();
        void draw(SpriteBase &screen, int x, int y);
    private:

        std::list<Fogo*> fogos_ativos;
        std::list<Fogo*> fogos_acabados;
        std::list<Bloco*> blocos_colididos;
        std::list<Personagem*> personagens_colididos;
};