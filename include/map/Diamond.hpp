

#ifndef _L_DIAMOND_HPP_
#define _L_DIAMOND_HPP_

#include "Cross.hpp"
#include "TypeDef.hpp"
#include "Triangle.hpp"
#include <random>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#define MULT 0.3

class Diamond
{

public:
	std::vector<std::vector<Vector3df>>		_vertices;
	std::vector<game::Triangle<float>>		_triangles;
	unsigned int							_size;

private:
	std::vector<std::vector<float>>	_map;
	float		_height;
	std::vector<Cross>	_crosses;

public:
	Diamond(const float &, const unsigned int &);

    void	manageSquare(const glm::uvec2 &, const unsigned int);
    void	manageDiamond(const glm::uvec2 &, const unsigned int);
	void	fillMap();
	void	printMap() const;

	void	updateVertices(float scale, float smooth);
	void	updateTriangles();
	float	boundedRand(float, float);

};


#endif // _L_DIAMOND_HPP_
