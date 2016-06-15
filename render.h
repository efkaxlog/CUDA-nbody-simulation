#ifndef RENDER_H
#define RENDER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "simulation.h"

class Render {
    public:
        float windowWidth;
        float windowHeight;
        float renderCameraSpeed;
        int particleBufferValuesNumber;
        std::vector<float> particlesBufferData;
        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        Simulation *simulation;
        GLFWwindow *window;
        GLuint shaderProgram;
        Render(Simulation *simulation, float windowWidth,
                 float windowHeight, int particleBufferValuesNumber);
        void setWindow(GLFWwindow *window);
        void display();
        void setAttribPointers();
        void initialize();
        void updateParticlesBufferData();
        void populateParticleBufferData();
};

#endif /* RENDER_H */
