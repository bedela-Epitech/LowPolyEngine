

#ifndef _L_DIAMOND_HPP_
#define _L_DIAMOND_HPP_

#include <random>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

enum flag {NORMAL, RIGHT_END, BOTTOM_END};

class Diamond
{

public:
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;
    unsigned int							_size;
    float							        _depth = 0;

private:
	std::vector<std::vector<float>>	_map;
	float		    _height;
    std::mt19937    _gen;
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
