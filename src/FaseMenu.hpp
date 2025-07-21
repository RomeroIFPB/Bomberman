#include "../ASCII_Engine/Fase.hpp"

class Menu : public Fase
{
    public:
        Menu(std::string name, const SpriteBase &bkg) : Fase(name,bkg) {}
        virtual ~Menu() {}

        void init() override;
        unsigned run(SpriteBuffer &screen) override;
};