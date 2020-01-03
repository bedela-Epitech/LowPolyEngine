//
// Created by adrien on 13/12/19.
//

#ifndef INC_71K2LEDEB_PERLIN_H
#define INC_71K2LEDEB_PERLIN_H

#include <cmath>
#include <cstdio>
#include <random>
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Perlin
{
public:
    std::vector<std::vector<float>>         _noiseMap;

public:
    Perlin(int);

};

inline
float quintic(const float &t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}


class PerlinNoise
{
public:
    PerlinNoise(const unsigned &seed = 2016)
    {
        std::mt19937 generator(seed);
        std::uniform_real_distribution<float> distribution;
        auto dice = std::bind(distribution, generator);
        for (unsigned i = 0; i < tableSize; ++i) {
#if 0
            // bad
            float gradientLen2;
            do {
                gradients[i] = Vec3f(2 * dice() - 1, 2 * dice() - 1, 2 * dice() - 1);
                gradientLen2 = gradients[i].length2();
            } while (gradientLen2 > 1);
            gradients[i].normalize();
#else
            // better
            float theta = acos(2 * dice() - 1);
            float phi = 2 * dice() * M_PI;

            float x = cos(phi) * sin(theta);
            float y = sin(phi) * sin(theta);
            float z = cos(theta);
            gradients[i] = glm::vec3(x, y, z);
#endif
            permutationTable[i] = i;
        }

        std::uniform_int_distribution<unsigned> distributionInt;
        auto diceInt = std::bind(distributionInt, generator);
        // create permutation table
        for (unsigned i = 0; i < tableSize; ++i)
            std::swap(permutationTable[i], permutationTable[diceInt() & tableSizeMask]);
        // extend the permutation table in the index range [256:512]
        for (unsigned i = 0; i < tableSize; ++i) {
            permutationTable[tableSize + i] = permutationTable[i];
        }
    }
    virtual ~PerlinNoise() {}

    //Improved Noise implementation (2002) This version compute the derivative of the noise function as well

    float eval(const glm::vec3 &p) const
    {
        int xi0 = ((int)std::floor(p.x)) & tableSizeMask;
        int yi0 = ((int)std::floor(p.y)) & tableSizeMask;
        int zi0 = ((int)std::floor(p.z)) & tableSizeMask;

        int xi1 = (xi0 + 1) & tableSizeMask;
        int yi1 = (yi0 + 1) & tableSizeMask;
        int zi1 = (zi0 + 1) & tableSizeMask;

        float tx = p.x - ((int)std::floor(p.x));
        float ty = p.y - ((int)std::floor(p.y));
        float tz = p.z - ((int)std::floor(p.z));

        float u = quintic(tx);
        float v = quintic(ty);
        float w = quintic(tz);

        // generate vectors going from the grid points to p
        float x0 = tx, x1 = tx - 1;
        float y0 = ty, y1 = ty - 1;
        float z0 = tz, z1 = tz - 1;

        float a = gradientDotV(hash(xi0, yi0, zi0), x0, y0, z0);
        float b = gradientDotV(hash(xi1, yi0, zi0), x1, y0, z0);
        float c = gradientDotV(hash(xi0, yi1, zi0), x0, y1, z0);
        float d = gradientDotV(hash(xi1, yi1, zi0), x1, y1, z0);
        float e = gradientDotV(hash(xi0, yi0, zi1), x0, y0, z1);
        float f = gradientDotV(hash(xi1, yi0, zi1), x1, y0, z1);
        float g = gradientDotV(hash(xi0, yi1, zi1), x0, y1, z1);
        float h = gradientDotV(hash(xi1, yi1, zi1), x1, y1, z1);

        float k0 = a;
        float k1 = (b - a);
        float k2 = (c - a);
        float k3 = (e - a);
        float k4 = (a + d - b - c);
        float k5 = (a + f - b - e);
        float k6 = (a + g - c - e);
        float k7 = (b + c + e + h - a - d - f - g);

        return k0 + k1 * u + k2 * v + k3 * w + k4 * u * v + k5 * u * w + k6 * v * w + k7 * u * v * w;
    }

private:
    /* inline */
    uint8_t hash(const int &x, const int &y, const int &z) const
    {
        return permutationTable[permutationTable[permutationTable[x] + y] + z];
    }

    //Compute dot product between vector from cell corners to P with predefined gradient directions
    //perm: a value between 0 and 255
    float x;
    float y;
    float z;//: coordinates of vector from cell corner to shaded point

    float gradientDotV(
            uint8_t perm, // a value between 0 and 255
            float x, float y, float z) const
    {
        switch (perm & 15) {
            case  0: return  x + y; // (1,1,0)
            case  1: return -x + y; // (-1,1,0)
            case  2: return  x - y; // (1,-1,0)
            case  3: return -x - y; // (-1,-1,0)
            case  4: return  x + z; // (1,0,1)
            case  5: return -x + z; // (-1,0,1)
            case  6: return  x - z; // (1,0,-1)
            case  7: return -x - z; // (-1,0,-1)
            case  8: return  y + z; // (0,1,1),
            case  9: return -y + z; // (0,-1,1),
            case 10: return  y - z; // (0,1,-1),
            case 11: return -y - z; // (0,-1,-1)
            case 12: return  y + x; // (1,1,0)
            case 13: return -x + y; // (-1,1,0)
            case 14: return -y + z; // (0,-1,1)
            case 15: return -y - z; // (0,-1,-1)
        }
    }

    static const unsigned tableSize = 256;
    static const unsigned tableSizeMask = tableSize - 1;
    glm::vec3 gradients[tableSize];
    unsigned permutationTable[tableSize * 2];
};

#endif //INC_71K2LEDEB_PERLIN_H
