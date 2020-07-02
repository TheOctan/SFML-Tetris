#include "ScoreBoard.hpp"



ScoreBoard::ScoreBoard() : point(0)
{
}

void ScoreBoard::addPoint()
{
	this->point++;
}

void ScoreBoard::addPoint(const unsigned count)
{
	this->point += count;
}

void ScoreBoard::removePoint()
{
	this->point--;
}

void ScoreBoard::removePoint(const unsigned count)
{
	this->point -= count;
}

void ScoreBoard::resetPoint()
{
	this->point = 0;
}