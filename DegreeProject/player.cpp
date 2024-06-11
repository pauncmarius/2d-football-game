#include "player.h"
#include <cmath>
#include <QImage>
#include <QDebug>
#include <iostream>


Player::Player() : VAO(0), VBO(0), EBO(0), widthScale(1.0f), heightScale(1.0f), currentFrame(0), frameCounter(0), currentState(Idle), velocityY(0.0f), isJumping(false)
{
    position[0] = -1.4f; // Ox
    position[1] = -0.17f; // Oy
}

Player::~Player()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Player::init(const std::map<PlayerState, std::vector<QString>> &texturePaths)
{
    initializeOpenGLFunctions();
    shader.init();
    setupShaders();
    setupBuffers();

    // Activează blending-ul pentru a elimina fundalul transparent al imaginilor
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const auto &pair : texturePaths) {
        PlayerState state = pair.first;
        const std::vector<QString> &paths = pair.second;
        numFrames[state] = paths.size();
        for (const auto& texturePath : paths) {
            auto texture = std::make_unique<Texture>();
            texture->initializeOpenGLFunctions();
            texture->load(texturePath);
            textures[state].push_back(std::move(texture));
        }
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
        uniform float alpha;

        void main() {
            vec4 texColor = texture(playerTexture, TexCoord);
            color = vec4(texColor.rgb, texColor.a * alpha);
        }
    )";

    std::cout<<"Player:"<<std::endl;

    shader.addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource); // Adaugă și compilează shader-ul vertex
    shader.addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource); // Adaugă și compilează shader-ul fragment
    shader.link(); // Leagă shader-ele la programul shader
}

void Player::setupBuffers()
{

    GLfloat vertices[] = {
        // positions   // texture Coords
        -0.5f, -1.0f,  0.0f, 1.0f, // Bottom-left
         0.5f, -1.0f,  1.0f, 1.0f, // Bottom-right
         0.5f,  1.0f,  1.0f, 0.0f, // Top-right
        -0.5f,  1.0f,  0.0f, 0.0f  // Top-left
    };

    // Indicii pentru desenarea triunghiurilor
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generează un VAO
    glGenVertexArrays(1, &VAO);
    // Generează un VBO
    glGenBuffers(1, &VBO);
    // Generează un EBO
    glGenBuffers(1, &EBO);

    // Leagă VAO-ul
    glBindVertexArray(VAO);
    // Leagă VBO-ul
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Încarcă datele vârfurilor în VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Leagă EBO-ul
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Încarcă indicii în EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifică formatul vârfurilor
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    // Activează atributul pentru primul vârf
    glEnableVertexAttribArray(0);
    // Specifică formatul vârfurilor
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    //Activează atributul pentru pal doliea vârf
    glEnableVertexAttribArray(1);

    // Dezleagă VAO-ul
    glBindVertexArray(0);
}

void Player::setProjectionMatrix(const QMatrix4x4 &projection)
{
    projectionMatrix = projection;
}

void Player::updateAnimationFrame()
{
    frameCounter++;
    // Ajustează numărul de cadre pentru a controla viteza animatiei
    if (frameCounter >= 5) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % numFrames[currentState];
    }

    // Actualizează logica săriturii
    if (isJumping) {
        position[1] += velocityY;
        velocityY -= 0.005f; // efectul gravitației

        if (velocityY < 0.0f && currentState != Kick) {
            setState(FallDown);
        }
        if (position[1] <= -0.17f) { // nivelul solului
            position[1] = -0.17f;
            isJumping = false;
            velocityY = 0.0f;
            setState(Idle);
        }
    }
}

void Player::render()
{
    shader.bind();

    shader.setUniformValue("projection", projectionMatrix);
    shader.setUniformValue("playerPosition", QVector2D(position[0], position[1]));
    shader.setUniformValue("widthScale", widthScale);
    shader.setUniformValue("heightScale", heightScale);
    textures[currentState][currentFrame]->bind();
    shader.setUniformValue("playerTexture", 0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    textures[currentState][currentFrame]->unbind();
    shader.unbind();
}

void Player::setScale(float width, float height)
{
    widthScale = width;
    heightScale = height;
}

void Player::setState(PlayerState state)
{
    if (currentState != state) {
        currentState = state;
        // Resetează cadrul la începutul noii animații
        currentFrame = 0;
    }
}

void Player::move(float dx)
{
    position[0] += dx;
}

void Player::jump()
{
    if (!isJumping) {
        isJumping = true;
        // Viteza inițială de săritură
        velocityY = 0.055f;
        setState(JumpUp);
    }
}

void Player::kick()
{
    setState(Kick);
}

void Player::setTransparency(float alpha)
{
    shader.bind();
    shader.setUniformValue("alpha", alpha);
    shader.unbind();
}

QPointF Player::getPosition() const
{
    return QPointF(position[0], position[1]);
}

void Player::setPosition(float x, float y)
{
    position[0] = x;
    position[1] = y;
}

QRectF Player::getBoundingBox() const {
    float width = widthScale * 0.3f; // Ajustează în funcție de dimensiunea sprite-ului jucătorului
    float height = heightScale * 1.5f; // Ajustează în funcție de dimensiunea sprite-ului jucătorului
    return QRectF(position[0] - width / 2, position[1] - height / 2, width, height);
}

