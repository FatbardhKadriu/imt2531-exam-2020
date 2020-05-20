#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>
#include <map>

#include "model.h"

class Level
{
public:
  void load();
  void draw(Shader shader);

private:
  Model cube;
  Model lake;
  Model wall;
  Model hill;
  void update(float dt);
  void drawFloor(Shader shader);
};

#endif