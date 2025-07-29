#include "FogoHandler.hpp"
#include <iostream>


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

void FogoHandler::comunicaExplodidas(std::list<Bomba*> &explodidas, std::list<Bloco*> &blocos, std::list<Personagem*> &personagens) 
{
    for (auto &bomba : explodidas) 
    {
        calcularExplosao(bomba,blocos,personagens);
    }

}

void FogoHandler::LimpaAcabados() {
    
    for (auto it = fogos_acabados.begin(); it != fogos_acabados.end(); ) {
        delete *it; // Assuming Fogo has a proper destructor
        it = fogos_acabados.erase(it);
    }
    fogos_acabados.clear();
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
void FogoHandler::update() 
{
    LimpaAcabados();
    blocos_colididos.clear();
    personagens_colididos.clear();
    for (auto it = fogos_ativos.begin() ; it != fogos_ativos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->update();
    }
    diminuiTempos();
}
void FogoHandler::draw(SpriteBase &screen, int x, int y) 
{
    for (auto it = fogos_ativos.begin() ; it != fogos_ativos.end() ; ++it)
    {
        if ((*it)->getActive())
            (*it)->draw(screen, (*it)->getPosL(), (*it)->getPosC());
    }
}


void FogoHandler::calcularExplosao(Bomba *bomba,std::list<Bloco*> &blocos, std::list<Personagem*> &personagens) 
{
    if(bomba->getBuff() == false)
    {
    // Norte
        int norte_atual = bomba->getPosL() - 3;
        if(norte_atual > 5)
        {
            Fogo* fogo_norte = new Fogo(norte_atual, bomba->getPosC());
            fogos_ativos.push_back(fogo_norte);
        }

    // Sul
        int sul_atual = bomba->getPosL() + 3;
        if(sul_atual < 35)
        {
            Fogo* fogo_sul = new Fogo(sul_atual, bomba->getPosC());
            fogos_ativos.push_back(fogo_sul);
        }

    // Leste
        int leste_atual = bomba->getPosC() + 7;
        if(leste_atual < 133)
        {
            Fogo* fogo_leste = new Fogo(bomba->getPosL(), leste_atual);
            fogos_ativos.push_back(fogo_leste);  
        }
   
    // Oeste
        int oeste_atual = bomba->getPosC() - 7;
        if(oeste_atual > 7)
        {
            Fogo* fogo_oeste = new Fogo(bomba->getPosL(), oeste_atual);
            fogos_ativos.push_back(fogo_oeste);
        }

    }
    else
    {
    // Norte
        int norte_atual = bomba->getPosL() + 3;
        bool colisaonorte = false;
        while(true)
        {
            if (norte_atual < 5) break;
            if (colisaonorte == true) break;
            for (auto &bloco : blocos) 
            {
                if (norte_atual == bloco->getPosL() && bomba->getPosC() == bloco->getPosC()) 
                {
                    Fogo* fogo_norte = new Fogo(norte_atual, bomba->getPosC());
                    fogos_ativos.push_back(fogo_norte);
                    colisaonorte = true;
                }
            }
            for (auto &personagem : personagens) 
            {
                if (norte_atual == personagem->getPosL() && bomba->getPosC() == personagem->getPosC()) 
                {
                    Fogo* fogo_norte = new Fogo(norte_atual, bomba->getPosC());
                    fogos_ativos.push_back(fogo_norte);
                    colisaonorte = true;
                }
            }
            if (colisaonorte == false)
            {
                Fogo* fogo_norte = new Fogo(norte_atual, bomba->getPosC());
                fogos_ativos.push_back(fogo_norte);
            }
            norte_atual -= 3;
        }
    // Sul
    int sul_atual = bomba->getPosL() + 3;
    bool colisaosul = false;
    while(true)
    {
        if (sul_atual > 35) break;
        if (colisaosul == true) break;
        for (auto &bloco : blocos) 
        {
            if (sul_atual == bloco->getPosL() && bomba->getPosC() == bloco->getPosC()) 
            {
                Fogo* fogo_sul = new Fogo(sul_atual, bomba->getPosC());
                fogos_ativos.push_back(fogo_sul);
                colisaosul = true;
            }
        }
        for (auto &personagem : personagens) 
        {
            if (sul_atual == personagem->getPosL() && bomba->getPosC() == personagem->getPosC()) 
            {
                Fogo* fogo_sul = new Fogo(sul_atual, bomba->getPosC());
                fogos_ativos.push_back(fogo_sul);
                colisaosul = true;
            }
        }
        if (colisaosul == false)
        {
            Fogo* fogo_sul = new Fogo(sul_atual, bomba->getPosC());
            fogos_ativos.push_back(fogo_sul);
        }
        sul_atual += 3;
    }
        
    // Oeste
    int oeste_atual = bomba->getPosC() - 7; 
    bool colisaooeste = false;
    while(true)
    {
        if (oeste_atual < 7) break; 
        if (colisaooeste == true) break;
        for (auto &bloco : blocos) 
        {
            if (bomba->getPosL() == bloco->getPosL() && oeste_atual == bloco->getPosC()) 
            {
                Fogo* fogo_oeste = new Fogo(bomba->getPosL(), oeste_atual);
                fogos_ativos.push_back(fogo_oeste);
                colisaooeste = true;
            }
        }
        for (auto &personagem : personagens) 
        {
            if (bomba->getPosL() == personagem->getPosL() && oeste_atual == personagem->getPosC()) 
            {
                Fogo* fogo_oeste = new Fogo(bomba->getPosL(), oeste_atual);
                fogos_ativos.push_back(fogo_oeste);
                colisaooeste = true;
            }
        }
        if (colisaooeste == false)
        {
            Fogo* fogo_oeste = new Fogo(bomba->getPosL(), oeste_atual);
            fogos_ativos.push_back(fogo_oeste);
        }
        oeste_atual -= 7; 
    }

    // Leste
    int leste_atual = bomba->getPosC() + 7; 
    bool colisaoleste = false;
    while(true)
    {
        if (leste_atual > 133) break; 
        if (colisaoleste == true) break;
        for (auto &bloco : blocos) 
        {
            if (bomba->getPosL() == bloco->getPosL() && leste_atual == bloco->getPosC()) 
            {
                Fogo* fogo_leste = new Fogo(bomba->getPosL(), leste_atual);
                fogos_ativos.push_back(fogo_leste);
                colisaoleste = true;
            }
        }
        for (auto &personagem : personagens) 
        {
            if (bomba->getPosL() == personagem->getPosL() && leste_atual == personagem->getPosC()) 
            {
                Fogo* fogo_leste = new Fogo(bomba->getPosL(), leste_atual);
                fogos_ativos.push_back(fogo_leste);
                colisaoleste = true;
            }
        }
        if (colisaoleste == false)
        {
            Fogo* fogo_leste = new Fogo(bomba->getPosL(), leste_atual);
            fogos_ativos.push_back(fogo_leste);
        }
        leste_atual += 7; 
    }


    }
}