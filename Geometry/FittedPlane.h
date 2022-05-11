#ifndef FITTEDPLACE_H
#define FITTEDPLACE_H

#include <library/Common.h>
#include <stdlib.h>

using namespace std;

#include <Geometry/Object.h>

const int NumVertices = 6; //(6 faces)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;


class FittedPlane : public Object
{

public:
    FittedPlane(float xmin,float xmax, float zmin, float zmax);
    virtual ~FittedPlane(){}


    void make();
    void aplicaTG(mat4 m);

private:
    float xmin, xmax, zmin,zmax;

    GLdouble xorig, yorig, zorig;

    color4 vertex_colors[4]; // 8 colors RGBA associats a cada vertex
    void quad( int a, int b, int c, int d );
    void initTexture() override;


    GLuint buffer;

};
#endif // FITTEDPLACE_H
