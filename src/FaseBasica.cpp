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
	p1 = new Bomberman("Bomberman", Sprite("rsc/bomberman.img"), 35, 7, 3, 1, 1);
	personagem_handler->adicionarPersonagem(p1);

	inimigo = new Inimigo("Inimigo",Sprite("rsc/inimigo.img"),5,133,3,1,1);
	personagem_handler->adicionarPersonagem(inimigo);

	acefalo = new Acefalo("Acefalo", Sprite("rsc/acefalo.img"), 8, 14, 1, 1, 1);
	personagem_handler->adicionarPersonagem(acefalo);

	acefalo2 = new Acefalo("Acefalo", Sprite("rsc/acefalo.img"), 23, 126, 1, 1, 1);
	personagem_handler->adicionarPersonagem(acefalo2);
	// Adiciona os personagens ao handler
std::vector<std::vector<int>> matriz_inicial = {
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0}  
};


	objs.push_back(new ObjetoDeJogo("Life",TextSprite(std::to_string(p1->getVidas())),42,17));
	SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	lifebomberman = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("Bombas",TextSprite(std::to_string(p1->getBombasDisponiveis())),43,17));
	SpriteBase *tmp2 = const_cast<SpriteBase*> (objs.back()->getSprite());
	bombasbomberman = dynamic_cast<TextSprite*> (tmp2);

	objs.push_back(new ObjetoDeJogo("Buff",TextSprite(std::to_string(p1->getBuffsBomba())),44,17));
	SpriteBase *tmp3 = const_cast<SpriteBase*> (objs.back()->getSprite());
	buffbomberman = dynamic_cast<TextSprite*> (tmp3);
	
	// Infos Inimigo

	objs.push_back(new ObjetoDeJogo("Life",TextSprite(std::to_string(inimigo->getVidas())),42,125));
	SpriteBase *tmpi = const_cast<SpriteBase*> (objs.back()->getSprite());
	lifeinimigo = dynamic_cast<TextSprite*> (tmpi);

	objs.push_back(new ObjetoDeJogo("Bombas",TextSprite(std::to_string(inimigo->getBombasDisponiveis())),43,125));
	SpriteBase *tmpi2 = const_cast<SpriteBase*> (objs.back()->getSprite());
	bombasinimigo = dynamic_cast<TextSprite*> (tmpi2);

	objs.push_back(new ObjetoDeJogo("Buff",TextSprite(std::to_string(inimigo->getBuffsBomba())),44,125));
	SpriteBase *tmpi3 = const_cast<SpriteBase*> (objs.back()->getSprite());
	buffinimigo = dynamic_cast<TextSprite*> (tmpi3);




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
		// Atualiza informações do bomberman
		lifebomberman->setText(std::to_string(p1->getVidas()));
		bombasbomberman->setText(std::to_string(p1->getBombasDisponiveis()));
		buffbomberman->setText(std::to_string(p1->getBuffsBomba()));
		// Atualiza informações do inimigo
		lifeinimigo->setText(std::to_string(inimigo->getVidas()));
		bombasinimigo->setText(std::to_string(inimigo->getBombasDisponiveis()));
		buffinimigo->setText(std::to_string(inimigo->getBuffsBomba()));
		
        char tecla = Keyboard::read();
		if (tecla == 'q' || tecla == 'Q') 
		{
			return Fase::MENU;
		}
		
		personagem_handler->tomarDecisoes(tecla, bloco_handler->getBlocosAtivos(), bomba_handler->getAtivas(),matriz_entidades);
		bomba_handler->comunicaAtivas(personagem_handler->getSoltas());
		

		fogo_handler->comunicaExplodidas(bomba_handler->getExplodidas(), bloco_handler->getBlocosAtivos(), personagem_handler->getPersonagens());
		fogo_handler->checarColisaoPersonagem(personagem_handler->getPersonagens());
		fogo_handler->checarColisaoBloco(bloco_handler->getBlocosAtivos());
		
		bloco_handler->recebeBlocosColididos(fogo_handler->getBlocosColididos());

		powerup_handler->recebeBlocosQuebrados(bloco_handler->getQuebrados());

		powerup_handler->SearchConsumidos(personagem_handler->getPersonagens());
		personagem_handler->recebePersonagensColididos(fogo_handler->getPersonagensColididos());

		if(p1->getVidas() <= 0) {
			return Fase::GAME_OVER;
		}

		if(inimigo->getVidas() <= 0) {
			return Fase::GAME_WIN;
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
			std::cout << bomba->getPosL() << " " << bomba->getPosC() << " " << bomba->getBuff() << std::endl;
		}
		
		std::cout << "Fogo: " << std::endl;
		for(auto &fogo : fogo_handler->getFogosAtivos()) {
			std::cout << fogo->getPosL() << " " << fogo->getPosC() << std::endl;
		}
		
		std::cout << "PowerUps: " << std::endl;
		for(auto &powerup : powerup_handler->getPowerUpsAtivos()) {
			std::cout << powerup->getPosL() << " " << powerup->getPosC() << std::endl;
		}
		
	    for (const auto& linha : matriz_entidades) {
        for (int valor : linha) {
            std::cout << valor << " ";
        }
        std::cout << "\n";
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

	setNaMatriz(p1->getPosL(), p1->getPosC(),5);
	setNaMatriz(inimigo->getPosL(), inimigo->getPosC(),6);
		
}	



