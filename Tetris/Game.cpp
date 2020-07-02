#include "Game.hpp"
#include<string>
#include<iostream>

Game::Game(
	sf::Texture& figureTexture, 
	sf::Texture& backgrond,
	sf::Texture& gameOverTexture, 
	sf::Font& progressFont, 
	sf::Vector2i sizeField
)
:	progressText		("0", progressFont),
	figureSprite		(figureTexture),
	backGroundSprite	(backgrond),
	gameOverSprite		(gameOverTexture),
	sizeField			(sizeField),
	field				(sizeField.x, IntVector(sizeField.y, 0)),
	active				(figureTexture, true, sizeField),
	generate			(figureTexture, false),
	hitBox				(sf::Vector2f(sizeField.x * 18, sizeField.y * 18)),
	gameOver			(false)
{
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(-1);

	this->progressText.setPosition(257, 150);
	
	this->gameOverSprite.setScale(0.5f, 0.5f);
	this->gameOverSprite.move(-10, 50);

	this->generate.setPosition(13, 1);
}

void Game::Draw(sf::RenderWindow& window)
{
	window.draw(this->backGroundSprite);		// фон

	for (int i = 0; i < this->sizeField.x; i++)
	{
		for (int j = 0; j < sizeField.y; j++)
		{
			if (field[i][j] == 0) continue;
			this->figureSprite.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
			this->figureSprite.setPosition(i * 18, j * 18);
			this->figureSprite.move(28, 31);

			window.draw(this->figureSprite);
		}
	}

	this->active.Draw(window);	

	this->generate.Draw(window);

	//window.draw(this->hitBox);
	window.draw(this->progressText);

	if (this->gameOver)
		window.draw(this->gameOverSprite);
}

void Game::update(float time)
{
	this->gameOver = this->active.getState();

	if (!this->active.getState() && this->active.update(time, this->field))
	{
		if (!this->active.getState())
		{
			this->progress.addPoint(this->checkLines());
			this->progressText.setString(std::to_string(this->progress.getPoint()));

			this->active.reset(
				this->generate.getNumber(),
				this->generate.getColor()
			);
			this->generate.reset();

			this->resetLine();
		}
	}
}

void Game::control(sf::RenderWindow& window)
{
	while (window.pollEvent(this->event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				this->active.moveRight();
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				this->active.moveLeft();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				this->active.rotate(this->field);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->active.boost();
}

sf::Uint32 Game::checkLines()
{
	sf::Uint32 lines = 0;

	for (int j = 0; j < this->sizeField.y; j++)
	{
		int horizontal = 0;
		for (int i = 0; i < this->sizeField.x; i++)
		{
			if (this->field[i][j]) horizontal++;
		}

		if (horizontal == this->sizeField.x)
			lines++;
	}

	return lines;
}

void Game::resetLine()
{
	//////////check lines///////
	int k = sizeField.y - 1;
	for (int i = sizeField.y - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < sizeField.x; j++)
		{
			if (field[j][i]) count++;
			field[j][k] = field[j][i];
		}
		if (count < sizeField.x) k--;
	}
}
