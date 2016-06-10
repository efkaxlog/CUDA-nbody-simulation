#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

const int CAM_RIGHT = 1;
const int CAM_LEFT = 2;
const int CAM_UP = 3;
const int CAM_DOWN = 4;
const int CAM_FORWARD = 5;
const int CAM_BACKWARD = 6;

class Camera {
    public:
        vec3 origin;
        vec3 eye;
        vec3 up;
        float mouseSpeed;
        float speed;
        float pitch, yaw;
        bool cameraRotationEnabled = false;
        Camera(glm::vec3 origin, glm::vec3 eye, glm::vec3 up);
        void move(const int direction);
        void rotate();
        mat4 lookAt();


};

#endif /* CAMERA_H */
