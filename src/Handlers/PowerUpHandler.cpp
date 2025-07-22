#include "PowerUpHandler.hpp"
#include <iostream>
#include <list>
#include <cstdlib>   
#include <string>


void PowerUpHandler::SearchConsumidos(std::list<Personagem*> &personagens) {
    for (auto &powerup : powerUpsAtivos)
    {
        for(auto &personagem : personagens) {
            if (powerup->getActive() && personagem->getPosL() == powerup->getPosL() && personagem->getPosC() == powerup->getPosC()) {
                powerUpsConsumidos.push_back(powerup);
                powerup->desativarObj();
                // Fazer a lógica para saber como tratar cada tipo de powerup
                if (powerup->getTipo() == "vida") 
                {
                    personagem->aumentarVida();
                    
                } else if (powerup->getTipo() == "bombaforte") 
                {
                    personagem->darBuff();
                } else if (powerup->getTipo() == "bombaextra")
                {
                    personagem->aumentarBomba();
                }
            }
        }
    }
}
void PowerUpHandler::recebeBlocosQuebrados(std::list<Bloco*> &blocosQuebrados) {
    for (auto &bloco : blocosQuebrados) {
            int numero = rand() % 100;
            if (numero < 50) { 
            } else if (numero < 75) {
                powerUpsAtivos.push_back(new PowerUp(Sprite("rsc/powerup_bombaextra.img"),bloco->getPosL(), bloco->getPosC(), "bombaextra"));   // 25% de chance
            } else if (numero < 90) {
                powerUpsAtivos.push_back(new PowerUp(Sprite("rsc/powerup_vida.img",COR::ROSA),bloco->getPosL(), bloco->getPosC(), "vida"));         // 15% de chance
            } else {
                powerUpsAtivos.push_back(new PowerUp(Sprite("rsc/powerup_bombaforte.img",COR::VERDE),bloco->getPosL(), bloco->getPosC(), "bombaforte"));     // 10% de chance
            }
    }
}

void PowerUpHandler::LimpaConsumidos() {

    for (auto it = powerUpsAtivos.begin(); it != powerUpsAtivos.end(); ) 
    {
        if (!(*it)->getActive()) 
        {
            it = powerUpsAtivos.erase(it); // já retorna o próximo válido
        } else 
        {
        ++it;
        }
    }
    for (auto it = powerUpsConsumidos.begin(); it != powerUpsConsumidos.end(); ) {
        delete *it; 
        it = powerUpsConsumidos.erase(it); 
    }
    powerUpsConsumidos.clear();
}

void PowerUpHandler::update() {
    for (auto &powerup : powerUpsAtivos) {
        if (powerup->getActive()) {
            powerup->update();
        }
    }
    LimpaConsumidos();
}

void PowerUpHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto &powerup : powerUpsAtivos) {
        if (powerup->getActive()) {
            powerup->draw(screen,powerup->getPosL(), powerup->getPosC());
        }
    }
}
