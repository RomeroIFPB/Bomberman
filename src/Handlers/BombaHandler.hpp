#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bomba.hpp"


class BombaHandler : public ObjetoDeJogo
{
    public:
        BombaHandler(const std::string &name, const SpriteBase &sprite, int posL, int posC)
            : ObjetoDeJogo(name, sprite, posL, posC) {}
        virtual ~BombaHandler() {
            for (auto &b : bombasAtivas) {
                delete b;
            }
            bombasAtivas.clear();
            for (auto &b : bombasExplodidas) {
                delete b;
            }
            bombasExplodidas.clear();
        }
        
        std::list<Bomba*>& getExplodidas() {return bombasExplodidas;};
        void comunicaAtivas(std::list<Personagem*> soltas);
        void LimpaExplodidas();
        void diminuiPavios();
        void limpaTudo();
        void update() override;
        void draw(SpriteBase &screen, int x = 0, int y = 0) override;
        std::list<Bomba*>& getAtivas() {return bombasAtivas;};
    private:
        std::list<Bomba*> bombasAtivas; // Lista de bombas ativas
        std::list<Bomba*> bombasExplodidas; // Lista de bombas explodidas
};