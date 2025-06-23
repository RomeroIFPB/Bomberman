#include "FaseBasica.hpp"
#include "../ASCII_Engine/input/Keyboard.hpp"

void FaseBasica::init() 
{
    Keyboard::setMode(Keyboard::NONBLOCKING);

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
	p1 = new Bomberman("Player1", Sprite("rsc/bomberman.img"), 20, 70, 3, 1, 1);
	personagem_handler->adicionarPersonagem(p1);
	Acefalo* acefalo = new Acefalo("Acefalo", Sprite("rsc/bomberman.img"), 5, 133, 1, 1, 1);
	personagem_handler->adicionarPersonagem(acefalo);
	// Adiciona os personagens ao handler
	std::vector<std::vector<int>> matriz_inicial = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}
    };
	bloco_handler->carregaMapa(matriz_inicial);

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
		if (tecla == 'q' || tecla == 'Q') 
		{
			return Fase::END_GAME;
		}
		
		personagem_handler->tomarDecisoes(tecla, bloco_handler->getBlocosAtivos(), bomba_handler->getAtivas(),matriz_entidades);
		bomba_handler->comunicaAtivas(personagem_handler->getSoltas());


		fogo_handler->comunicaExplodidas(bomba_handler->getExplodidas());
		fogo_handler->checarColisaoPersonagem(personagem_handler->getPersonagens());
		fogo_handler->checarColisaoBloco(bloco_handler->getBlocosAtivos());
		
		bloco_handler->recebeBlocosColididos(fogo_handler->getBlocosColididos());

		powerup_handler->recebeBlocosQuebrados(bloco_handler->getQuebrados());

		powerup_handler->SearchConsumidos(personagem_handler->getPersonagens());
		personagem_handler->recebePersonagensColididos(fogo_handler->getPersonagensColididos());

		if(p1->getVidas() <= 0) {
			std::cout << "GAME OVER" << std::endl;
			return Fase::GAME_OVER;
		}

		update();
		draw(screen);
		system("clear");
		show(screen);
		usleep(500000);
		atualizarMatriz();
		
		/*
		std::cout << "Blocos: " << std::endl;
		for(auto &bloco : bloco_handler->getBlocosAtivos()) {
			std::cout << (bloco->getPosL() - 5)/3 << " " << bloco->getPosC()/7 << std::endl;
		}
		std::cout << "Bombas: " << std::endl;
		for(auto &bomba : bomba_handler->getAtivas()) {
			std::cout << bomba->getPosL() << " " << bomba->getPosC() << std::endl;
		}
		std::cout << "Fogo: " << std::endl;
		for(auto &fogo : fogo_handler->getFogosAtivos()) {
			std::cout << fogo->getPosL() << " " << fogo->getPosC() << std::endl;
		}
		std::cout << "PowerUps: " << std::endl;
		for(auto &powerup : powerup_handler->getPowerUpsAtivos()) {
			std::cout << powerup->getPosL() << " " << powerup->getPosC() << std::endl;
		}
		*/
    }
	
	
	return 0;
}

void FaseBasica::atualizarMatriz()
{
	matriz_entidades = std::vector<std::vector<int>>(11, std::vector<int>(19, 0));


	auto setNaMatriz = [&](int l, int c, int valor){
		int i = (l - 5) / 3;
		int j = (c - 7) / 7;
		if (i >= 0 && i < 11 && j >= 0 && j < 19)
		{
			matriz_entidades[i][j] = valor;
		}
		else
		{
			std::cerr << "Tentativa de acesso fora da matriz: (" << l << ", " << c << ")\n";
			std::cout << "i: " << i << ", j: " << j << std::endl;
		}
			
			
	};
	
	for (auto &bloco : bloco_handler->getBlocosAtivos())
		setNaMatriz(bloco->getPosL(), bloco->getPosC(), 1);

	for (auto &bomba : bomba_handler->getAtivas())
		setNaMatriz(bomba->getPosL(), bomba->getPosC(), 2);

	for (auto &fogo : fogo_handler->getFogosAtivos())
		setNaMatriz(fogo->getPosL(), fogo->getPosC(), 3);

	for (auto &powerup : powerup_handler->getPowerUpsAtivos())
		setNaMatriz(powerup->getPosL(), powerup->getPosC(), 4);

	for (auto &personagem : personagem_handler->getPersonagens())
		setNaMatriz(personagem->getPosL(), personagem->getPosC(), 5);
		
}	


