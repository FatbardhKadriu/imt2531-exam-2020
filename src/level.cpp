#include "level.h"

void Level::load() {
    cube.load("resources/models/cube.obj", "resources/textures/grass.jpg");
    lake.load("resources/models/cube.obj", "resources/textures/lake.jpg");
    wall.load("resources/models/cube.obj", "resources/textures/wall.png");
}

void Level::draw(Shader shader) {
        drawFloor(shader);
}

void Level::drawFloor(Shader shader)
{
    shader.use();
    for (int x = 0; x < 61; x++)
    {
        for (int z = 0; z < 31; z++)
        {
            cube.draw(glm::vec3(x-30, -1.0, z-15), 1.0, 0, shader);
            // lake.draw(glm::vec3(x-4, -1.0f, z-14), 1.0, 0, shader);
        }
    }
    //left and right wall
    for(int z = 16; z > -17; z-- )
    {
        wall.draw3(glm::vec3(30, -0.8, z), 1.0, -30, shader);
        wall.draw3(glm::vec3(-30, -0.8, z), 1.0, 30, shader);
        wall.draw3(glm::vec3(30, -0.8, z), 2.0, -30, shader);
        wall.draw3(glm::vec3(-30, -0.8, z), 2.0, 30, shader);
    }
    //front and back wall
    for(int x = 30; x > -31; x--)
    {
        wall.draw2(glm::vec3(x, -0.8, 15), 1.0, -30, shader);
        wall.draw2(glm::vec3(x, -0.8, -15), 1.0, 30, shader);
        wall.draw2(glm::vec3(x, -0.8, 16), 2.0, -30, shader);
        wall.draw2(glm::vec3(x, -0.8, -16), 2.0, 30, shader);
    }
}