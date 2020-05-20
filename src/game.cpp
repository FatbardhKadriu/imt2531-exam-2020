#include "game.h"

void Game::init() {
  shader = Shader("../resources/shaders/vertex.vert", "../resources/shaders/fragment.frag");
  duck.load("resources/models/duck.obj", "resources/textures/duck.jpg");

  level.load();
  player.load("resources/models/duck.obj", "resources/textures/duck.jpg");
  for (int i = 0; i < 4; i++)
  {
    deers.push_back(Deer(i, "resources/models/deer.obj", "resources/textures/doe-body.png",
                         glm::vec3(sin(i)*(-15.0f), -0.5f, cos(i) * (10.0f))));
  }
  for(int i = 0; i < 20; i+=8)
  {

      trees.push_back(Tree(i, "resources/models/tree.obj", "resources/textures/tree.jpg",
                           glm::vec3(10 + i, -.5f, -9)));
    }
   for(float i = 1.3; i < 20; i += 8)
   {
     scrubPines.push_back(Tree(i, "resources/models/scrubPine.obj", "resources/textures/LushPine.png",
                               glm::vec3(10 + i, -.5f, -10)));
   }     
  for(int i = 3; i < 20; i+=8)
  {
    trees.push_back(Tree(i, "resources/models/tree.obj", "resources/textures/tree.jpg",
                         glm::vec3(29, -.5f, -8 + i)));
  }
  for (float i = 4.5; i < 25; i += 8)
  {
    scrubPines.push_back(Tree(i, "resources/models/scrubPine.obj", "resources/textures/LushPine.png",
                              glm::vec3(28, -.5f, -8 + i)));
  }
}

void Game::update(float dt) {
  checkCollision(dt);
}

void Game::processInput(float dt) {
  if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, dt);
  if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, dt);
  if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, dt);
  if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, dt);
  if (keys[GLFW_KEY_T]) view = (view + 1) % 3;
  if (keys[GLFW_KEY_LEFT_SHIFT]) {
    camera.ProcessKeyboard(RUN, dt);
  } else {
    camera.ProcessKeyboard(STOP_RUN, dt);
  }
}

void Game::render() {
  shader.reset();
  setLighting();
  setUpTransformations();
  for(auto &deer: deers){
    deer.draw(shader);
  }
  for(auto &tree: trees){
    tree.draw(shader);
  }
  for(auto &scrubPine: scrubPines){
    scrubPine.draw2(shader);
  }
  level.draw(shader);
  duck.draw(glm::vec3(10, -0.55f, 7), 0.008, 90, 180, 0, shader);

  drawPlayer();
}

void Game::checkCollision(float dt)
{
  //collision for deer
  for (auto &deer : deers)
  {
    if (deer.getPosition().z)
    {
      if (glm::distance(camera.Position, glm::vec3(deer.getPosition().x, 0.0f, deer.getPosition().z)) <= 0.8)
      {
        if (keys[GLFW_KEY_W])
          camera.ProcessKeyboard(BACKWARD, dt);
        if (keys[GLFW_KEY_S])
          camera.ProcessKeyboard(FORWARD, dt);
        if (keys[GLFW_KEY_A])
          camera.ProcessKeyboard(RIGHT, dt);
        if (keys[GLFW_KEY_D])
          camera.ProcessKeyboard(LEFT, dt);
      }
    }
  }
  //collision for tree
  for (auto &tree : trees)
  {
    if (tree.getPosition().z)
    {
      if (glm::distance(camera.Position, glm::vec3(tree.getPosition().x, 0.0f, tree.getPosition().z)) <= 1.8)
      {
        if (keys[GLFW_KEY_W])
          camera.ProcessKeyboard(BACKWARD, dt);
        if (keys[GLFW_KEY_S])
          camera.ProcessKeyboard(FORWARD, dt);
        if (keys[GLFW_KEY_A])
          camera.ProcessKeyboard(RIGHT, dt);
        if (keys[GLFW_KEY_D])
          camera.ProcessKeyboard(LEFT, dt);
      }
    }
  }
  //collision for other type of tree
  for (auto &scrubPine : scrubPines)
    {
      if (scrubPine.getPosition().z)
      {
        if (glm::distance(camera.Position, glm::vec3(scrubPine.getPosition().x, 0.0f, scrubPine.getPosition().z)) <= 0.8)
        {
          if (keys[GLFW_KEY_W])
            camera.ProcessKeyboard(BACKWARD, dt);
          if (keys[GLFW_KEY_S])
            camera.ProcessKeyboard(FORWARD, dt);
          if (keys[GLFW_KEY_A])
            camera.ProcessKeyboard(RIGHT, dt);
          if (keys[GLFW_KEY_D])
            camera.ProcessKeyboard(LEFT, dt);
        }
      }
    }

    //collision for hill
    for(int x = -30; x < 31; x++)
    {
      if((glm::distance(camera.Position, glm::vec3(x, 0.0f, 15.0f)) <= 0.5) || (glm::distance(camera.Position, glm::vec3(x, 0.0f, -15.0f)) <= 0.6))
      {
        if (keys[GLFW_KEY_W])
          camera.ProcessKeyboard(BACKWARD, dt);
        if (keys[GLFW_KEY_S])
          camera.ProcessKeyboard(FORWARD, dt);
        if (keys[GLFW_KEY_A])
          camera.ProcessKeyboard(RIGHT, dt);
        if (keys[GLFW_KEY_D])
          camera.ProcessKeyboard(LEFT, dt);
      }
    }
    //collision for hill
    for (int z = -15; z < 16; z++)
    {
      if ((glm::distance(camera.Position, glm::vec3(30.0f, 0.0f, z)) <= 1.3) || (glm::distance(camera.Position, glm::vec3(-30.0f, 0.0f, z)) <= 1.3f))
      {
        if (keys[GLFW_KEY_W])
          camera.ProcessKeyboard(BACKWARD, dt);
        if (keys[GLFW_KEY_S])
          camera.ProcessKeyboard(FORWARD, dt);
        if (keys[GLFW_KEY_A])
          camera.ProcessKeyboard(RIGHT, dt);
        if (keys[GLFW_KEY_D])
          camera.ProcessKeyboard(LEFT, dt);
      }
    }

    //collision for lake
    for (int x = 0; x < 61; x++)
    {
      for (int z = 0; z < 31; z++)
      {
        if(x > 40 && z > 8){
        if((glm::distance(camera.Position, glm::vec3(x-33, 0.1f, z-18)) <= 0.7))
          {
            if (keys[GLFW_KEY_W])
              camera.ProcessKeyboard(BACKWARD, dt);
            if (keys[GLFW_KEY_S])
              camera.ProcessKeyboard(FORWARD, dt);
            if (keys[GLFW_KEY_A])
              camera.ProcessKeyboard(RIGHT, dt);
            if (keys[GLFW_KEY_D])
              camera.ProcessKeyboard(LEFT, dt);
          }
        }
      }
    }
  }
void Game::setUpTransformations() {
  auto projection = glm::perspective(glm::radians(camera.Zoom), 16.f / 9.f, 0.01f, 650.f);
  auto lookAt = glm::mat4(1.0f);

  switch (view) {
    case FIRST_PERSON:
      lookAt = camera.GetFirstPersonView();
      break;
    case THIRD_PERSON:
      lookAt = camera.GetThirdPersonView();
      break;
    case BIRD_VIEW:
      lookAt = camera.Get2DView();
      break;
  }

  shader.setMat4("view", lookAt);
  shader.setMat4("projection", projection);
}

void Game::setLighting() {
  shader.setDirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.5f));
}

void Game::drawPlayer() {
  if (view != FIRST_PERSON) {
    player.draw(glm::vec3(camera.Position.x , camera.Position.y-0.3, camera.Position.z), 0.008, 90, 180, 0, shader);
  }
}