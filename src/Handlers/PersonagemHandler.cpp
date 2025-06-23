#include "PersonagemHandler.hpp"
#include <iostream>

bool PersonagemHandler::tem_barreira(char tecla, Personagem* &p, std::list<Bloco*> &blocos, std::list<Bomba*> &bombas) 
{
    bool encontrou = false;
    switch (tecla) {
        case 'w':
            if(p->getPosL() - 3 == 2)
            {
                encontrou = true;
            }
            for(auto &bloco : blocos)
            {
                if(p->getPosL() - 3 == bloco->getPosL() && p->getPosC() == bloco->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            for(auto &bomba : bombas)
            {
                if(p->getPosL() - 3 == bomba->getPosL() && p->getPosC() == bomba->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            break;
        case 's':
            if(p->getPosL() + 3 == 38)
            {
                encontrou = true;
            }
            for(auto &bloco : blocos)
            {
                if(p->getPosL() + 3 == bloco->getPosL() && p->getPosC() == bloco->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            for(auto &bomba : bombas)
            {
                if(p->getPosL() + 3 == bomba->getPosL() && p->getPosC() == bomba->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            break;
        case 'a':
            if(p->getPosC() - 7 == 0)
            {
                encontrou = true;
            } 
            for(auto &bloco : blocos)
            {
                if(p->getPosL() == bloco->getPosL() && p->getPosC() - 7 == bloco->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            for(auto &bomba : bombas)
            {
                if(p->getPosL() == bomba->getPosL() && p->getPosC() - 7 == bomba->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            break;
        case 'd':
            if(p->getPosC() + 7 == 140)
            {
                encontrou = true;
            } 
            for(auto &bloco : blocos)
            {
                if(p->getPosL() == bloco->getPosL() && p->getPosC() + 7 == bloco->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            for(auto &bomba : bombas)
            {
                if(p->getPosL() == bomba->getPosL() && p->getPosC() + 7 == bomba->getPosC())
                {
                    encontrou = true;
                    break;
                }
            }
            break;
    }
    if(encontrou == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PersonagemHandler::tomarDecisoes(char tecla, std::list<Bloco*> &blocos, std::list<Bomba*> &bombas,std::vector<std::vector<int>> &matriz) 
{
    for (auto &personagem : personagens) {
        if (personagem->getActive()) {
            char resultado = personagem->decisao(tecla,matriz);
            switch (resultado)
            {
                case 'w':
                    if (!tem_barreira('w', personagem, blocos, bombas)) {
                        personagem->mover('w');
                    }
                    break;
                case 's':
                    if (!tem_barreira('s', personagem, blocos, bombas)) {
                        personagem->mover('s');
                    }
                    break;
                case 'a':
                    if (!tem_barreira('a', personagem, blocos, bombas)) {
                        personagem->mover('a');
                    }
                    break;
                case 'd':
                    if (!tem_barreira('d', personagem, blocos, bombas)) {
                        personagem->mover('d');
                    }
                    break;
                case 'l':
                    if (personagem->getBombasDisponiveis() > 0) {
                        personagem->diminuirBombas();
                        designaBomba(personagem);
                    }
            }
        } 
    }
}

void PersonagemHandler::adicionarPersonagem(Personagem *personagem) 
{
    if (personagem) {
        personagens.push_back(personagem);
    } else {
        std::cerr << "Erro: Tentativa de adicionar um personagem nulo." << std::endl;
    }
}

void PersonagemHandler::designaBomba(Personagem *p) {
    soltou_bomba.push_back(p);
}

void PersonagemHandler::recebePersonagensColididos(std::list<Personagem*> &colididos) 
{
    for (auto &personagem : colididos) {
        for (auto it = personagens.begin(); it != personagens.end(); ++it) {
            if ((*it)->getName() == personagem->getName()) {
                (*it)->diminuirVida();
            }
        }
    }
}

void PersonagemHandler::limpaBombardeios() 
{
    soltou_bomba.clear();
}

void PersonagemHandler::update() 
{
    limpaBombardeios();
    for (auto it = personagens.begin() ; it != personagens.end() ; ++it)
    {
        if ((*it)->getVidas() <= 0)
            (*it)->desativarObj();
    }
    for (auto it = personagens.begin() ; it != personagens.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
}

void PersonagemHandler::draw(SpriteBase &screen, int x, int y) 
{
    for (auto it = personagens.begin() ; it != personagens.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}