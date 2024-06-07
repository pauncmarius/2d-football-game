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
    QImage image(path);
    if (!image.isNull()) {
        image = image.convertToFormat(QImage::Format_RGBA8888);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        // Check for errors
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

void Texture::release()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}