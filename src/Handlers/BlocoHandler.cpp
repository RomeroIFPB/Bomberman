#include "BlocoHandler.hpp"
#include <iostream>

void BlocoHandler::carregaMapa(std::vector<std::vector<int>> &matriz) 
{
    for(int i = 0; i < matriz.size(); ++i) {
        for(int j = 0; j < matriz[i].size(); ++j) {
            if (matriz[i][j] == 1) { // Bloco ativo
                Bloco *bloco = new Bloco(i * 3 + 5, 7 + j * 7);
                blocosAtivos.push_back(bloco);
            }
        }
    }

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

void BlocoHandler::limpaTudo() {
    for (auto it = blocosAtivos.begin(); it != blocosAtivos.end(); ++it) {
        delete *it; // Libera a memória do bloco
    }
    blocosAtivos.clear();
    
    for (auto it = blocosQuebrados.begin(); it != blocosQuebrados.end(); ++it) {
        delete *it; // Libera a memória do bloco quebrado
    }
    blocosQuebrados.clear();
}

void BlocoHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = blocosAtivos.begin(); it != blocosAtivos.end(); ++it) {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}

