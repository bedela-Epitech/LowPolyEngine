

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

void    Diamond::manageSquare(unsigned int x, unsigned int y, const unsigned int size)
{
    _map[x + size / 2][y + size / 2] =
            ((_map[x][y] + _map[x + size][y] +
              _map[x][y + size] + _map[x + size][y + size]) / 4.f)
            + boundedRand(-_height, _height);
}

void    Diamond::manageDiamond(unsigned int x, unsigned int y, const unsigned int size, int flag)
{
    float topDiamond = 0.f;
    float leftDiamond = 0.f;
    float topDivider = 4.f;
    float leftDivider = 4.f;

    if (y < size / 2)
        topDivider--;
    else
        topDiamond = _map[x + size / 2][y - size / 2];


    if (x < size / 2)
        leftDivider--;
    else
        leftDiamond = _map[x - size / 2][y + size / 2];


    _map[x + size / 2][y] = ((_map[x][y] + _map[x + size][y] +
                              _map[x + size / 2][y + size / 2] +
                              topDiamond) / topDivider) + boundedRand(-_height, _height);

    _map[x][y + size / 2] = ((_map[x][y] + _map[x][y + size] +
                              _map[x + size / 2][y + size / 2] +
                              leftDiamond) / leftDivider) + boundedRand(-_height, _height);
    if (flag & RIGHT_END)
    {
        _map[x + size][y + size / 2] = ((_map[x + size][y + size] + _map[x + size][y] +
                                         _map[x + size / 2][y + size / 2]) / 3.f) + boundedRand(-_height, _height);
    }
    if (flag & BOTTOM_END)
    {
        _map[x + size / 2][y + size] = ((_map[x + size][y + size] + _map[x][y + size] +
                                         _map[x + size / 2][y + size / 2]) / 3.f) + boundedRand(-_height, _height);
    }
}

void    Diamond::fillMap()
{
    unsigned int    nbSquare = (_size -1) / 2;
    unsigned int    squareSize = _size - 1;

    for (int i = 1; i <= nbSquare; i *= 2)
    {
        for (int j = 0; j < i * i; ++j)
        {
            manageSquare(j % i * squareSize, j / i * squareSize, squareSize);// check if end of column + check if end of line
            manageDiamond(j % i * squareSize, j / i * squareSize, squareSize, (2 * (j / i == i - 1)) + (j % i == i - 1));
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
    float maxHeight = 0;
    float minHeight = 0;
    for (const auto &line : _map)
    {
        for (const auto &data : line)
        {
            maxHeight = std::max(maxHeight, data);
            minHeight = std::min(minHeight, data);
        }
    }
    _depth = maxHeight - minHeight;
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

            _colors.push_back(1.f - ((maxHeight - _map[x][z + 1]) / _depth));
            _colors.push_back((maxHeight - _map[x][z + 1]) / _depth);
            _colors.push_back(0.f);
            _colors.push_back(1.f - ((maxHeight - _map[x + 1][z]) / _depth));
            _colors.push_back((maxHeight - _map[x + 1][z]) / _depth);
            _colors.push_back(0.f);
            _colors.push_back(1.f - ((maxHeight - _map[x][z]) / _depth));
            _colors.push_back((maxHeight - _map[x][z]) / _depth);
            _colors.push_back(0.f);

            _colors.push_back(1.f - ((maxHeight - _map[x + 1][z + 1]) / _depth));
            _colors.push_back((maxHeight - _map[x + 1][z + 1]) / _depth);
            _colors.push_back(0.f);
            _colors.push_back(1.f - ((maxHeight - _map[x + 1][z]) / _depth));
            _colors.push_back((maxHeight - _map[x + 1][z]) / _depth);
            _colors.push_back(0.f);
            _colors.push_back(1.f - ((maxHeight - _map[x][z + 1]) / _depth));
            _colors.push_back((maxHeight - _map[x][z + 1]) / _depth);
            _colors.push_back(0.f);
            color += inc;
        }
    }
}

float	Diamond::boundedRand(float min, float max)
{
    return (((float)rand() / (float)(RAND_MAX)) * (max - min) + min);
}
