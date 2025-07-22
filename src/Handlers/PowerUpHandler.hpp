#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "../Entidades/Personagem.hpp"
#include "../Entidades/PowerUp.hpp"
#include "../Entidades/Bloco.hpp"

class PowerUpHandler : public ObjetoDeJogo
{
public:
    PowerUpHandler(const std::string &nome, const Sprite &sprite, int x, int y)
        : ObjetoDeJogo(nome, sprite, x, y) {}
    virtual ~PowerUpHandler() {
        for (auto &powerup : powerUpsAtivos) {
            delete powerup;
        }
        powerUpsAtivos.clear();
        for (auto &powerup : powerUpsConsumidos) {
            delete powerup;
        }
        powerUpsConsumidos.clear();
    }

    std::list<PowerUp*>& getPowerUpsAtivos() { return powerUpsAtivos; }
    void SearchConsumidos(std::list<Personagem*> &personagens);
    void recebeBlocosQuebrados(std::list<Bloco*> &blocosQuebrados);
    void LimpaConsumidos();
    void update();
    void draw(SpriteBase &screen, int x, int y);

private:
    std::list<PowerUp*> powerUpsAtivos; // Lista de power-ups ativos
    std::list<PowerUp*> powerUpsConsumidos; // Lista de power-ups consumidos

};