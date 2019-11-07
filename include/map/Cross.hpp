
#ifndef _L_CROSS_HPP_

#define _L_CROSS_HPP_

#include "TypeDef.hpp"

class Cross
{
public:
	float _middle;

	float _topleft;
	float _topRight;
	float _botLeft;
	float _botRight;

	float _height;

public:
	Cross(const float &height);
	~Cross();

	float		getMiddle(const float &randValue);

	float		leftCross() const;
	float		RightCross() const;
	float		TopCross() const;
	float		BotCross() const;
};

#endif // _L_CROSS_HPP_
