

#include "map/Diamond.hpp"

Diamond::Diamond(const float &height, const unsigned int &powPower)
{
	srand(time(NULL));
	_height = height;
	_size = (unsigned int)pow(2, powPower) + 1;
	_map = std::vector<std::vector<float>>(_size, std::vector<float>(_size, 0.0));

	_map[0][0] = boundedRand(-height, height);
	_map[_map.size() - 1][0] = boundedRand(-height, height);
	_map[0][_map.size() - 1] = boundedRand(-height, height);
	_map[_map.size() - 1][_map.size() - 1] = boundedRand(-height, height);
}

void    Diamond::manageSquare(const glm::uvec2 &pos, const unsigned int size)
{
	_map[pos.x + size / 2][pos.y + size / 2] =
			((_map[pos.x][pos.y] +
			 _map[pos.x + size][pos.y] +
			 _map[pos.x][pos.y + size] +
			 _map[pos.x + size][pos.y + size]) / 4.f) + boundedRand(-_height, _height);
}

void    Diamond::manageDiamond(const glm::uvec2 &pos, const unsigned int size, int flag)
{
	float topDiamond;
	float leftDiamond;
	float topDivider = 4.f;
	float leftDivider = 4.f;

	if (pos.y < size / 2)
	{
		topDiamond = 0.f;
		topDivider--;
	} else {
		topDiamond = _map[pos.x + size / 2][pos.y - size / 2];
	}


	if (pos.x < size / 2)
	{
		leftDiamond = 0.f;
		leftDivider--;
	} else {
		leftDiamond = _map[pos.x - size / 2][pos.y + size / 2];
	}


	_map[pos.x + size / 2][pos.y] = ((_map[pos.x][pos.y] +
									 _map[pos.x + size][pos.y] +
									 _map[pos.x + size / 2][pos.y + size / 2] +
									 topDiamond) / topDivider) + boundedRand(-_height, _height);

	_map[pos.x][pos.y + size / 2] = ((_map[pos.x][pos.y] +
									 _map[pos.x][pos.y + size] +
									 _map[pos.x + size / 2][pos.y + size / 2] +
									 leftDiamond) / leftDivider) + boundedRand(-_height, _height);
	if (flag & 1)
	{
		_map[pos.x + size][pos.y + size / 2] = ((_map[pos.x + size][pos.y + size] +
												_map[pos.x + size][pos.y] +
												_map[pos.x + size / 2][pos.y + size / 2]) / 3.f) + boundedRand(-_height, _height);
	}
	if (flag & 2)
	{
		_map[pos.x + size / 2][pos.y + size] = ((_map[pos.x + size][pos.y + size] +
												_map[pos.x][pos.y + size] +
												_map[pos.x + size / 2][pos.y + size / 2]) / 3.f) + boundedRand(-_height, _height);
	}
}

void    Diamond::fillMap()
{
	unsigned int    nbSquare = (_size -1) / 2;
	unsigned int    squareSize = _size - 1;
	glm::uvec2      pos;

	for (int i = 1; i <= nbSquare; i *= 2)
	{
		for (int j = 0; j < i * i; ++j)
		{
			pos = glm::uvec2(j % i * squareSize, j / i * squareSize);
			manageSquare(pos, squareSize);
			manageDiamond(pos, squareSize, (2 * (j / i == i - 1)) + (j % i == i - 1));
		}
		squareSize /= 2;
		_height /= 2.f;
	}
	printMap();
}

void	Diamond::printMap() const
{
	for (const auto &vec : _map)
	{
		for (const auto &value : vec)
		{
			std::cout << value << ", ";
		}
		std::cout << std::endl;
	}
}

void	Diamond::updateVertices(float scale, float smooth)
{
	float inc = 1.f / (_map.size() * _map.size());
	float color = 0.f;
	for (int x = 0; x < _map.size() - 1; x++)
	{
		for (int z = 0; z < _map.size() - 1; z++)
		{
			_trueTriangles.push_back(x * scale);
			_trueTriangles.push_back(_map[x][z + 1] * smooth - 100);
			_trueTriangles.push_back((z + 1) * scale);
			_trueTriangles.push_back((x + 1) * scale);
			_trueTriangles.push_back(_map[x + 1][z] * smooth - 100);
			_trueTriangles.push_back(z * scale);
			_trueTriangles.push_back(x * scale);
			_trueTriangles.push_back(_map[x][z] * smooth - 100);
			_trueTriangles.push_back(z * scale);

			glm::vec3 v0(x * scale, _map[x][z + 1] * smooth - 100, (z + 1) * scale);
			glm::vec3 v1((x + 1) * scale, _map[x + 1][z] * smooth - 100, z * scale);
			glm::vec3 v2(x * scale, _map[x][z] * smooth - 100, z * scale);
			glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);
			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);
			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);

			_trueTriangles.push_back((x + 1) * scale);
			_trueTriangles.push_back(_map[x + 1][z + 1] * smooth - 100);
			_trueTriangles.push_back((z + 1) * scale);
			_trueTriangles.push_back((x + 1) * scale);
			_trueTriangles.push_back(_map[x + 1][z] * smooth - 100);
			_trueTriangles.push_back(z * scale);
			_trueTriangles.push_back(x * scale);
			_trueTriangles.push_back(_map[x][z + 1] * smooth - 100);
			_trueTriangles.push_back((z + 1) * scale);

			v0 = glm::vec3((x + 1) * scale, _map[x + 1][z + 1] * smooth - 100, (z + 1) * scale);
			v1 = glm::vec3((x + 1) * scale, _map[x + 1][z] * smooth - 100, z * scale);
			v2 = glm::vec3(x * scale, _map[x][z + 1] * smooth - 100, (z + 1) * scale);
			normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);
			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);
			_normals.push_back(normal.x);
			_normals.push_back(normal.y);
			_normals.push_back(normal.z);

			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);
			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);
			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);

			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);
			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);
			_colors.push_back(0.5f);
			_colors.push_back(color);
			_colors.push_back(0.5f);
			color += inc;
		}
	}
}

float	Diamond::boundedRand(float min, float max)
{
	return (((float)rand() / (float)(RAND_MAX)) * (max - min) + min);
}
