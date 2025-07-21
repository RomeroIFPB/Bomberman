#include "Personagem.hpp"

class Inimigo : public Personagem
{
public:
    Inimigo(std::string name, const SpriteBase &s, int posL, int posC, int vidas, int bombasMax, int bombasDisponiveis)
        : Personagem(name, s, posL, posC, vidas, bombasMax, bombasDisponiveis) {}

    virtual ~Inimigo() {}

    char decisao(char entrada,std::vector<std::vector<int>> &matriz) override;
    
};