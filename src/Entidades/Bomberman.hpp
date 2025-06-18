#include "Personagem.hpp"

class Bomberman : public Personagem
{
public:
    Bomberman(std::string name, const SpriteBase &s, int posL, int posC, int vidas, int bombasMax, int bombasDisponiveis)
        : Personagem(name, s, posL, posC, vidas, bombasMax, bombasDisponiveis) {}

    virtual ~Bomberman() {}

    char decisao(char entrada,std::vector<std::vector<int>> &matriz) override;
};