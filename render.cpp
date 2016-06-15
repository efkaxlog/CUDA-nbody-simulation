#include "render.h"
#include "shader.h"

const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec3 position;"
    "in vec3 color;"
    "out vec3 Color;"
    "uniform mat4 view;"
    "uniform mat4 proj;"
    "uniform mat4 ortho;"
    "void main()"
    "{"
    "   Color = color;"
    "   gl_PointSize = 100.0 / length(view * vec4(position.xyz, 1.0));"
    "   gl_Position = proj * view * vec4(position.xyz, 1.0);"
    "}";
 
const GLchar* fragmentSource =
     "#version 150 core\n"
    "in vec3 Color;"
    "out vec4 outColor;"
    "void main()"
    "{"
    "   vec2 circCoord = 2.0 * gl_PointCoord - 1.0;"
    "   if (dot(circCoord, circCoord) > 1.0) {"
    "       discard;"
    "   }"
    "   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";


Render::Render(Simulation *simulation, float windowWidth,
                 float windowHeight, int particleBufferValuesNumber) {
    this->simulation = simulation;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->particleBufferValuesNumber = particleBufferValuesNumber;
    particlesBufferData.resize(simulation->particlesNumber * particleBufferValuesNumber);
}

void Render::setWindow(GLFWwindow *window) {
    this->window = window;
}

void Render::initialize() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, particlesBufferData.size() * sizeof(float),
                    &particlesBufferData[0], GL_DYNAMIC_DRAW);
    shaderProgram = makeShaderProgram(vertexSource, fragmentSource);
    glUseProgram(shaderProgram);
}   

void Render::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_POINTS, 0, simulation->particlesNumber);
    glfwSwapBuffers(window);
} 

void Render::updateParticlesBufferData() {
    for(int i=0; i<simulation->particles.size(); i++) {
        particlesBufferData[i * particleBufferValuesNumber] = simulation->particles[i].xPos;
        particlesBufferData[i * particleBufferValuesNumber + 1] = simulation->particles[i].yPos;
        particlesBufferData[i * particleBufferValuesNumber + 2] = simulation->particles[i].zPos;
    }
    glBufferData(GL_ARRAY_BUFFER, particlesBufferData.size() * sizeof(float),
                    &particlesBufferData[0], GL_DYNAMIC_DRAW);
}

void Render::populateParticleBufferData() {
    particlesBufferData.clear();
    for (const auto &p : simulation->particles) {
        particlesBufferData.push_back(p.xPos);
        particlesBufferData.push_back(p.yPos);
        particlesBufferData.push_back(p.zPos);
        particlesBufferData.push_back(p.r);
        particlesBufferData.push_back(p.g);
        particlesBufferData.push_back(p.b);
    }
}

void Render::setAttribPointers() {
    GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(positionAttribute);
    
    GLint colourAttribute = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colourAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colourAttribute);
}
