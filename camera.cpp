#include "camera.h"

Camera::Camera(vec3 origin, vec3 eye, vec3 up)
{
    speed = 10.0f;
    mouseSpeed = 0.2f;
    this->origin = origin;
    this->eye = eye;
    this->up = up;
    yaw = 0.0f;
    pitch = 0.0f;
}

void Camera::move(const int direction)
{
    switch (direction)
    {
        case CAM_RIGHT:
            origin += glm::normalize(glm::cross(eye, up)) * speed;
            break;
        case CAM_LEFT:
            origin -= glm::normalize(glm::cross(eye, up)) * speed;
            break;
        case CAM_UP:
            break;
        case CAM_DOWN:
            break;
        case CAM_FORWARD:
            origin += speed * eye;
            break;
        case CAM_BACKWARD:
            origin -= speed * eye;
            break;
    }
}

void Camera::rotate()
{
    eye = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
}

mat4 Camera::lookAt()
{
   return glm::lookAt(origin, eye+origin, up); 
}
