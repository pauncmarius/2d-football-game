#include "shader.h"
#include <QDebug>

Shader::Shader()
{
    program = 0;
    vertexShader = 0;
    fragmentShader = 0;
}

Shader::~Shader()
{
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void Shader::initialize()
{
    // Initialize OpenGL functions here
    initializeOpenGLFunctions();
    program = glCreateProgram();
    if (program == 0) {
        qDebug() << "ERROR::PROGRAM_CREATION_ERROR\n Failed to create shader program.";
    }
}

void Shader::addShaderFromSourceCode(GLenum shaderType, const char *source)
{
    // Check if the OpenGL context is initialized
    if (!program) {
        qDebug() << "ERROR::SHADER_CREATION_ERROR\n OpenGL program not initialized.";
        return;
    }

    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        qDebug() << "ERROR::SHADER_CREATION_ERROR\n Failed to create shader of type:" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        return;
    }

    // Attach source code to shader object
    glShaderSource(shader, 1, &source, nullptr);

    // Compile the shader
    glCompileShader(shader);

    // Check for compile errors
    checkCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

    // Attach the compiled shader to the program
    glAttachShader(program, shader);

    // Assign the shader to the correct member variable
    if (shaderType == GL_VERTEX_SHADER) {
        vertexShader = shader;
    } else if (shaderType == GL_FRAGMENT_SHADER) {
        fragmentShader = shader;
    }
}


void Shader::link()
{

    glLinkProgram(program);
    checkLinkErrors(program);

    if (vertexShader != 0) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
    if (fragmentShader != 0) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::checkCompileErrors(GLuint shader, const QString &type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        qDebug() << "ERROR::SHADER_COMPILATION_ERROR of type:" << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
    } else {
        qDebug() << "SUCCESS::SHADER_COMPILATION_SUCCESS of type:" << type;
    }
}

void Shader::checkLinkErrors(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        qDebug() << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- ";
    } else {
        qDebug() << "SUCCESS::PROGRAM_LINKING_SUCCESS";
    }
}
