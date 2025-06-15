#pragma once
#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Personagem : public ObjetoDeJogo
{
    public:
        Personagem(std::string name, const SpriteBase &s, int posL, int posC, int vidas, int bombasMax, int bombasDisponiveis)
            : ObjetoDeJogo(name,s,posL,posC), vidas(vidas), bombasMax(bombasMax), bombasDisponiveis(bombasMax) {}

        virtual ~Personagem() {}

        char decisao(char entrada);
        void mover(char entrada);
        void diminuirVida();
        void diminuirBombas();
        void restituirBomba(){bombasDisponiveis++;};
        void aumentarBomba(){bombasDisponiveis++; bombasMax++;};

        int getVidas() const { return vidas; }
        int getBombasMax() const { return bombasMax; }
        int getBombasDisponiveis() const { return bombasDisponiveis; }
        int getAtivo() const { return ativo; }

    private:
        int vidas;
        int bombasMax;
        int bombasDisponiveis;
        bool ativo;
};