#include "ball.h"
#include <cmath>
#include <memory>
#include <iostream>

Ball::Ball() : VAO(0), VBO(0), EBO(0), radius(0.05f), currentFrame(0), frameCounter(0), state(Moving) {
    position[0] = 0.0f;
    position[1] = 0.9f;
    velocity[0] = 0.0f;
    velocity[1] = 0.0f;
}

Ball::~Ball() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Ball::init(const std::vector<QString> &texturePaths) {
    initializeOpenGLFunctions();

    shader.init();
    setupShaders();
    setupBuffers();

    numFrames = texturePaths.size();
    for (const auto& texturePath : texturePaths) {
        auto texture = std::make_unique<Texture>();
        texture->initializeOpenGLFunctions();
        texture->load(texturePath);
        textures.push_back(std::move(texture));
    }
}

void Ball::setupShaders() {
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;
        layout(location = 1) in vec2 texCoord;

        out vec2 TexCoord;

        uniform mat4 projection;
        uniform vec2 ballPosition;
        uniform float ballRadius;

        void main() {
            gl_Position = projection * vec4(position * ballRadius + ballPosition, 0.0, 1.0);
            TexCoord = texCoord;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 color;

        uniform sampler2D ballTexture;
        uniform float alpha;

        void main() {
            vec4 texColor = texture(ballTexture, TexCoord);
            color = vec4(texColor.rgb, texColor.a * alpha);
        }
    )";

    std::cout<<"Ball:"<<std::endl;
    shader.addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource);
    shader.addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shader.link();
}

void Ball::setupBuffers() {
    const int numSegments = 200;
    const float angleIncrement = (2.0f * 3.14159265359f) / numSegments;
    GLfloat vertices[(numSegments + 2) * 4];
    GLuint indices[numSegments * 3];

    // Centrul cercului
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    // Coordonatele de textură ale centrului
    vertices[2] = 0.5f;
    vertices[3] = 0.5f;

    for (int i = 1; i <= numSegments + 1; ++i) {
        float angle = i * angleIncrement;
        vertices[i * 4] = cos(angle); // Coordonata X a vârfului
        vertices[i * 4 + 1] = sin(angle); // Coordonata Y a vârfului
        // Coordonatele de textură
        vertices[i * 4 + 2] = cos(angle) * 0.5f + 0.5f;
        vertices[i * 4 + 3] = sin(angle) * 0.5f + 0.5f;
    }

    for (int i = 0; i < numSegments; ++i) {
        indices[i * 3] = 0; // Centrul cercului
        indices[i * 3 + 1] = i + 1; // Primul vârf al triunghiului
        indices[i * 3 + 2] = i + 2; // Al doilea vârf al triunghiului
    }

    // Generează un VAO
    glGenVertexArrays(1, &VAO);
    // Generează un VBO
    glGenBuffers(1, &VBO);
    // Generează un EBO
    glGenBuffers(1, &EBO);

    // Leagă VAO-ul pentru a începe configurarea acestuia
    glBindVertexArray(VAO);

    // Leagă VBO-ul pentru a începe configurarea acestuia
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Încarcă datele vârfurilor în VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Leagă EBO-ul pentru a începe configurarea acestuia
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Încarcă datele indicilor în EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifică formatul și poziția datelor pentru atributul de vârf 0 (poziția)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    // Activează atributul de vârf 0
    glEnableVertexAttribArray(0);

    // Specifică formatul și poziția datelor pentru atributul de vârf 1 (coordonatele texturii)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    // Activează atributul de vârf 1
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Dezleagă VAO-ul
}

void Ball::setProjectionMatrix(const QMatrix4x4 &projection) {
    projectionMatrix = projection;
}

void Ball::updateSpawningAnimation() {
    if (state == Moving) {
        velocity[1] -= 0.192f; // Gravitație
        position[1] += velocity[1] * 0.016f;

        if (position[1] <= -0.28f) { // Nivelul solului
            position[1] = -0.28f;
            velocity[1] *= -0.7f; // simulare bouncing

            if (velocity[1] < 0.01f) {
                velocity[1] = 0.0f;
                state = Stopped;
            }
        }
    }
}


void Ball::updateAnimationFrame() {
    if (state == Moving) {
        frameCounter++;
        // Ajustează numărul de cadre pentru a controla viteza animatiei
        if (frameCounter >= 10) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % numFrames;
        }
    }
}

void Ball::render() {
    shader.bind();
    shader.setUniformValue("projection", projectionMatrix);
    shader.setUniformValue("ballPosition", QVector2D(position[0], position[1]));
    shader.setUniformValue("ballRadius", radius);
    // Leagă textura curentă
    textures[currentFrame]->bind();
    glBindVertexArray(VAO);
    // Desenează elementele (triunghiurile) folosind indicii din EBO
    glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0); // numSegments * 3
    glBindVertexArray(0);
    // Dezleagă textura curentă
    textures[currentFrame]->unbind();
    shader.unbind();
}

QPointF Ball::getPosition() const {
    return QPointF(position[0], position[1]);
}

BallState Ball::getState() const {
    return state;
}

QPointF Ball::getVelocity() const {
    return QPointF(velocity[0], velocity[1]);
}

void Ball::setVelocity(float vx, float vy) {
    velocity[0] = vx;
    velocity[1] = vy;
    state = Moving;
}

void Ball::updatePosition() {
    position[0] += velocity[0];

    velocity[0] *= 0.925f; //aplicam un efect intarziat de oprire al mingii dupa nedectetarea coliziunii(player & minge)

    //std::cout<<velocity[0]<<std::endl;

    if (fabs(velocity[0]) < 0.01f ) {
        //std::cout<<"Ball will stop"<<std::endl;
        velocity[0] = 0.0f;
        state = Stopped;
    }
}

void Ball::setTransparency(float alpha)
{
    shader.bind();
    shader.setUniformValue("alpha", alpha);
    shader.unbind();
}

void Ball::setPosition(float x, float y)
{
    position[0] = x;
    position[1] = y;
}
