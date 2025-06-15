#include "PowerUpHandler.hpp"
#include <iostream>
#include <list>

void PowerUpHandler::SearchConsumidos(std::list<Personagem*> &personagens) {
    for (auto &powerup : powerUpsAtivos)
    {
        for(auto &personagem : personagens) {
            if (powerup->getActive() && personagem->getPosL() == powerup->getPosL() && personagem->getPosC() == powerup->getPosC()) {
                powerUpsConsumidos.push_back(powerup);
                powerup->desativarObj();
                personagem->aumentarBomba();
            }
        }
    }
}
void PowerUpHandler::recebeBlocosQuebrados(std::list<Bloco*> &blocosQuebrados) {
    for (auto &bloco : blocosQuebrados) {
        powerUpsAtivos.push_back(new PowerUp(bloco->getPosL(), bloco->getPosC()));
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
