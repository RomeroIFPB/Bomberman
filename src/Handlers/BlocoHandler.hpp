#include <string>
#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bloco.hpp"
class BlocoHandler : public ObjetoDeJogo
{
    public:
        BlocoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}
        virtual ~BlocoHandler() {
            for (auto &b : blocosAtivos) {
                delete b;
            }
            blocosAtivos.clear();
            
            for (auto &b : blocosQuebrados) {
                delete b;
            }
            blocosQuebrados.clear();
        }
        std::list<Bloco*>& getBlocosAtivos() { return blocosAtivos; }
        void carregaMapa(std::vector<std::vector<int>> &matriz);
        std::list<Bloco*>& getQuebrados() {return blocosQuebrados;}
        void recebeBlocosColididos(std::list<Bloco*> &blocosColididos);
        void limpaTudo();
        void LimpaQuebrados();

        void update();
        void draw(SpriteBase &screen, int x, int y);

    private:
        std::list<Bloco*> blocosQuebrados;
        std::list<Bloco*> blocosAtivos;

};