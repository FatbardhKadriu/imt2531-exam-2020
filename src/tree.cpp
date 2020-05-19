#include <tree.h>
#include <iostream>

Tree::Tree(int id, std::string modelPath, std::string texturePath, glm::vec3 position)
    : id(id),
      position(position)
{
    model = std::unique_ptr<Model>(new Model());
    model2 = std::unique_ptr<Model>(new Model());
    model->load(modelPath, texturePath);
    model2-> load(modelPath, texturePath);
    // rotationY = 180;
}

void Tree::draw(Shader shader)
{
    shader.use();
    // shader.setGhostLight(this->position, this->color, id);
    model->draw(this->position, 0.004, -90, rotationY, 0, shader);
}
void Tree::draw2(Shader shader)
{
    model2->draw(this->position, 0.002, 0, rotationY, 0, shader);
}
