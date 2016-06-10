#include "controls.h"
#include <iostream>
//Controls::Controls(GLFWwindow *window, Simulation *simulation, Camera *camera, Render *render) {
//    this->window = window;
//    this->simulation = simulation;
//    this->camera = camera;
//    this->render = render;
//}

Control control;

void setupControlFields(Control &control, GLFWwindow *window, Simulation *simulation,
                         Camera *camera, Render *render) {
    control.window = window;
    control.simulation = simulation;
    control.camera = camera;
    control.render = render;
}

void doMovement() {
    if(control.keys[GLFW_KEY_W]) 
        control.camera->move(CAM_FORWARD);
    if(control.keys[GLFW_KEY_S])
        control.camera->move(CAM_BACKWARD);
    if(control.keys[GLFW_KEY_A])
        control.camera->move(CAM_LEFT);
    if(control.keys[GLFW_KEY_D])
        control.camera->move(CAM_RIGHT);
}

void printParticlePos(Particle *particle) {
    std::cout<<"---------------\n";
    std::cout<<particle->xPos<<"\n";
    std::cout<<particle->yPos<<"\n";
    std::cout<<particle->zPos<<"\n";
    
    std::cout<<"\n";
}

void handleKeyPresses(int key) {
    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(control.window, GL_TRUE);
            break;
        case GLFW_KEY_P:
            printParticlePos(&control.simulation->particles.at(0));
            printParticlePos(&control.simulation->particles.at(control.simulation->particles.size() / 2));
            printParticlePos(&control.simulation->particles.at(1));
            break;
        case GLFW_KEY_G:
            control.simulation->physics->G += control.simulation->physics->G / 10;
            break;
        case GLFW_KEY_RIGHT:
            control.simulation->calculateForces();
            control.render->updateParticlesBufferData();
            break;
        case GLFW_KEY_SPACE:
            control.simulation->togglePause();
            break;
        case GLFW_KEY_LEFT_SHIFT:
            control.render->renderCameraSpeed /= 10.0f;
            break;
        case GLFW_KEY_KP_ADD:
            control.render->renderCameraSpeed *= 10.0f;
            break;
    }
}

void handleKeyReleases(int key) {
    switch (key) {
        case GLFW_KEY_LEFT_SHIFT:
            control.render->renderCameraSpeed *= 10.0f;
            break;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        control.keys[key] = true;
        handleKeyPresses(key);
    }
    if (action == GLFW_RELEASE) {
        control.keys[key] = false;
        handleKeyReleases(key);
    }
}

void mouse_movement_callback(GLFWwindow* window, double xpos, double ypos) {
    if(!control.camera->cameraRotationEnabled)
        return;

    if(control.firstMouse) {
        control.lastX = xpos;
        control.lastY = ypos;
        control.firstMouse = false;
    }
    
    GLfloat xoffset = xpos - control.lastX;
    GLfloat yoffset = control.lastY - ypos;
    xoffset *= control.camera->mouseSpeed;
    yoffset *= control.camera->mouseSpeed;
    control.lastX = xpos;
    control.lastY = ypos;

    control.camera->yaw += xoffset;
    control.camera->pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (control.camera->pitch > 89.0f)
        control.camera->pitch = 89.0f;
    if (control.camera->pitch < -89.0f)
        control.camera->pitch = -89.0f;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        control.camera->cameraRotationEnabled = true;
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        control.camera->cameraRotationEnabled = false;
        control.firstMouse = true;
    }
}
