

#include "map/Diamond.hpp"

Diamond::Diamond(const float &height, const unsigned int &powPower, const std::vector<std::vector<float>> &noiseMap)
{
    _noiseMap = noiseMap;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());

    _height = height;
    _size = (unsigned int)pow(2, powPower) + 1;
    _map = std::vector<std::vector<float>>(_size, std::vector<float>(_size, 0.0));

    _map[0][0] = _noiseMap[0][0];//boundedRand(-height, height);
    _map[_map.size() - 1][0] = _noiseMap[_map.size() - 2][0];//boundedRand(-height, height);
    _map[0][_map.size() - 1] = _noiseMap[0][_map.size() - 2];//boundedRand(-height, height);
    _map[_map.size() - 1][_map.size() - 1] = _noiseMap[_map.size() - 2][_map.size() - 2];//boundedRand(-height, height);
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
    float inc = 0.5f / (_map.size() * _map.size());
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
    for (int x = 0; x < _noiseMap.size(); x++)
    {
        for (int z = 0; z < _noiseMap.size(); z++)
        {
            _map[x][z] += _noiseMap[x][z];
        }
    }
    _depth = maxHeight - minHeight;
    for (int x = 0; x < _noiseMap.size() - 1; x++)
    {
        for (int z = 0; z < _noiseMap.size() - 1; z++)
        {

            glm::vec3 v0(x * scale, _map[x][z + 1] * smooth - 100, (z + 1) * scale);
            glm::vec3 v1((x + 1) * scale, _map[x + 1][z] * smooth - 100, z * scale);
            glm::vec3 v2(x * scale, _map[x][z] * smooth - 100, z * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));



            v0 = glm::vec3((x + 1) * scale, _map[x + 1][z + 1] * smooth - 100, (z + 1) * scale);
            v1 = glm::vec3((x + 1) * scale, _map[x + 1][z] * smooth - 100, z * scale);
            v2 = glm::vec3(x * scale, _map[x][z + 1] * smooth - 100, (z + 1) * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

            color += inc;
        }
    }
}

float	Diamond::boundedRand(float min, float max)
{
    std::uniform_real_distribution<> dis(min, max);
    return (static_cast<float>(dis(_gen)));
}
