#include "shadow.h"
#include <iostream>


Shadow::Shadow() : VAO(0), VBO(0), EBO(0) {}

Shadow::~Shadow()
{
    cleanup();
}

void Shadow::init()
{
    // Inițializează funcțiile OpenGL
    initializeOpenGLFunctions();

    // Inițializează obiectul shader
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

    shader.addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource); // Adaugă și compilează shader-ul vertex
    shader.addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource); // Adaugă și compilează shader-ul fragment
    shader.link(); // Leagă shader-ele la programul shader
}

void Shadow::setupBuffers()
{
    const int numSegments = 200;
    const float angleIncrement = (2.0f * 3.14159265359f) / numSegments;
    // Coordonatele vârfurilor
    GLfloat vertices[(numSegments + 2) * 4];
    // Indicii pentru desenarea triunghiurilor
    GLuint indices[numSegments * 3];

    // Centrul cercului
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    for (int i = 1; i <= numSegments + 1; ++i) {
        float angle = i * angleIncrement;
        // Coordonata X a vârfului
        vertices[i * 4] = cos(angle);
        // Coordonata Y a vârfului
        vertices[i * 4 + 1] = sin(angle);
    }

    for (int i = 0; i < numSegments; ++i) {
        // Centrul cercului
        indices[i * 3] = 0;
        // Primul vârf al triunghiului
        indices[i * 3 + 1] = i + 1;
        // Al doilea vârf al triunghiului
        indices[i * 3 + 2] = i + 2;
    }

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

void Shadow::render(const QMatrix4x4 &projection, float x, float y, float scale, float transparency)
{
    shader.bind();

    // Setează matricea de proiecție
    shader.setUniformValue("projection", projection);
    // Setează poziția umbrei
    shader.setUniformValue("shadowPosition", QVector2D(x, y));
    // Setează scalarea
    shader.setUniformValue("scale", scale);
    // Setează transparența umbrei
    shader.setUniformValue("transparency", transparency);

    // Leagă VAO-ul
    glBindVertexArray(VAO);
    // Desenează elementele
    glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0);
    // Dezleagă VAO-ul
    glBindVertexArray(0);

    shader.unbind();
}

void Shadow::cleanup()
{
    // Șterge VAO-ul
    glDeleteVertexArrays(1, &VAO);
    // Șterge VBO-ul
    glDeleteBuffers(1, &VBO);
    // Șterge EBO-ul
    glDeleteBuffers(1, &EBO);
}
