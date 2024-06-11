#include "shader.h"
#include <QDebug>

Shader::Shader() : program(0), vertexShader(0), fragmentShader(0){}

Shader::~Shader()
{
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void Shader::init()
{
    // Inițializează funcțiile OpenGL
    initializeOpenGLFunctions();

    // Creează un program OpenGL
    program = glCreateProgram();
    if (program == 0) {
        qDebug() << "ERROR::PROGRAM_CREATION_ERROR\n Failed to create shader program.";
    }
}

void Shader::addShaderFromSourceCode(GLenum shaderType, const char *source)
{
    // Verifică dacă programul OpenGL este inițializat
    if (!program) {
        qDebug() << "ERROR::SHADER_CREATION_ERROR\n OpenGL program not initd.";
        return;
    }

    // Creează un obiect shader
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        qDebug() << "ERROR::SHADER_CREATION_ERROR\n Failed to create shader of type:" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        return;
    }

    // Atașează codul sursă la obiectul shader
    glShaderSource(shader, 1, &source, nullptr);

    // Compilează shader-ul
    glCompileShader(shader);

    // Verifică erorile de compilare
    checkCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

    // Atașează shader-ul compilat la program
    glAttachShader(program, shader);

     // Asignează shader-ul la variabila corespunzătoare
    if (shaderType == GL_VERTEX_SHADER) {
        vertexShader = shader;
    } else if (shaderType == GL_FRAGMENT_SHADER) {
        fragmentShader = shader;
    }
}

void Shader::link()
{
    // Atribuie programul shader
    glLinkProgram(program);
    checkLinkErrors(program);

    // Șterge shaderele după ce au fost legate
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

// Setează valorile uniform pentru tipul int
void Shader::setUniformValue(const char *name, int value) {
    glUniform1i(glGetUniformLocation(program, name), value);
}

// Setează valorile uniform pentru tipul float
void Shader::setUniformValue(const char *name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

// Setează valorile uniform pentru tipul QVector2D
void Shader::setUniformValue(const char *name, const QVector2D &value) {
    glUniform2fv(glGetUniformLocation(program, name), 1, reinterpret_cast<const GLfloat*>(&value));
}

// Setează valorile uniform pentru tipul QVector3D
void Shader::setUniformValue(const char *name, const QVector3D &value) {
    glUniform3fv(glGetUniformLocation(program, name), 1, reinterpret_cast<const GLfloat*>(&value));
}

// Setează valorile uniform pentru tipul QVector4D
void Shader::setUniformValue(const char *name, const QVector4D &value) {
    glUniform4fv(glGetUniformLocation(program, name), 1, reinterpret_cast<const GLfloat*>(&value));
}

// Setează valorile uniform pentru tipul QMatrix4x4
void Shader::setUniformValue(const char *name, const QMatrix4x4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, value.constData());
}
