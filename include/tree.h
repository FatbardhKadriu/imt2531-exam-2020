#pragma once
#ifndef TREE_H
#define TREE_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "model.h"

class Tree
{
private:
    int id;
    std::unique_ptr<Model> model;
    std::unique_ptr<Model> model2;
    glm::vec3 position;

public:
    Tree(int id, std::string modelPath, std::string texturePath, glm::vec3 position);
    void draw(Shader shader);
    void draw2(Shader shader);
    void setPosition(const glm::vec3 position) { this->position = position; }
    glm::vec3 getPosition() const { return this->position; }
};

#endif