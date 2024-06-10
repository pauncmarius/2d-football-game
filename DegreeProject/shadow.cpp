#include "shadow.h"
#include <iostream>


Shadow::Shadow() : VAO(0), VBO(0), EBO(0) {}

Shadow::~Shadow()
{
    cleanup();
}

void Shadow::init()
{
    initializeOpenGLFunctions();
    shader.init();
    setupShaders();
    setupBuffers();
}

void Shadow::setupShaders()
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;

        uniform mat4 projection;
        uniform vec2 shadowPosition;
        uniform float scale;

        void main() {
            gl_Position = projection * vec4(position * scale + shadowPosition, 0.0, 1.0);
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 color;

        uniform float transparency;

        void main() {
            color = vec4(0.0, 0.0, 0.0, transparency);
        }
    )";

    std::cout<<"Shadow:"<<std::endl;

    shader.addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource);
    shader.addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shader.link();
}

void Shadow::setupBuffers()
{
    const int numSegments = 200;
    const float angleIncrement = (2.0f * 3.14159265359f) / numSegments;
    GLfloat vertices[(numSegments + 2) * 4];
    GLuint indices[numSegments * 3];

    vertices[0] = 0.0f; // Center of the circle
    vertices[1] = 0.0f;

    for (int i = 1; i <= numSegments + 1; ++i) {
        float angle = i * angleIncrement;
        vertices[i * 4] = cos(angle);
        vertices[i * 4 + 1] = sin(angle);
    }

    for (int i = 0; i < numSegments; ++i) {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i + 2;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Shadow::render(const QMatrix4x4 &projection, float x, float y, float scale, float transparency)
{
    shader.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("shadowPosition", QVector2D(x, y));
    shader.setUniformValue("scale", scale);
    shader.setUniformValue("transparency", transparency);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader.unbind();
}

void Shadow::cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
