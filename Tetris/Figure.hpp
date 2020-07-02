#pragma once

#ifndef FIGURE_HPP
#define FIGURE_HPP

#include<SFML\Graphics.hpp>
#include<array>

typedef std::vector<int>			IntVector;
typedef std::vector<IntVector>		Matrix;
typedef std::array<sf::Vector2i,4>	VectorHolder;

class Figure
{
public:
	Figure(
		sf::Texture&	texture,
		bool			dinamic = true,
		sf::Vector2i	size = sf::Vector2i(10, 20)
	);
	Figure(
		sf::Texture&	texture,
		sf::Uint32		number,
		sf::Uint32		color,
		sf::Vector2i	size = sf::Vector2i(10, 20),
		bool			dinamic = true
	);

	void Draw(sf::RenderWindow& window);
	void setColor(sf::Uint32 color);
	void reset(sf::Uint32 number, sf::Uint32 color);
	void reset();
	void setPosition(sf::Vector2i position);
	void setPosition(int x, int y);
	void rotate(Matrix& field);
	void boost();

	//Accessors
	inline int			getColor()	const { return this->color;				}
	inline int			getNumber() const { return this->number;			}
	inline VectorHolder getTiles()	const { return this->tilesPositions;	}
	inline bool			getState()	const { return this->gameOver;			}

	//Control
	void moveLeft();
	void moveRight();

	bool update(float time, Matrix& field);

private:
	bool checkCollision(Matrix& field);

private:
	sf::Sprite		sprite;
	VectorHolder	temp;
	VectorHolder	tilesPositions;
	sf::Vector2i	offset;
	sf::Vector2i	sizeField;

	sf::Uint32		number;
	sf::Uint32		color;
	
	sf::Int32		dx;
	sf::Int32		offsetDx;
	sf::Int32		figures[7][4]{
		1,5,3,7,	//I
		2,4,5,7,	//Z
		3,5,4,6,	//S
		3,5,4,7,	//T
		2,5,3,7,	//L
		3,5,7,6,	//J
		2,3,4,5		//O
	};

	float		timer;
	float		delay;

	bool		dinamic;
	bool		gameOver;
};

#endif // !FIGURE_HPP


