#include "level.h"

void Level::load() {
    cube.load("resources/models/cube.obj", "resources/textures/wall.png");
}

void Level::draw(Shader shader) {
        drawFloor(shader);
}

void Level::drawFloor(Shader shader)
{
    shader.use();
    for (int x = 0; x < 60; x++)
    {
        for (int z = 0; z < 40; z++)
        {
            cube.draw(glm::vec3(x - 15, -1.0, z - 14), 1.0, 0, shader);
        }
    }
}