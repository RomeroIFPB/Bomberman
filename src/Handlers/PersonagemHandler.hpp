#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Personagem.hpp"
#include "../Entidades/Bomba.hpp"
#include "../Entidades/Bloco.hpp"
#include <list>

class PersonagemHandler : public ObjetoDeJogo
{
public:

    PersonagemHandler(const std::string &name, const SpriteBase &sprite, int posL, int posC)
        : ObjetoDeJogo(name, sprite,posL,posC) {}

    virtual ~PersonagemHandler()
    {
        limpaMortos(); // Limpa os personagens mortos
        for (auto &p : personagens) {
            delete p; // Libera a memória do personagem
        }
        personagens.clear();
        soltou_bomba.clear();
    }

    std::list<Personagem*>& getPersonagens() {return personagens;};

    void adicionarPersonagem(Personagem *personagem);

    std::list<Personagem*> getSoltas() const {return soltou_bomba;};
    void limpaMortos();
    void tomarDecisoes(char tecla, std::list<Bloco*> &blocos, std::list<Bomba*> &bombas, std::vector<std::vector<int>> &matriz);
    void designaBomba(Personagem *p);
    void recebePersonagensColididos(std::list<Personagem*> &colididos);
    void limpaBombardeios();
    void update() override;
    void draw(SpriteBase &screen, int x, int y) override;
    bool tem_barreira(char tecla, Personagem* &p, std::list<Bloco*> &blocos, std::list<Bomba*> &bombas);
    void tem_personagem(char tecla, Personagem* &p);
    void limpaTudo();
    
private:
    std::list<Personagem*> personagens;
    std::list <Personagem*> soltou_bomba;
};