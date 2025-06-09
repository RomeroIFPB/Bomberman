#include "FogoHandler.hpp"
#include <iostream>

void FogoHandler::getBlocosColididos() 
{
    std::cout << "Oi!";
}

void FogoHandler::checarColisaoPersonagem(std::list<Personagem*> &p)
{
    for (auto &personagem : p) 
    {
        for (auto it = fogos_ativos.begin(); it != fogos_ativos.end(); ++it) 
        {
            if ((*it)->getPosL() == personagem->getPosL() && 
                (*it)->getPosC() == personagem->getPosC())
            {
                personagens_colididos.push_back(personagem);
            }
        }
    }
}

void FogoHandler::checarColisaoBloco(std::list<Bloco*> &b)
{
    for (auto &bloco : b) 
    {
        for (auto it = fogos_ativos.begin(); it != fogos_ativos.end(); ++it) 
        {
            if ((*it)->getPosL() == bloco->getPosL() && 
                (*it)->getPosC() == bloco->getPosC())
            {
                blocos_colididos.push_back(bloco);
            } 
        }
    }
}

void FogoHandler::getPersonagensColididos() {
    // Implement logic to get collided characters
}
void FogoHandler::comunicaExplodidas(std::list<Bomba*> &explodidas) 
{
    for (auto &bomba : explodidas) 
    {
        calcularExplosao(bomba);
    }

}

void FogoHandler::LimpaAcabados() {
    
    for (auto it = fogos_acabados.begin(); it != fogos_acabados.end(); ) {
        delete *it; // Assuming Fogo has a proper destructor
        it = fogos_acabados.erase(it);
    }
    fogos_acabados.clear();
}


void FogoHandler::LimpaPersonagensColididos() {
    // Implement logic to clear collided characters
}
void FogoHandler::LimpaBlocosColididos() {
    // Implement logic to clear collided blocks
}
void FogoHandler::diminuiTempos() {
    for (auto it = fogos_ativos.begin(); it != fogos_ativos.end(); ) {
        (*it)->diminuirTempo();
        if ((*it)->getTempoRestante() <= 0) {
            fogos_acabados.push_back(*it);
            it = fogos_ativos.erase(it);
        } else {
            ++it;
        }
    }
}
void FogoHandler::update() {
    LimpaAcabados();
    for (auto it = fogos_ativos.begin() ; it != fogos_ativos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
    diminuiTempos();
}
void FogoHandler::draw(SpriteBase &screen, int x, int y) {
    for (auto it = fogos_ativos.begin() ; it != fogos_ativos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}

void FogoHandler::calcularExplosao(Bomba *bomba) {
    // Norte
    int norte_atual = bomba->getPosL() - 3;
    Fogo* fogo_norte = new Fogo(norte_atual, bomba->getPosC());
    fogos_ativos.push_back(fogo_norte);
    // Sul
    int sul_atual = bomba->getPosL() + 3;
    Fogo* fogo_sul = new Fogo(sul_atual, bomba->getPosC());
    fogos_ativos.push_back(fogo_sul);
    // Leste
    int leste_atual = bomba->getPosC() + 7;
    Fogo* fogo_leste = new Fogo(bomba->getPosL(), leste_atual);
    fogos_ativos.push_back(fogo_leste);     
    // Oeste
    int oeste_atual = bomba->getPosC() - 7;
    Fogo* fogo_oeste = new Fogo(bomba->getPosL(), oeste_atual);
    fogos_ativos.push_back(fogo_oeste);
}