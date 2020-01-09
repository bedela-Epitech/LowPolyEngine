

#include "map/Diamond.hpp"

Diamond::Diamond(const float &height, const unsigned int &powPower, const std::vector<std::vector<float>> &noiseMap)
{
    _noiseMap = noiseMap;
    for (auto &line : _noiseMap)
    {
        line.push_back(line[line.size() - 1]);
    }
    _noiseMap.push_back(_noiseMap[_noiseMap.size() - 1]);
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());

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
    unsigned int    nbSquare = (_size - 1) / 2;
    unsigned int    squareSize = _size - 1;
    std::vector<std::vector<float>> heights = {{3.1, 0.1}, {0.1, 0.1}};
    _height = 0.1;
    for (int i = 1; i <= nbSquare; i *= 2)
    {
        int line = 0;
        int column = 0;
        for (int j = 0; j < i * i; ++j)
        {
            if (i > 1) {
                line = (j / i) / (i / 2);
                 column = (j % i) / (i / 2);
                 _height = heights[line][column];
            }
            if (_height > 1)
                std::cout << _height << " ";
            manageSquare(j % i * squareSize, j / i * squareSize,
                         squareSize);// check if end of column + check if end of line
            manageDiamond(j % i * squareSize, j / i * squareSize, squareSize,
                          (2 * (j / i == i - 1)) + (j % i == i - 1));
        }
        squareSize /= 2;
        //_height /= 2.f;
        for (auto &line : heights)
            for (auto &h : line)
                h /= 2.f;
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



float	Diamond::boundedRand(float min, float max)
{
    std::uniform_real_distribution<> dis(min, max);
    return (static_cast<float>(dis(_gen)));
}
