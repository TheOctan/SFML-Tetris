//Tetris_main.cpp
//

#include<SFML\Graphics.hpp>
#include<iostream>

#include"Game.hpp"

using namespace std;
using namespace sf;

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(320, 480), "Tetris", Style::Close);

	Image icon;
	icon.loadFromFile("images/Tetris.png");

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Texture figureTexture;
	Texture background;
	Texture frame;
	Texture gameOverTexture;
	Font	progressFont;

	figureTexture.		loadFromFile("images/tiles.png");	
	background.			loadFromFile("images/background.png");
	gameOverTexture.	loadFromFile("images/gameover.png");	
	progressFont.		loadFromFile("fonts/digifaw.TTF");

	Game game(
		figureTexture, 
		background,
		gameOverTexture, 
		progressFont, 
		sf::Vector2i(10, 20)
	);
	
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		game.control(window);
		game.update(time);

		window.clear();
		game.Draw(window);
		window.display();
	}

	return 0;
}
