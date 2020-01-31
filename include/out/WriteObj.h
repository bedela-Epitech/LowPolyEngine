//
// Created by adrien on 27/01/20.
//

#ifndef INC_71K2LEDEB_WRITEOBJ_H
#define INC_71K2LEDEB_WRITEOBJ_H

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>

class WriteObj
{
private:
    inline static unsigned int _nbFace = 1000000;
public:
    WriteObj() = default;
    static void exportToObj(const std::vector<glm::vec3> &, const std::vector<glm::vec3> &);
};

#endif //INC_71K2LEDEB_WRITEOBJ_H
