#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions>
#include <QString>

class Texture : protected QOpenGLFunctions
{
public:
    Texture();
    ~Texture();

    void load(const QString &path);
    void bind();

private:
    GLuint textureId;
};

#endif // TEXTURE_H
