#pragma once
#include <list>
#include <vector>
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Personagem : public ObjetoDeJogo
{
    public:
        Personagem(std::string name, const SpriteBase &s, int posL, int posC, int vidas, int bombasMax, int bombasDisponiveis)
            : ObjetoDeJogo(name,s,posL,posC), vidas(vidas), bombasMax(bombasMax), bombasDisponiveis(bombasMax), buffsBomba(0){}

        virtual ~Personagem() {}

        virtual char decisao(char entrada, std::vector<std::vector<int>> &matriz) = 0;
        void mover(char entrada);
        void aumentarVida();
        void diminuirVida();
        void diminuirBombas();
        void restituirBomba(){bombasDisponiveis++;};
        void aumentarBomba(){bombasDisponiveis++; bombasMax++;};
        void darBuff(){buffsBomba+= 1;};
        void tirarBuff(){buffsBomba-=1;};

        int getVidas() const { return vidas; }
        int getBombasMax() const { return bombasMax; }
        int getBombasDisponiveis() const { return bombasDisponiveis; }
        int getAtivo() const { return ativo; }
        bool getBuffsBomba() const {return buffsBomba;}


    private:
        int vidas;
        int bombasMax;
        int bombasDisponiveis;
        bool ativo;
        int buffsBomba;
};