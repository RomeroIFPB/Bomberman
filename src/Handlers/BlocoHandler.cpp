#include "BlocoHandler.hpp"
#include <iostream>

void BlocoHandler::carregaMapa() {
    Bloco* bloco = new Bloco(20, 70);
    blocosAtivos.push_back(bloco);
}

void BlocoHandler::recebeBlocosColididos(std::list<Bloco*> &blocosColididos) 
{
    for (auto &bloco : blocosColididos) {
        if (bloco->getActive()) {
            bloco->desativarObj();
            blocosQuebrados.push_back(bloco);
        }
    }
}

void BlocoHandler::LimpaQuebrados() {

    for (auto it = blocosAtivos.begin(); it != blocosAtivos.end(); ) {
        if (!(*it)->getActive()) {
            it = blocosAtivos.erase(it); // Remove o bloco da lista
        } else {
            ++it; // Avança para o próximo bloco ativo
        }
    }

    for (auto it = blocosQuebrados.begin(); it != blocosQuebrados.end();) {
        delete *it;
        it = blocosQuebrados.erase(it);
    }
    
    blocosQuebrados.clear();
}

void BlocoHandler::update() {
    for (auto it = blocosAtivos.begin() ; it != blocosAtivos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }

    LimpaQuebrados();
}

void BlocoHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = blocosAtivos.begin(); it != blocosAtivos.end(); ++it) {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}

