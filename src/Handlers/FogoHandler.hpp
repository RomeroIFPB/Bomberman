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
        virtual ~FogoHandler() {
            for (auto &fogo : fogos_ativos) {
                delete fogo; 
            }
            fogos_ativos.clear();
            for (auto &fogo : fogos_acabados) {
                delete fogo; 
            }
            fogos_acabados.clear();
        }
        std::list<Fogo*>& getFogosAtivos() { return fogos_ativos; }
        std::list<Bloco*>& getBlocosColididos() { return blocos_colididos; }
        std::list<Personagem*>& getPersonagensColididos() { return personagens_colididos; }
        void comunicaExplodidas(std::list<Bomba*> &explodidas,std::list<Bloco*> &blocos, std::list<Personagem*> &personagens);
        void checarColisaoBloco(std::list<Bloco*> &b);
        void checarColisaoPersonagem(std::list<Personagem*> &p);
        void searchAcabados();
        void LimpaAcabados();
        void diminuiTempos();
        void calcularExplosao(Bomba *bomba, std::list<Bloco*> &blocos, std::list<Personagem*> &personagens);
        void limpaTudo();
        void update();
        void draw(SpriteBase &screen, int x, int y);
    private:

        std::list<Fogo*> fogos_ativos;
        std::list<Fogo*> fogos_acabados;
        std::list<Bloco*> blocos_colididos;
        std::list<Personagem*> personagens_colididos;
};