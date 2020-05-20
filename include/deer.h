#pragma once
#ifndef DEER_H
#define DEER_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "model.h"

class Deer{
private:
    int id;
    std::unique_ptr<Model> model;
    glm::vec3 position;
    glm::vec3 nextPosition;
    glm::vec3 direction;
    glm::vec3 front;
    glm::vec3 crossProduct;
    // glm::vec3 color;
    int rotationY = 0;
    float speed = 0.1;
    float dotProduct;
    void rotate();

public:
    float deltaTime = 0;
    // float searchTime;
    // std::vector<std::pair<int, int>> path;
    Deer(int id, std::string modelPath, std::string texturePath, glm::vec3 position);
    void draw(Shader shader);
    void update(float dt);

    void setPosition(const glm::vec3 position) { this->position = position; }

    glm::vec3 getPosition() const { return this->position; }
};

#endif