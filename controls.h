#ifndef CONTROLS_H
#define CONTROLS_H
#include "simulation.h"
#include "camera.h"
#include "render.h"
#include <GLFW/glfw3.h>


struct Control {
    GLFWwindow *window;
    Simulation *simulation;
    Camera *camera;
    Render *render;
    bool firstMouse = true;
    bool keys[1024];
    float lastX, lastY;
};

extern Control control;

//class Controls {
//    public:
//        Simulation *simulation;
//        Camera *camera;
//        GLFWwindow *window;
//        Render *render;
//        Controls(GLFWwindow *window, Simulation *simulation, Camera *camera, Render *render);
void setupControlFields(Control &control, GLFWwindow *window, Simulation *simulation,
                         Camera *camera, Render *render);
void doMovement();
void handleKeyPresses(int key);
void handleKeyReleases(int key);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_movement_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
//    private:
//        bool firstMouse = true;
//        bool keys[1024];
//        float lastX, lastY;
//};


#endif /* CONTROLS_H */
