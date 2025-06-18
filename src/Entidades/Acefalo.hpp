#include "Personagem.hpp"

class Acefalo : public Personagem
{
public:
    Acefalo(std::string name, const SpriteBase &s, int posL, int posC, int vidas, int bombasMax, int bombasDisponiveis)
        : Personagem(name, s, posL, posC, vidas, bombasMax, bombasDisponiveis) {}

    virtual ~Acefalo() {}

    char decisao(char entrada,std::vector<std::vector<int>> &matriz) override;
    private:
        char ultimaDirecao = 'n';
};