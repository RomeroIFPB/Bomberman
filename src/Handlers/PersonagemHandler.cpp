#include "PersonagemHandler.hpp"
#include <iostream>
void PersonagemHandler::tomarDecisoes(char tecla) {
    for (auto &personagem : personagens) {
        if (personagem->getActive()) {
            char resultado = personagem->decisao(tecla);
            if (resultado == 'b' && personagem->getBombasDisponiveis() > 0) {
                designaBomba(personagem);
                personagem->diminuirBombas();
            }
            else if (resultado == 'm')
            {
                personagem->mover(tecla);
            }

        } 
    }
}

void PersonagemHandler::adicionarPersonagem(Personagem *personagem) {
    if (personagem) {
        personagens.push_back(personagem);
    } else {
        std::cerr << "Erro: Tentativa de adicionar um personagem nulo." << std::endl;
    }
}

void PersonagemHandler::designaBomba(Personagem *p) {
    soltou_bomba.push_back(p);
}
void PersonagemHandler::recebePersonagensColididos() {
    // Implement logic to receive collided characters
}
void PersonagemHandler::limpaBombardeios() {
    soltou_bomba.clear();
}
void PersonagemHandler::update() {
    limpaBombardeios();
    for (auto it = personagens.begin() ; it != personagens.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
}
void PersonagemHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = personagens.begin() ; it != personagens.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}