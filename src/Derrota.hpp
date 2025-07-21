#include "../ASCII_Engine/Fase.hpp"

class Derrota : public Fase
{
    public:
        Derrota(std::string name, const SpriteBase &bkg) : Fase(name,bkg) {}
        virtual ~Derrota() {}

        void init() override;
        unsigned run(SpriteBuffer &screen) override;
};