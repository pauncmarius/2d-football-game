#include "backgroundRenderer.h"
#include <iostream>

BackgroundRenderer::BackgroundRenderer() : VAO(0), VBO(0), EBO(0) {}

BackgroundRenderer::~BackgroundRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void BackgroundRenderer::init(const QString &texturePath) {
    initializeOpenGLFunctions();

    texture.initializeOpenGLFunctions();
    texture.load(texturePath);

    shader.init();
    setupShaders();
    setupBuffers();
}

void BackgroundRenderer::setupBuffers() {
    // Coordonatele vârfurilor și coordonatele texturii
    GLfloat vertices[] = {
        // positions          // texture Coords
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, // Bottom-left
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // Bottom-right
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // Top-right
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // Top-left
    };

    // Indicii pentru desenarea triunghiurilor
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generează un VAO (Vertex Array Object)
    glGenVertexArrays(1, &VAO);
    // Generează un VBO (Vertex Buffer Object)
    glGenBuffers(1, &VBO);
    // Generează un EBO (Element Buffer Object)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Specifică formatul și poziția datelor pentru atributul de vârf 1 (coordonatele texturii)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Dezleagă VAO-ul
    glBindVertexArray(0);
}

void BackgroundRenderer::setupShaders() {
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

    std::cout<<"BgRenderer:"<<std::endl;

    shader.addShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource); // Adaugă și compilează shader-ul vertex din codul sursă
    shader.addShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource); // Adaugă și compilează shader-ul fragment din codul sursă
    shader.link(); // Leagă shader-ele compilate la programul shader

}

void BackgroundRenderer::render() {
    shader.bind();
    texture.bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    texture.unbind();
    shader.unbind();
}
