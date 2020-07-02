#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include<SFML\Graphics.hpp>
#include<vector>
#include"Figure.hpp"
#include"ScoreBoard.hpp"



class Game
{
public:
	Game(
		sf::Texture& figureTexture, 
		sf::Texture& backgrond,
		sf::Texture& gameOverTexture, 
		sf::Font& progressFont, 
		sf::Vector2i sizeField
	);

	void Draw(sf::RenderWindow& window);
	void update(float time);
	void control(sf::RenderWindow& window);
	sf::Uint32 checkLines();
	void resetLine();

	//Accessors
	inline sf::Event& getEvent() { return this->event; }	// получение события

private:
	//Progress
	ScoreBoard			progress;
	sf::Text			progressText;

	//Sprites
	sf::Sprite			gameOverSprite;
	sf::Sprite			backGroundSprite;
	sf::Sprite			figureSprite;

	sf::Vector2u		sizeField;
	Matrix				field;
	Figure				active;
	Figure				generate;

	sf::RectangleShape	hitBox;

	//Engine
	sf::Event			event;	
	bool				gameOver;

};

#endif // !GAME_HPP



