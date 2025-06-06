#include <string>
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class BlocoHandler : public ObjetoDeJogo
{
    public:
        BlocoHandler(const std::string &nome, const Sprite &sprite, int x, int y)
            : ObjetoDeJogo(nome, sprite, x, y) {}

        void getQuebrados();
        void recebeBlocosColididos();

        void LimpaQuebrados();

        void update();
        void draw(SpriteBase &screen, int x, int y);
    

};