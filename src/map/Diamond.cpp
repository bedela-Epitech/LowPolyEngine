

#include "map/Diamond.hpp"

Diamond::Diamond(const float &height, const int &size)
{
	srand(time(NULL));
	_height = height;
	std::vector<float> vector;
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			vector.push_back(0);
		}
		_map.push_back(vector);
		vector.clear();
	}

	_map[0][0] = 0;// ((float)rand() / (float)(RAND_MAX)) * height;
	_map[_map.size() - 1][0] = 0;//((float)rand() / (float)(RAND_MAX)) * height;
	_map[0][_map.size() - 1] = 0;//((float)rand() / (float)(RAND_MAX)) * height;
	_map[_map.size() - 1][_map.size() - 1] = 0.4f;//((float)rand() / (float)(RAND_MAX)) * height;

}

Diamond::~Diamond()
{

}

void	Diamond::square(const Vector2di &pos, const unsigned int &size)
{
	Cross		cross(_height);

	cross._topleft = _map[pos.y][pos.x];
	cross._topRight = _map[pos.y][pos.x + size];
	cross._botLeft = _map[pos.y + size][pos.x];
	cross._botRight = _map[pos.y + size][pos.x + size];

	float rando = ((((float)rand() / (float)(RAND_MAX)) * _height * 2.f) - _height);
	//rando = 0;
	_map[pos.x + (size / 2)][pos.y + (size / 2)] = cross.getMiddle(rando);

	_crosses.push_back(cross);
}

void	Diamond::manageCrosses()
{
	int	crossNb = sqrt(_crosses.size());
	Vector2di	step;
	int size = _map.size() / (crossNb * 2);
	int randomAdd;
	for (int y = 0; y < crossNb; y++)
	{
		for (int x = 0; x < crossNb; x++)
		{
			randomAdd = ((((float)rand() / (float)(RAND_MAX)) * _height * 2.f) - _height);
			//randomAdd = 0;
			step.x = ((_map.size() * x) / crossNb) + size;
			step.y = ((_map.size() * y) / crossNb) + size;
			if (x == 0)
				_map[step.x - size][step.y] = _crosses[x + (y * crossNb)].leftCross() / 3 + randomAdd;
			else
				_map[step.x - size][step.y] = (_crosses[x + (y * crossNb)].leftCross() + _crosses[(x - 1) + (y * crossNb)]._middle) / 4 + randomAdd;

			if (x == crossNb - 1)
				_map[step.x + size][step.y] = _crosses[x + (y * crossNb)].RightCross() / 3 + randomAdd;
			else
				_map[step.x + size][step.y] = (_crosses[x + (y * crossNb)].RightCross() + _crosses[(x + 1) + (y * crossNb)]._middle) / 4 + randomAdd;


			if (y == 0)
				_map[step.x][step.y - size] = _crosses[x + (y * crossNb)].TopCross() / 3 + randomAdd;
			else
				_map[step.x][step.y - size] = (_crosses[x + (y * crossNb)].TopCross() + _crosses[x + ((y - 1) * crossNb)]._middle) / 4 + randomAdd;


			if (y == crossNb - 1)
				_map[step.x][step.y + size] = _crosses[x + (y * crossNb)].BotCross() / 3 + randomAdd;
			else
				_map[step.x][step.y + size] = (_crosses[x + (y * crossNb)].BotCross() + _crosses[x + ((y + 1) * crossNb)]._middle) / 4 + randomAdd;


		}
	}
	_crosses.clear();
}

void	Diamond::fillMap()
{
	int size = _map.size();
	int squareNb = 1;
	int x;
	int y;
	while (squareNb < _map.size() - 1)
	{
		for (int i = 0; i < squareNb; i++)
		{
			for (int j = 0; j < squareNb; j++)
			{
				x = (_map.size() * j) / squareNb;
				y = (_map.size() * i) / squareNb;
				square(Vector2di(x, y), size - 1);
			}
		}
		manageCrosses();
		//printMap();
		std::cout << std::endl;
		size = (size + 1) / 2;
		squareNb *= 2;
		_height /= 2.f;
	}
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
	std::vector<Vector3df>	verticesLine;
	float x = 0;
	float z = 0;
	float inc = 1;
	for (const auto &vec : _map)
	{
		x = 0;
		for (const auto &value : vec)
		{
			verticesLine.push_back(Vector3df(x * scale, (float)value * smooth - 100, z * scale));
			x += inc;
		}
		z += inc;
		_vertices.push_back(verticesLine);
		verticesLine.clear();
	}
}

void	Diamond::updateTriangles()
{
	for (int y = 0; y < _vertices.size() - 1; y++)
	{
		for (int x = 0; x < _vertices.size() - 1; x++)
		{
			_triangles.push_back(game::Triangle<float>(_vertices[y + 1][x], _vertices[y][x + 1], _vertices[y][x]));
			_triangles.push_back(game::Triangle<float>(_vertices[y + 1][x + 1], _vertices[y][x + 1], _vertices[y + 1][x]));
		}
	}
}
