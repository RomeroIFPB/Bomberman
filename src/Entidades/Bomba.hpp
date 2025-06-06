#pragma once
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "Personagem.hpp"

class Bomba : public ObjetoDeJogo
{
    public:
        Bomba(Personagem *dono) : ObjetoDeJogo("Bomba", Sprite("rsc/bomba.img"), dono->getPosL(), dono->getPosC()), pavio(3), dono(dono) {}
        virtual ~Bomba() {}

        int getPavio() const { return pavio; }
        Personagem* getDono() const { return dono; }
        void diminuirPavio() { pavio--;}

    private:
        int pavio;
        Personagem *dono;
};