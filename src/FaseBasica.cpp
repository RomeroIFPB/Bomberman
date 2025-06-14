#include "FaseBasica.hpp"
#include "../ASCII_Engine/input/Keyboard.hpp"

void FaseBasica::init() 
{
    Keyboard::setMode(Keyboard::BLOCKING);

	// Inicialização dos Handlers
	personagem_handler = new PersonagemHandler("Personagem", Sprite("rsc/HandlerSprite.img"),0,0);
	objs.push_back(personagem_handler);
	bomba_handler = new BombaHandler("Bomba", Sprite("rsc/HandlerSprite.img"),0,0);
	objs.push_back(bomba_handler);
	fogo_handler = new FogoHandler("Fogo", Sprite("rsc/HandlerSprite.img"),0,0);
	objs.push_back(fogo_handler);
	bloco_handler = new BlocoHandler("Bloco", Sprite("rsc/HandlerSprite.img"),0,0);
	objs.push_back(bloco_handler);
	powerup_handler = new PowerUpHandler("PowerUp", Sprite("rsc/HandlerSprite.img"),0,0);
	objs.push_back(powerup_handler);

	// Inicialização de entidades

	// Personagens:
	p1 = new Personagem("Player1", Sprite("rsc/bomberman.img"), 5, 7, 3, 1, 1);
	Personagem *p2 = new Personagem("Player2", Sprite("rsc/bomberman.img"), 0, 1, 3, 1, 1);

	// Adiciona os personagens ao handler
	personagem_handler->adicionarPersonagem(p1);
	personagem_handler->adicionarPersonagem(p2);

	p2->desativarObj();

	bloco_handler->carregaMapa();

}

unsigned FaseBasica::run(SpriteBuffer &screen)
{
    //PADRÃO
	screen.clear();
	draw(screen);
	system("clear");
	show(screen);
    
    while(true)
    {
        char tecla = Keyboard::read();

		personagem_handler->tomarDecisoes(tecla);
		bomba_handler->comunicaAtivas(personagem_handler->getSoltas());


		fogo_handler->comunicaExplodidas(bomba_handler->getExplodidas());
		fogo_handler->checarColisaoPersonagem(personagem_handler->getPersonagens());
		fogo_handler->checarColisaoBloco(bloco_handler->getBlocosAtivos());
		
		bloco_handler->recebeBlocosColididos(fogo_handler->getBlocosColididos());

		powerup_handler->recebeBlocosQuebrados(bloco_handler->getQuebrados());

		//powerup_handler->SearchConsumidos(personagem_handler->getPersonagens());
		//personagem_handler->recebePersonagensColididos();


        // ESTADO GERAL DO JOGO
		update();
		draw(screen);
		system("clear");
		show(screen);
		std::cout << p1->getPosL() << " " << p1->getPosC() << " " << p1->getBombasMax() << std::endl;

	}
    return 0;
}

