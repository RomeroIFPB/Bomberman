#pragma once
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "Personagem.hpp"

class Bomba : public ObjetoDeJogo
{
    public:
        Bomba(Personagem *dono, bool buff) : ObjetoDeJogo("Bomba", Sprite("rsc/bomba.img"), dono->getPosL(), dono->getPosC()), pavio(5), dono(dono), buff(buff) {}
        virtual ~Bomba() {}

        int getPavio() const { return pavio; }
        Personagem* getDono() const { return dono; }
        bool getBuff() const { return buff; }

        void diminuirPavio() { pavio--;}

    private:
        int pavio;
        bool buff;
        Personagem *dono;
};