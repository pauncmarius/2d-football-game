#include "player.h"
#include <cmath>
#include <QImage>
#include <QDebug>

Player::Player() : VAO(0), VBO(0), EBO(0), widthScale(1.0f), heightScale(1.0f), currentFrame(0), frameCounter(0)
{
    position[0] = -1.4f; // Position close to the left border
    position[1] = -0.18f; // Ground level
}

Player::~Player()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    for (auto texture : textures) {
        delete texture;
    }
}

void Player::initialize(const std::vector<QString> &texturePaths)
{
    initializeOpenGLFunctions();
    setupShaders();
    setupBuffers();

    // Enable blending to remove black bg
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    numFrames = texturePaths.size();
    for (const auto& texturePath : texturePaths) {
        QOpenGLTexture *texture = new QOpenGLTexture(QImage(texturePath).convertToFormat(QImage::Format_RGBA8888));
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);
        textures.push_back(texture);
    }
}

void Player::setupShaders()
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;
        layout(location = 1) in vec2 texCoord;

        out vec2 TexCoord;

        uniform mat4 projection;
        uniform vec2 playerPosition;
        uniform float widthScale;
        uniform float heightScale;

        void main() {
            vec2 scaledPosition = vec2(position.x * widthScale, position.y * heightScale);
            gl_Position = projection * vec4(scaledPosition + playerPosition, 0.0, 1.0);
            TexCoord = texCoord;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 color;

        uniform sampler2D playerTexture;

        void main() {
            vec4 texColor = texture(playerTexture, TexCoord);
            color = texColor;
        }
    )";

    shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shader.link();
}

void Player::setupBuffers()
{
    // Define vertices for a rectangle representing the player
    GLfloat vertices[] = {
        // Positions   // Texture Coords
        -0.5f, -1.0f,  0.0f, 1.0f, // Bottom-left
         0.5f, -1.0f,  1.0f, 1.0f, // Bottom-right
         0.5f,  1.0f,  1.0f, 0.0f, // Top-right
        -0.5f,  1.0f,  0.0f, 0.0f  // Top-left
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

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

void Player::setProjectionMatrix(const QMatrix4x4 &projection)
{
    projectionMatrix = projection;
}

void Player::updateAnimationFrame()
{
    frameCounter++;
    if (frameCounter >= 5) { // Adjust the number of frames to control the speed
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % numFrames;
    }
}

void Player::render()
{
    shader.bind();
    shader.setUniformValue("projection", projectionMatrix);
    shader.setUniformValue("playerPosition", position[0], position[1]);
    shader.setUniformValue("widthScale", widthScale);
    shader.setUniformValue("heightScale", heightScale);
    textures[currentFrame]->bind();
    shader.setUniformValue("playerTexture", 0);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Render the rectangle
    glBindVertexArray(0);
    textures[currentFrame]->release();
    shader.release();
}

void Player::setScale(float width, float height)
{
    widthScale = width;
    heightScale = height;
}
