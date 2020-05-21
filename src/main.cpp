#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <util.h>
#include <game.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void menu(Game &game, GLFWwindow *window);

Game game;
bool show_main_menu;
// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

static float dayNightCycle = 0.0f;

int main(int argc, char *argv[]) {
  if (argc > 1 && (std::string)argv[1] == "dev") {
    Config::devMode = true;
  }

  // glfw: initialize and configure
  auto window = initialize_glfw_and_gl(Config::SCR_WIDTH, Config::SCR_HEIGHT);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  initialize_gui(window);
  
  game.init();

  // render loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    game.processInput(deltaTime);
    game.update(deltaTime);
    game.render(currentFrame, dayNightCycle);
    if (Config::devMode)
      draw_gui();
    menu(game, window);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

	clean_up(window);
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
  {
    static int counter = 0;

    ImGui::Begin("Menu"); // Create a window called "Menu!" and append into it.
    ImGui::Checkbox("Show main menu", &show_main_menu); // Edit bools storing our window open/close state
    if (ImGui::Button("Exit"))
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    ImGui::End();
  }
  if(show_main_menu)
  {
    ImGui::Begin("Main Menu");
    ImGui::SliderFloat("Day/Night cycle", &dayNightCycle, 0.0f, 1.68);
    
    ImGui::End();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}