//
// Created by adrien on 06/03/2021.
//

#include "tool/ModelCreator.h"

ModelCreator::ModelCreator()
{


}

std::vector<float> ModelCreator::getTriangle(const std::vector<glm::vec3> &triPos, const glm::vec3 &normal, const glm::vec3 &color)
 {
     std::vector<float> triangle;

     for (const auto &pos : triPos)
     {
         triangle.push_back(pos.x);
         triangle.push_back(pos.y);
         triangle.push_back(pos.z);

         triangle.push_back(normal.x);
         triangle.push_back(normal.y);
         triangle.push_back(normal.z);

         triangle.push_back(color.x);
         triangle.push_back(color.y);
         triangle.push_back(color.z);
     }

     return triangle;
 }

std::vector<float> ModelCreator::getCube(const glm::vec3 &pos, float size)
 {
     std::vector<float> cube;
     auto a = getTriangle({pos + glm::vec3(size, -size, -size), pos + glm::vec3(-size, -size, -size), pos + glm::vec3(size, size, -size)} , glm::vec3(0.f, 0.f, -1.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(size, size, -size), pos + glm::vec3(-size, -size, -size), pos + glm::vec3(-size, size, -size)} , glm::vec3(0.f, 0.f, -1.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());

     a = getTriangle({pos + glm::vec3(size, -size, size), pos + glm::vec3(-size, -size, size), pos + glm::vec3(size, size, size)} , glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(size, size, size), pos + glm::vec3(-size, -size, size), pos + glm::vec3(-size, size, size)} , glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());


     a = getTriangle({pos + glm::vec3(-size, -size, -size), pos + glm::vec3(-size, size, -size), pos + glm::vec3(-size, -size, size)} , glm::vec3(-1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(-size, size, -size), pos + glm::vec3(-size, size, size), pos + glm::vec3(-size, -size, size)} , glm::vec3(-1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());

     a = getTriangle({pos + glm::vec3(size, -size, -size), pos + glm::vec3(size, size, -size), pos + glm::vec3(size, -size, size)} , glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(size, size, -size), pos + glm::vec3(size, size, size), pos + glm::vec3(size, -size, size)} , glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());


     a = getTriangle({pos + glm::vec3(-size, size, -size), pos + glm::vec3(-size, size, size), pos + glm::vec3(size, size, size)} , glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(-size, size, -size), pos + glm::vec3(size, size, -size), pos + glm::vec3(size, size, size)} , glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());

     a = getTriangle({pos + glm::vec3(-size, -size, -size), pos + glm::vec3(-size, -size, size), pos + glm::vec3(size, -size, size)} , glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     a = getTriangle({pos + glm::vec3(-size, -size, -size), pos + glm::vec3(size, -size, -size), pos + glm::vec3(size, -size, size)} , glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
     cube.insert(cube.end(), a.begin(), a.end());
     return cube;
 }