#include "texture.h"
#include <QImage>
#include <QOpenGLContext>
#include <QDebug>

Texture::Texture() : textureId(0)
{
}

Texture::~Texture()
{
    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
    }
}

void Texture::load(const QString &path)
{
    // Încarcă imaginea din fișier
    QImage image(path);
    if (!image.isNull()) {
        // Convertește imaginea la format RGBA
        image = image.convertToFormat(QImage::Format_RGBA8888);

        // Generează și configurează textura OpenGL
        glGenTextures(1, &textureId);
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

        // Setează parametrii de filtrare și înfășurare
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        unbind();

        // Verifică erori
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            qDebug() << "OpenGL error in Texture::load: " << err;
        }
    } else {
        qDebug() << "Failed to load image: " << path;
    }
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
