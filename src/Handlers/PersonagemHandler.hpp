#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Personagem.hpp"
#include <list>

class PersonagemHandler : public ObjetoDeJogo
{
public:

    PersonagemHandler(const std::string &name, const SpriteBase &sprite, int posL, int posC)
        : ObjetoDeJogo(name, sprite,posL,posC) {}

    virtual ~PersonagemHandler() {}

    std::list<Personagem*>& getPersonagens() {return personagens;};

    void adicionarPersonagem(Personagem *personagem);

    std::list<Personagem*> getSoltas() const {return soltou_bomba;};
    void tomarDecisoes(char tecla);
    void designaBomba(Personagem *p);
    void recebePersonagensColididos(std::list<Personagem*> &colididos);
    void limpaBombardeios();
    void update() override;
    void draw(SpriteBase &screen, int x, int y) override;

private:
    std::list<Personagem*> personagens;
    std::list <Personagem*> soltou_bomba;
};