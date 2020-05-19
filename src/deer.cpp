#include<deer.h>
#include<iostream>

Deer::Deer(int id, std::string modelPath, std::string texturePath, glm::vec3 position)
    : id(id),
      position(position),
      front(glm::vec3(-1.0f, 0.0f, 0.0f))
{
    model = std::unique_ptr<Model>(new Model());
    model->load(modelPath, texturePath);
    rotationY = 180;
}

void Deer::draw(Shader shader)
{
    shader.use();
    // shader.setGhostLight(this->position, this->color, id);
    model->draw(this->position, 0.15, 0, rotationY, 0, shader);
}
