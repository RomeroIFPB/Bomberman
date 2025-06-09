#include "BlocoHandler.hpp"
#include <iostream>

void BlocoHandler::getQuebrados() {
    // Implement logic to get broken blocks
}

void BlocoHandler::carregaMapa() {
    Bloco* bloco = new Bloco(20, 70);
    blocosAtivos.push_back(bloco);
}

void BlocoHandler::recebeBlocosColididos(std::list<Bloco*> &blocosColididos) 
{
    blocosQuebrados = blocosColididos;
for (auto itQuebrado = blocosQuebrados.begin(); itQuebrado != blocosQuebrados.end(); ) {
    bool encontrado = false;

    // Percorre todos os blocos ativos
    for (auto itAtivo = blocosAtivos.begin(); itAtivo != blocosAtivos.end(); ++itAtivo) {
        if (*itQuebrado == *itAtivo) { // compara os ponteiros diretamente
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        (*itQuebrado)->desativarObj();
        itQuebrado = blocosQuebrados.erase(itQuebrado); // remove e avança
    } else {
        ++itQuebrado; // apenas avança
    }
}

}

void BlocoHandler::LimpaQuebrados() {
    for (auto it = blocosQuebrados.begin(); it != blocosQuebrados.end(); ) {
        delete *it;
        it = blocosQuebrados.erase(it);
    }
    blocosQuebrados.clear();
}

void BlocoHandler::update() {
    LimpaQuebrados();
    for (auto it = blocosAtivos.begin() ; it != blocosAtivos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
}

void BlocoHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = blocosAtivos.begin(); it != blocosAtivos.end(); ++it) {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}

