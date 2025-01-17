#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "level.h"
#include "camera.h"
#include "deer.h"
#include "tree.h"

enum CameraState {
  FIRST_PERSON,
  THIRD_PERSON,
  BIRD_VIEW
};

class Game {
  public:
    bool keys[1024];
    Camera camera = Camera(glm::vec3(-1.0f, 0.0f, 13.0f));
    void init();
    void update(float dt, bool let_deer_move);
    void processInput(float dt);
    void render(float time, float speedCycle,bool enableDayNight);
  private:
    int view = 0;
    Model player;
    std::vector<Deer> deers;
    std::vector<Tree> trees;
    std::vector<Tree> scrubPines;
    Model hill;
    Model duck;
    Model eagle;
    Level level;
    Shader shader;
    void setLighting(float time, float speedValue, bool enableDayNight);
    void setUpTransformations();
    void drawPlayer();
    void checkCollision(float dt);
};

#endif