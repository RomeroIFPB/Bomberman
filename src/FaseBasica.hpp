#include "../ASCII_Engine/Fase.hpp"
#include "Handlers/PersonagemHandler.hpp"
#include "Handlers/BombaHandler.hpp"
#include "Handlers/FogoHandler.hpp"
#include "Handlers/BlocoHandler.hpp"
#include "Handlers/PowerUpHandler.hpp"
#include <list>

class FaseBasica : public Fase
{
    public:
        FaseBasica(std::string name, const SpriteBase &bkg) : Fase(name,bkg) {}
        virtual ~FaseBasica() {}

        void ConcentrarBarreiras();
        void init() override;
        unsigned run(SpriteBuffer &screen) override;
    private:
        PersonagemHandler* personagem_handler;
        BombaHandler* bomba_handler;
        FogoHandler* fogo_handler;
        BlocoHandler* bloco_handler;
        PowerUpHandler* powerup_handler;
        std::list<ObjetoDeJogo*> barreiras;
        Personagem *p1;


};