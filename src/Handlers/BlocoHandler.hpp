#include <string>
#include <list>
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "../Entidades/Bloco.hpp"
class BlocoHandler : public ObjetoDeJogo
{
    public:
        BlocoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}
        virtual ~BlocoHandler()
        {
            LimpaQuebrados();
            for (auto &bloco : blocosAtivos) {
                delete bloco; // Libera a memória do bloco ativo
            }
            blocosAtivos.clear();
            
            for (auto &bloco : blocosQuebrados) {
                delete bloco; // Libera a memória do bloco quebrado
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