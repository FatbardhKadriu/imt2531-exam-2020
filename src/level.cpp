#include "level.h"

void Level::load() {
    cube.load("resources/models/cube.obj", "resources/textures/grass.jpg");
    lake.load("resources/models/cube.obj", "resources/textures/lake.jpg");
    wall.load("resources/models/cube.obj", "resources/textures/wall.png");
    hill.load("resources/models/cube.obj", "resources/textures/hill.jpg");
}

void Level::draw(Shader shader) {
     drawFloor(shader);
     //left and right wall
     for (int z = 16; z > -17; z--)
     {
         hill.draw(glm::vec3(30, 0.0, z), 1.0, 0, 0, 0, shader);
         hill.draw(glm::vec3(-30, 0.0, z), 1.0, 0, 0, 0, shader);
        //  hill.draw(glm::vec3(30, -0.9, z), 2.0, 0, 0, 30, shader);
        //  hill.draw(glm::vec3(-30, -0.9, z), 2.0, 0, 0, -30, shader);
     }
     //front and back wall
     for (int x = 30; x > -31; x--)
     {
         hill.draw(glm::vec3(x, 0.0, 15), 1.0, 0, 0, 0, shader);
         hill.draw(glm::vec3(x, 0.0, -15), 1.0, 0, 0, 0, shader);
        //  hill.draw(glm::vec3(x, -0.8, 16), 2.0, -30, 0, 0, shader);
        //  hill.draw(glm::vec3(x, -0.8, -16), 2.0, 30,0, 0, shader);
     }

}

void Level::drawFloor(Shader shader)
{
    shader.use();
    for (int x = 0; x < 61; x++)
    {
        for (int z = 0; z < 31; z++)
        {
            cube.draw(glm::vec3(x-30, -1.0, z-15), 1.0, 0, 0, 0, shader);
            if(x > 40 && z > 8)
            {
                lake.draw(glm::vec3(x-33, -.9, z-18), 1.0, 0, 0, 0, shader);
            }
        }
    }
  }