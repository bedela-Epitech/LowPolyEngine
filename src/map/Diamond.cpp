

#include "map/Diamond.hpp"

Diamond::Diamond(unsigned int size,
                 const std::vector<std::vector<float>> &northMap,
                 const std::vector<std::vector<float>> &eastMap,
                 const std::vector<std::vector<float>> &southMap,
                 const std::vector<std::vector<float>> &westMap)
        : _northMapEmpty(northMap.empty()), _eastMapEmpty(eastMap.empty()),
          _southMapEmpty(southMap.empty()), _westMapEmpty(westMap.empty())
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());

    _size = size;
    _map = std::vector<std::vector<float>>(_size, std::vector<float>(_size, 0.f));

    // init map corners
    _map[0][0] = boundedRand(-_height, _height);
    _map[_map.size() - 1][_map.size() - 1] = boundedRand(-_height, _height);
    _map[_map.size() - 1][0] = boundedRand(-_height, _height);
    _map[0][_map.size() - 1] = boundedRand(-_height, _height);

    // If this chunk is surrounded by other chunks
    // we use the neighbours to init the sides of the map
    if (!_westMapEmpty)
        for (int i = 0; i < westMap.size(); i++)
            _map[0][i] = westMap[_size - 1][i];

    if (!_eastMapEmpty)
        for (int i = 0; i < eastMap.size(); i++)
            _map[_size - 1][i] = eastMap[0][i];

    if (!_northMapEmpty)
        for (int i = 0; i < northMap.size(); i++)
            _map[i][_size - 1] = northMap[i][0];

    if (!_southMapEmpty)
        for (int i = 0; i < southMap.size(); i++)
            _map[i][0] = southMap[i][_size - 1];
}

void    Diamond::manageSquare(unsigned int x, unsigned int y, const unsigned int size, const std::shared_ptr<Biome> &biome)
{
    _map[x + size / 2][y + size / 2] =
            ((_map[x][y] + _map[x + size][y] +
              _map[x][y + size] + _map[x + size][y + size]) / 4.f)
            + biome->boundedRand();
}

void    Diamond::manageDiamond(unsigned int x, unsigned int y, const unsigned int size, int flag, const std::shared_ptr<Biome> &biome)
{
    float topDiamond = 0.f;
    float leftDiamond = 0.f;
    float topDivider = 3.f;
    float leftDivider = 3.f;

    if (_southMapEmpty || y >= size / 2)
    {
        if (y >= size / 2)
        {
            topDiamond = _map[x + size / 2][y - size / 2];
            topDivider++;
        }
        _map[x + size / 2][y] = ((_map[x][y] + _map[x + size][y] +
                                  _map[x + size / 2][y + size / 2] +
                                  topDiamond) / topDivider) + biome->boundedRand();
    }
    if (_westMapEmpty || x >= size / 2)
    {
        if (x >= size / 2)
        {
            leftDiamond = _map[x - size / 2][y + size / 2];
            leftDivider++;
        }
        _map[x][y + size / 2] = ((_map[x][y] + _map[x][y + size] +
                                  _map[x + size / 2][y + size / 2] +
                                  leftDiamond) / leftDivider) + biome->boundedRand();
    }
    if (flag & RIGHT_END && _eastMapEmpty)
    {
        _map[x + size][y + size / 2] = ((_map[x + size][y + size] + _map[x + size][y] +
                                         _map[x + size / 2][y + size / 2]) / 3.f) + biome->boundedRand();
    }
    if (flag & TOP_END && _northMapEmpty)
    {
        _map[x + size / 2][y + size] = ((_map[x + size][y + size] + _map[x][y + size] +
                                         _map[x + size / 2][y + size / 2]) / 3.f) + biome->boundedRand();
    }
}

void    Diamond::fillMap()
{
    unsigned int    nbSquare = (_size - 1) / 2;
    unsigned int    squareSize = _size - 1;
    _height = 0.1;
    _map[squareSize / 2][squareSize / 2] = _map[0][0] +
                                           _map[_map.size() - 1][_map.size() - 1] +
                                           _map[_map.size() - 1][0] +
                                           _map[0][_map.size() - 1]/* + boundedRand(-_height, _height)*/;

    std::vector<std::vector<std::shared_ptr<Biome>>> biomes(2, std::vector<std::shared_ptr<Biome>>(2, nullptr));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (getDiff(i, j, squareSize / 2) > 1.f)
                biomes[i][j] = std::make_shared<Mountain>(Mountain());
            else
                biomes[i][j] = std::make_shared<Land>(Land());
        }
    }
    for (int i = 1; i <= nbSquare; i *= 2)
    {
        int line = 0;
        int column = 1;
        for (int j = 0; j < i * i; ++j)
        {
            if (i > 1) {
                line = (j / i) / (i / 2);
                column = (j % i) / (i / 2);
                _height = biomes[line][column]->_height;
            }
            if (i != 1) {
                manageSquare(j % i * squareSize, j / i * squareSize,
                             squareSize, biomes[line][column]);// check if end of column + check if end of line
            }
            manageDiamond(j % i * squareSize, j / i * squareSize, squareSize,
                          (2 * (j / i == i - 1)) + (j % i == i - 1), biomes[line][column]);
        }
        squareSize /= 2;

        for (auto &line : biomes)
            for (auto &h : line)
                h->_height /= 2.f;
    }
}

float   Diamond::getDiff(int x, int y, unsigned int size) const
{
    float max = _map[size][size];
    float min = _map[size][size];

    for (int i = x * size; i <= x * size + size; i++)
    {
        for (int j = y * size; j <= y * size + size; j++)
        {
            max = std::max(_map[i][j], max);
            min = std::min(_map[i][j], min);
        }
    }
    std::cout << max - min << std::endl;
    return max - min;
}

float	Diamond::boundedRand(float min, float max)
{
    std::uniform_real_distribution<> dis(min, max);
    return (static_cast<float>(dis(_gen)));
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