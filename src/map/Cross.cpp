
#include "map/Cross.hpp"

Cross::Cross(const float &height) : _height(height)
{
}

Cross::~Cross()
{
}

float		Cross::getMiddle(const float &randValue)
{
	_middle = (_topleft + _topRight + _botLeft + _botRight) / 4.f + randValue;
	return (_middle);
}

float		Cross::leftCross() const
{
	return (_topleft + _botLeft + _middle);
}

float		Cross::RightCross() const
{
	return (_topRight + _botRight + _middle);
}

float		Cross::TopCross() const
{
	return (_topleft + _topRight + _middle);
}

float		Cross::BotCross() const
{
	return (_botLeft + _botRight + _middle);
}

