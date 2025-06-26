#include "BombaHandler.hpp"
#include <iostream>
void BombaHandler::comunicaAtivas(std::list<Personagem*> soltas) {
    for (auto &personagem : soltas) {
        if(personagem->getBuffsBomba() <= 0)
        {
            Bomba *bomba = new Bomba(personagem,false);
            bombasAtivas.push_back(bomba);
        }
        else if(personagem->getBuffsBomba() > 0)
        {
            Bomba *bomba = new Bomba(personagem,true);
            bombasAtivas.push_back(bomba);
            personagem->tirarBuff();
        }
    }
}
void BombaHandler::LimpaExplodidas() {
    for (auto it = bombasExplodidas.begin(); it != bombasExplodidas.end(); ) {
        delete *it;
        it = bombasExplodidas.erase(it);
    }
    bombasExplodidas.clear();
}
void BombaHandler::diminuiPavios() 
{
    for(auto it = bombasAtivas.begin(); it != bombasAtivas.end(); ) 
    {
        if ((*it)->getPavio() <= 0) 
        {
            bombasExplodidas.push_back(*it);
            (*it)->getDono()->restituirBomba();
            it = bombasAtivas.erase(it);
        } 
        else {
            (*it)->diminuirPavio();
            ++it;
        }

    }
}
void BombaHandler::update() {
    LimpaExplodidas();
    for (auto it = bombasAtivas.begin() ; it != bombasAtivas.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
    diminuiPavios();
}
void BombaHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = bombasAtivas.begin() ; it != bombasAtivas.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}
