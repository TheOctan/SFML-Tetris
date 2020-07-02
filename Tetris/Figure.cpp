#include "Figure.hpp"
#include<cstdlib>
#include<ctime>

Figure::Figure(
	sf::Texture&	texture,
	bool			dinamic,
	sf::Vector2i	size
	
)
:	Figure(texture, rand(), rand(), size, dinamic)
{

}

Figure::Figure(
	sf::Texture&	texture,
	sf::Uint32		number,
	sf::Uint32		color,
	sf::Vector2i	size,
	bool			dinamic
)
:	sizeField	(size),
	offsetDx	(0),
	offset		(0, 0),
	dx			(0),
	number		(number % 7),
	color		(1 + color % 7),
	timer		(0.f),
	delay		(0.3f),
	dinamic		(dinamic),
	gameOver	(false)
{
	this->sprite.setTexture(texture);

	if(this->dinamic)
		this->offsetDx = rand() % (this->sizeField.x - 1);

	for (int i = 0; i < temp.size(); i++)
	{
		tilesPositions[i].x = figures[this->number][i] % 2 + this->offsetDx;
		tilesPositions[i].y = figures[this->number][i] / 2;
	}
}

void Figure::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < tilesPositions.size(); i++)		
	{
		this->sprite.setTextureRect(sf::IntRect(color * 18, 0, 18, 18));
		this->sprite.setPosition(tilesPositions[i].x * 18, tilesPositions[i].y * 18);
		this->sprite.move(28, 31);

		window.draw(this->sprite);
	}
}

void Figure::setColor(sf::Uint32 color)
{
	this->color = 1 + color % 7;
}

void Figure::reset(sf::Uint32 number, sf::Uint32 color)
{
	this->number = number;
	this->color = color;

	if(this->dinamic)
		this->offsetDx = rand() % (this->sizeField.x - 1);

	for (int i = 0; i < temp.size(); i++)
	{
		tilesPositions[i].x = figures[this->number][i] % 2 + this->offsetDx;
		tilesPositions[i].y = figures[this->number][i] / 2;		
	}

	if (!this->dinamic)
		this->setPosition(offset);
}

void Figure::reset()
{
	this->reset(rand() % 7, 1 + rand() % 7);
}

void Figure::setPosition(sf::Vector2i position)
{
	if (!this->dinamic)
	{
		this->offset = position;

		for (int i = 0; i < tilesPositions.size(); i++)
		{
			this->tilesPositions[i].x += offset.x;
			this->tilesPositions[i].y += offset.y;
		}
	}
}

void Figure::setPosition(int x, int y)
{
	if (!this->dinamic)
	{
		this->offset.x = x;
		this->offset.y = y;

		for (int i = 0; i < tilesPositions.size(); i++)
		{
			this->tilesPositions[i].x += offset.x;
			this->tilesPositions[i].y += offset.y;
		}
	}
}

void Figure::boost()
{
	if(this->dinamic)			
		this->delay = 0.05;
}

void Figure::rotate(Matrix& field)
{
	////Rotate////
	if (this->dinamic)
	{
		if (this->number != 6)
		{
			//  cos sin		=>	0 1 *	|x| = (0*x+1*y) (-1*x+0*y) = (y, -x)
			// -sin cos		=> -1 0		|y|

			sf::Vector2i point = tilesPositions[1];
			for (int i = 0; i < tilesPositions.size(); i++)
			{
				sf::Int32 x = tilesPositions[i].y - point.y;
				sf::Int32 y = tilesPositions[i].x - point.x;
				tilesPositions[i].x = point.x - x;
				tilesPositions[i].y = point.y + y;
			}

			if (checkCollision(field))
			{
				for (int i = 0; i < tilesPositions.size(); i++)
				{
					tilesPositions[i] = temp[i];
				}
			}
		}
	}		
}

void Figure::moveLeft()
{
	if(this->dinamic) this->dx = -1;
}

void Figure::moveRight()
{
	if (this->dinamic) this->dx = 1;
}

bool Figure::update(float time, Matrix& field)
{
	if (this->dinamic)
	{
		bool isFell = false;

		this->timer += time;

		//// <-Move-> ////
		for (int i = 0; i < tilesPositions.size(); i++)
		{
			this->temp[i] = this->tilesPositions[i];
			this->tilesPositions[i].x += dx;
		}
		if (checkCollision(field))
		{
			for (int i = 0; i < 4; i++)
			{
				tilesPositions[i] = temp[i];
			}
		}

		////////Tick//////////
		if (this->timer > this->delay)
		{
			for (int i = 0; i < tilesPositions.size(); i++)
			{
				this->temp[i] = this->tilesPositions[i];
				this->tilesPositions[i].y++;
			}

			if (checkCollision(field))
			{
				for (int i = 0; i < tilesPositions.size(); i++)
				{
					if (temp[i].y == 1)
					{
						this->gameOver = true;
					}
				}

				for (int i = 0; i < tilesPositions.size(); i++)
				{
					field[this->temp[i].x][this->temp[i].y] = this->color;
				}

				//this->reset();
				isFell = true;
			}

			this->timer = 0;
		}

		this->dx = 0;
		this->delay = 0.3;

		return isFell;
	}
	else
	{
		return false;
	}
}

bool Figure::checkCollision(Matrix& field)
{
	if (this->dinamic)
	{
		for (int i = 0; i < 4; i++)
		{
			if (
				tilesPositions[i].x < 0 ||
				tilesPositions[i].x >= sizeField.x ||
				tilesPositions[i].y >= sizeField.y
				) return true;

			else if (field[this->tilesPositions[i].x][this->tilesPositions[i].y])
				return true;
		}
	}

	return false;
}
