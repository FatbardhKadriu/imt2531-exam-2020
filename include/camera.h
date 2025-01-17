#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <config.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific
// input methods
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, RUN, STOP_RUN };


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for
// use in OpenGL
class Camera {
 public:
  // Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  float running = false;

  // Euler Angles
  float Yaw;
  float Pitch;

  // Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  // Constructor with vectors
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH)
      : Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }

  // Constructor with scalar values
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
      : Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  // First Person
  glm::mat4 GetFirstPersonView() { return glm::lookAt(Position, Position + Front, Up); }

  // Third person view
  glm::mat4 GetThirdPersonView() {
    return glm::lookAt(glm::vec3(Position.x - Front.x, Position.y - Front.y, Position.z - Front.z + 0.3), Position + Front, Up);
  }

  // Birds eye view
  glm::mat4 Get2DView() {
    return glm::lookAt(glm::vec3(Position.x, Position.y + 10.0f, Position.z), Position, glm::vec3(0.0f, 0.0f, -1.0f));
  }

  // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined
  // ENUM (to abstract it from windowing systems)
  void ProcessKeyboard(Camera_Movement input, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (input == FORWARD) Position += Front * velocity;
    if (input == BACKWARD) Position -= Front * velocity;
    if (input == LEFT) Position -= Right * velocity;
    if (input == RIGHT) Position += Right * velocity;
    if (input == RUN && !running) {
      MovementSpeed *= 1.7;
      running = true;
    }
    if (input == STOP_RUN && running) {
      MovementSpeed /= 1.7;
      running = false;
    }
    //user stays at the ground level
    Position.y = 0.0f;
  }

  // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
  void ProcessMouseMovement(float xPos, float yPos, GLboolean constrainPitch = true) {
    // Calculate offset based on last mouse position relative to current mouse position
    float xoffset = (xPos - mouseLastX) * MouseSensitivity;
    float yoffset = (mouseLastY - yPos) * MouseSensitivity;

    // Update last position to current
    mouseLastX = xPos;
    mouseLastY = yPos;

    Yaw = glm::mod(Yaw + xoffset, 360.0f);
    ;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
      if (Pitch > 89.0f) Pitch = 89.0f;
      if (Pitch < -89.0f) Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
  }

  // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void ProcessMouseScroll(float yoffset)
  {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
      Zoom = 1.0f;
    if (Zoom > 45.0f)
      Zoom = 45.0f;
  }

 private:
  // Default mouse position values
  GLfloat mouseLastX = 400, mouseLastY = 300;

  // Calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right =
        glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the
                                                     // more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
  }
};
#endif