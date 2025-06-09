#include <string>
#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bloco.hpp"
class BlocoHandler : public ObjetoDeJogo
{
    public:
        BlocoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}

        std::list<Bloco*>& getBlocosAtivos() { return blocosAtivos; }
        void carregaMapa();
        void getQuebrados();
        void recebeBlocosColididos(std::list<Bloco*> &blocosColididos);

        void LimpaQuebrados();

        void update();
        void draw(SpriteBase &screen, int x, int y);

    private:
        std::list<Bloco*> blocosQuebrados;
        std::list<Bloco*> blocosAtivos;

};