#include "level.h"

void Level::load() {
    cube.load("resources/models/cube.obj", "resources/textures/grass.jpg");
    lake.load("resources/models/cube.obj", "resources/textures/lake.jpg");
    wall.load("resources/models/cube.obj", "resources/textures/wall.png");
}

void Level::draw(Shader shader) {
     drawFloor(shader);
     //left and right wall
     for (int z = 16; z > -17; z--)
     {
         wall.draw(glm::vec3(30, -0.9, z), 1.0, 0, 0, 30, shader);
         wall.draw(glm::vec3(-30, -0.9, z), 1.0, 0, 0, -30, shader);
         wall.draw(glm::vec3(30, -0.9, z), 2.0, 0, 0, 30, shader);
         wall.draw(glm::vec3(-30, -0.9, z), 2.0, 0, 0, -30, shader);
     }
     //front and back wall
     for (int x = 30; x > -31; x--)
     {
         wall.draw(glm::vec3(x, -0.8, 15), 1.0, -30,0, 0, shader);
         wall.draw(glm::vec3(x, -0.8, -15), 1.0, 30,0, 0, shader);
         wall.draw(glm::vec3(x, -0.8, 16), 2.0, -30,0, 0, shader);
         wall.draw(glm::vec3(x, -0.8, -16), 2.0, 30,0, 0, shader);
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
            // lake.draw(glm::vec3(x,-1.0 ,z), 1.0, 0, 0, 0, shader);
            if(x > 40 && z > 8)
            {
                lake.draw(glm::vec3(x-33, -.9, z-18), 1.0, 0, 0, 0, shader);
            }
            // lake.draw(glm::vec3(x-4, -1.0f, z-14), 1.0, 0, shader);
        }
    }
    //render lake
    for (int x = 10; x <= 20; x++)
    {
        for (int z = 10; z >-11; z--)
        {
            lake.draw(glm::vec3(x, -1.0, z), 1.0, 0, 0, 0, shader);
        }
    }
  }