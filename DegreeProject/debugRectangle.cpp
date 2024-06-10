#include "debugRectangle.h"

DebugRectangle::DebugRectangle() : VAO(0), VBO(0), EBO(0), color(Qt::red)
{
}

DebugRectangle::~DebugRectangle()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void DebugRectangle::init()
{
    initializeOpenGLFunctions();
    setupShaders();
    setupBuffers();
}

void DebugRectangle::setRectangle(const QRectF &rect)
{
    rectangle = rect;

    GLfloat vertices[] = {
        rect.left(),  rect.top(),    // Top-left
        rect.right(), rect.top(),    // Top-right
        rect.right(), rect.bottom(), // Bottom-right
        rect.left(),  rect.bottom()  // Bottom-left
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void DebugRectangle::setColor(const QColor &color)
{
    this->color = color;
}

void DebugRectangle::setProjectionMatrix(const QMatrix4x4 &projection)
{
    projectionMatrix = projection;
}

void DebugRectangle::setupShaders()
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;

        uniform mat4 projection;

        void main() {
            gl_Position = projection * vec4(position, 0.0, 1.0);
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 color;

        uniform vec4 debugColor;

        void main() {
            color = debugColor;
        }
    )";

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shader.link();
}

void DebugRectangle::setupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void DebugRectangle::render()
{
    shader.bind();
    shader.setUniformValue("projection", projectionMatrix);
    shader.setUniformValue("debugColor", QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF()));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader.release();
}
