#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>

// Clasa Texture derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class Texture : public QOpenGLFunctions_3_3_Core
{
public:
    Texture();
    ~Texture();

    void load(const QString &path); // Încarcă textura dintr-un fișier
    void bind(); // Leagă textura pentru a fi folosită în OpenGL
    void unbind(); // Dezleagă textura

private:
    GLuint textureId; // ID-ul texturii OpenGL
};

#endif // TEXTURE_H
