#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <util.h>
#include <game.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void menu(Game &game, GLFWwindow *window);
unsigned int loadTexture(const char *path);
unsigned int loadCubemap(std::vector<std::string> faces);

Game game;
bool show_main_menu;
bool enable_day_night;
bool allow_deer_move;
// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

static float dayNightCycle = 1.2f;

int main() {
  // glfw: initialize and configure
  auto window = initialize_glfw_and_gl(Config::SCR_WIDTH, Config::SCR_HEIGHT);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  initialize_gui(window);

  Shader skyboxShader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");

  // skybox VAO
  unsigned int skyboxVAO, skyboxVBO;
  glGenVertexArrays(1, &skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glBindVertexArray(skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  std::vector<std::string> faces{
      "resources/textures/skybox/right.jpg",
      "resources/textures/skybox/left.jpg",
      "resources/textures/skybox/top.jpg",
      "resources/textures/skybox/bottom.jpg",
      "resources/textures/skybox/front.jpg",
      "resources/textures/skybox/back.jpg"};
  unsigned int cubemapTexture = loadCubemap(faces);

  skyboxShader.use();
  skyboxShader.setInt("skybox", 0);

  game.init();

  // render loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    game.processInput(deltaTime);
    game.update(deltaTime, allow_deer_move);
    game.render(currentFrame, dayNightCycle, enable_day_night);
    if (Config::devMode)
      draw_gui();
    menu(game, window);


    glm::mat4 view = game.camera.GetFirstPersonView();
    auto projection = glm::perspective(glm::radians(game.camera.Zoom), 16.f / 9.f, 0.01f, 650.f);

    // draw skybox as last
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    skyboxShader.use();
    view = glm::mat4(glm::mat3(game.camera.GetFirstPersonView())); // remove translation from the view matrix
    skyboxShader.setMat4("view", view);
    skyboxShader.setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

	clean_up(window);
  glDeleteVertexArrays(1, &skyboxVAO);
  glDeleteBuffers(1, &skyboxVAO);

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024)
    if (action == GLFW_PRESS) {
      game.keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      game.keys[key] = false;
    }
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) { game.camera.ProcessMouseMovement(xPos, yPos); }
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  game.camera.ProcessMouseScroll(yoffset);
}
void menu(Game &game, GLFWwindow *window)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

    ImGui::Begin("Main Menu");
    ImGui::SliderFloat("Speed cycle", &dayNightCycle, 0.0f, 1.68);
    ImGui::Checkbox("Enable dynamic Day/Night", &enable_day_night);
    ImGui::Checkbox("Allow deer to move", &allow_deer_move);
    if (ImGui::Button("Exit"))
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
