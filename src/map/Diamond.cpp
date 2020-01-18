

#include "map/Diamond.hpp"

Diamond::Diamond(const float &height, const unsigned int &powPower, const std::vector<std::vector<float>> &noiseMap
        , const std::vector<std::vector<float>> &northMap
        , const std::vector<std::vector<float>> &eastMap
        , const std::vector<std::vector<float>> &southMap
        , const std::vector<std::vector<float>> &westMap)
        : _northMap(northMap), _eastMap(eastMap), _southMap(southMap), _westMap(westMap)
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

    auto m = std::make_shared<Mountain>(Mountain());
    auto l = std::make_shared<Land>(Land());

    _map[0][0] = m->boundedRand();
    _map[_map.size() - 1][0] = l->boundedRand();
    _map[0][_map.size() - 1] = l->boundedRand();
    _map[_map.size() - 1][_map.size() - 1] = m->boundedRand();
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
    float rightDiamond = 0.f;
    float bottomDiamond = 0.f;
    float topDivider = 4.f;
    float leftDivider = 4.f;
    float rightDivider = 4.f;
    float bottomDivider = 4.f;


    if (y < size / 2)
    {
        if (_northMap.empty())
            topDivider--;
        else
            topDiamond = _northMap[x + size / 2][_size - (y - size / 2)];
    }
    else
        topDiamond = _map[x + size / 2][y - size / 2];


    if (x < size / 2)
    {
        if (_westMap.empty())
            leftDivider--;
        else
            leftDiamond = _westMap[_size - (x - size / 2)][y + size / 2];
    }
    else
        leftDiamond = _map[x - size / 2][y + size / 2];


    _map[x + size / 2][y] = ((_map[x][y] + _map[x + size][y] +
                              _map[x + size / 2][y + size / 2] +
                              topDiamond) / topDivider) + biome->boundedRand();

    _map[x][y + size / 2] = ((_map[x][y] + _map[x][y + size] +
                              _map[x + size / 2][y + size / 2] +
                              leftDiamond) / leftDivider) + biome->boundedRand();
    if (flag & RIGHT_END)
    {
        if (_eastMap.empty())
            rightDivider--;
        else
            rightDiamond = _eastMap[size / 2][y + size / 2];
        _map[x + size][y + size / 2] = ((_map[x + size][y + size] + _map[x + size][y] +
                                         _map[x + size / 2][y + size / 2] + rightDiamond) / rightDivider) + biome->boundedRand();
    }
    if (flag & BOTTOM_END)
    {
        if (_southMap.empty())
            bottomDivider--;
        else
            bottomDiamond = _southMap[x + size / 2][size / 2];
        _map[x + size / 2][y + size] = ((_map[x + size][y + size] + _map[x][y + size] +
                                         _map[x + size / 2][y + size / 2] + bottomDiamond) / bottomDivider) + biome->boundedRand();
    }
}

void    Diamond::fillMap()
{
    unsigned int    nbSquare = (_size - 1) / 2;
    unsigned int    squareSize = _size - 1;
    std::vector<std::vector<std::shared_ptr<Biome>>> biomes(2, std::vector<std::shared_ptr<Biome>>(2, nullptr));
    biomes[0][0] = std::make_shared<Mountain>(Mountain());
    biomes[0][1] = std::make_shared<Land>(Land());
    biomes[1][0] = std::make_shared<Land>(Land());
    biomes[1][1] = std::make_shared<Mountain>(Mountain());

    _height = 0.1;
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
            manageSquare(j % i * squareSize, j / i * squareSize,
                         squareSize, biomes[line][column]);// check if end of column + check if end of line
            manageDiamond(j % i * squareSize, j / i * squareSize, squareSize,
                          (2 * (j / i == i - 1)) + (j % i == i - 1), biomes[line][column]);
        }
        squareSize /= 2;

        for (auto &line : biomes)
            for (auto &h : line)
                h->_height /= 2.f;
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
