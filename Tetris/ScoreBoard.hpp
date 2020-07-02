#pragma once

#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

class ScoreBoard
{
public:
	ScoreBoard();
	
	void addPoint();
	void addPoint(const unsigned count);
	void removePoint();
	void removePoint(const unsigned count);
	void resetPoint();

	inline const unsigned getPoint() const { return this->point; }

private:
	unsigned point;
};

#endif // !SCORE_BORAD_HPP
