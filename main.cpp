#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "particle.h"
#include "physics.h"
#include "camera.h"
#include "shader.h"
#include "simulation.h"
#include "controls.h"
#include "render.h"
#include <cuda_runtime_api.h>
#include <cuda.h>
#include "nbody.h"

GLfloat deltaTime = 0.0f;   // Time between current frame and last frame
GLfloat lastFrame = 0.0f;   // Time of last frame

int main() {
    srand(time(NULL)); // seeding random
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    float windowWidth = 1280.0f;
    float windowHeight = 720.0f;

    GLFWwindow *window = glfwCreateWindow(
        windowWidth, windowHeight, "OpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_movement_callback);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int particlesNumber = 32768;

    Physics physics(10.0f, 0.01f);
    Simulation simulation(particlesNumber, &physics);
    Camera camera(glm::vec3(0.0f, 0.0f, 100.0f),
                  glm::vec3(0.0f, 0.0f, -100.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

    simulation.generateRandomParticles(100.0f, true);
    Render render(&simulation, windowWidth, windowHeight, 6, window, camera.speed);
    setupControlFields(control, window, &simulation, &camera, &render);

    glm::mat4 view = camera.lookAt();
    GLint uniView = glGetUniformLocation(render.shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 
        render.windowWidth / render.windowHeight, 0.1f, 100000.0f);
    GLint uniProj = glGetUniformLocation(render.shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    
    setupCuda(&simulation);

    
    
    //int steps = 0;
    while(!glfwWindowShouldClose(window)) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera.speed = render.renderCameraSpeed * deltaTime;
        render.display();
        view = camera.lookAt(); 
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        doMovement();
        camera.rotate();
        if(!simulation.simulationPaused) {
            cudaCalculate();
            updateData();
            simulation.updatePositions();
        //    steps++;
        }
        render.updateParticlesBufferData();
        glfwPollEvents();
        //if (steps >= 50) 
        //    break;
    }
    glfwTerminate();
    cleanupCuda();
    return 0;
}
