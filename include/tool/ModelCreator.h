//
// Created by adrien on 06/03/2021.
//

#ifndef LOWPOLYENGINE_MODELCREATOR_H
#define LOWPOLYENGINE_MODELCREATOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class ModelCreator
{
private:
public:
    ModelCreator();
    static std::vector<float> getTriangle(const std::vector<glm::vec3> &, const glm::vec3 &, const glm::vec3 &);
    static std::vector<float> getCube(const glm::vec3 &, float );

};

#endif //LOWPOLYENGINE_MODELCREATOR_H
