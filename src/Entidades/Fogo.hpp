#include "ASCII_Engine/ObjetoDeJogo.hpp"
class Fogo : public ObjetoDeJogo
{
    public:
    Fogo(int x, int y);
    virtual ~Fogo();
    
    int getTempoRestante() const { return tempoRestante; }
    void diminuirTempo(){tempoRestante--;}
    private:
        int tempoRestante;
    
};