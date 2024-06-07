#include "glwindow.h"
#include <QOpenGLShaderProgram>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent), texture(new Texture), shaderProgram(new Shader)
{
    // Set window flags to prevent resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);
}

GLWindow::~GLWindow()
{
    delete texture;
    delete shaderProgram;
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();  // Initialize OpenGL functions

    texture->initializeOpenGLFunctions();

    // Load the texture
    texture->load("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg1.jpg");

    // Setup shaders
    shaderProgram->initialize();
    setupShaders();

    GLfloat vertices[] = {
        // Positions          // Texture Coords
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, // Bottom-left
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // Bottom-right
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // Top-right
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // Top-left
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader program
    shaderProgram->bind();

    // Bind texture
    texture->bind();

    // Render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind texture
    texture->release();

    shaderProgram->release();
}

void GLWindow::setupShaders()
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec2 texCoord;

        out vec2 TexCoord;

        void main()
        {
            gl_Position = vec4(position, 1.0);
            TexCoord = texCoord;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 color;

        uniform sampler2D ourTexture;

        void main()
        {
            color = texture(ourTexture, TexCoord);
        }
    )";

    shaderProgram->addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shaderProgram->link();
}
