#include "../ASCII_Engine/Fase.hpp"

class Vitoria : public Fase
{
    public:
        Vitoria(std::string name, const SpriteBase &bkg) : Fase(name,bkg) {}
        virtual ~Vitoria() {}

        void init() override;
        unsigned run(SpriteBuffer &screen) override;
};