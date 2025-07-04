#include <list>
#include <vector>
#include "../ASCII_Engine/Fase.hpp"
#include "Entidades/Bomberman.hpp"
#include "Entidades/Acefalo.hpp"
#include "Handlers/PersonagemHandler.hpp"
#include "Handlers/BombaHandler.hpp"
#include "Handlers/FogoHandler.hpp"
#include "Handlers/BlocoHandler.hpp"
#include "Handlers/PowerUpHandler.hpp"


class FaseBasica : public Fase
{
    public:
        FaseBasica(std::string name, const SpriteBase &bkg) : Fase(name,bkg) {}
        virtual ~FaseBasica() {}

        void atualizarMatriz();
        void init() override;
        unsigned run(SpriteBuffer &screen) override;
    private:
        PersonagemHandler* personagem_handler;
        BombaHandler* bomba_handler;
        FogoHandler* fogo_handler;
        BlocoHandler* bloco_handler;
        PowerUpHandler* powerup_handler;
        std::vector<std::vector<int>> matriz_entidades;
        Bomberman *p1;

        TextSprite* lifebomberman;
        TextSprite* bombasbomberman;
        TextSprite* buffbomberman;

        TextSprite* lifeinimigo;
        TextSprite* bombasinimigo;
        TextSprite* buffinimigo;
};