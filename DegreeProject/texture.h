#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>

class Texture : public QOpenGLFunctions_3_3_Core
{
public:
    Texture();
    ~Texture();

    void load(const QString &path);
    void bind();
    void unbind();

private:
    GLuint textureId;
};

#endif // TEXTURE_H
