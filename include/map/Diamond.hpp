

#ifndef _L_DIAMOND_HPP_
#define _L_DIAMOND_HPP_

#include <random>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

enum flag {NORMAL, RIGHT_END, BOTTOM_END};

class Diamond
{

public:
    std::vector<float>                      _trueTriangles;
    std::vector<float>                      _normals;
    std::vector<float>                      _colors;
    unsigned int							_size;
    float							        _depth = 0;

private:
	std::vector<std::vector<float>>	_map;
	float		_height;

public:
	Diamond(const float &, const unsigned int &);

    void	manageSquare(unsigned int , unsigned int , const unsigned int);
    void	manageDiamond(unsigned int, unsigned int , const unsigned int, int);
	void	fillMap();
	void	printMap() const;

	void	updateVertices(float scale, float smooth);
	void	updateTriangles();
	float	boundedRand(float, float);

};


#endif // _L_DIAMOND_HPP_
