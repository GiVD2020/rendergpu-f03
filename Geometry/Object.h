#ifndef Object_H
#define Object_H

#include <QObject>
#include <vector>
#include <memory>

#include <library/Common.h>
using namespace Common;

#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <Geometry/TG.h>
#include <Geometry/Animation.h>
#include <Geometry/Cara.h>
#include <Geometry/Material.h>
#include  "math.h"

typedef vec4  point4;

// Classe que conte la representacio d'un Objecte: geometria, topologia, material i textures
class Object : public QObject, public Animable {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;
    vector<point4> normalsVertexs;
    //Vector pels vèrtexs de textura
    vector<vec2>   textVertexs;

    // Estructures per passar a la GPU
    GLuint buffer;
    GLuint vao;

    int     numPoints;
    point4 *points;
    point4 *normals;

    // Els colors s'usen en la primera execució però després son prescindibles
    point4 *colors;

    int Index; // index de control del numero de vertexs a passar a la GPU

    shared_ptr<QGLShaderProgram> program;

    //Atribut textura
    shared_ptr<QOpenGLTexture> texture;
    //QOpenGLTexture *texture;

    //vec2 de les coordenades de textura
    vec2 *textureVertexCoords;
    //Atribut material, com que és protected no fa falta setter i getter(almenys de moment)
    Material *material;




public:

    Object(const int npoints, QObject *parent = 0);
    Object(const int npoints, QString n);
    Object(const int npoints, QString n, vec3 difuse);
    Object(const int npoints, QString n, vec3 difuse, vec3 especular, vec3 ambient, float shineness);
    ~Object();

    void parseObjFile(const QString &fileName);

    void setTexture(shared_ptr<QOpenGLTexture> t);

    virtual void make();
    virtual void toGPU(shared_ptr<QGLShaderProgram> p);
    virtual void toGPUTexture(shared_ptr<QGLShaderProgram> pr);

    virtual void draw();
    virtual void drawTexture();

    Capsa3D calculCapsa3D();

    virtual void aplicaTG(shared_ptr<TG> tg);

    //TEXTURES INDIRECTES PER CAPSA
    vector<vec2> coordenades();

    //TEXTURES INDIRECTES AMB NORMALS
    vector<vec2> coordenades(vector<vec4> normalsVertexs);



private:
    virtual void initTexture();
};



#endif // Object_H
