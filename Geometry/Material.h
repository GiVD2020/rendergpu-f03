#pragma once

#include <QGLShaderProgram>
#include "library/Common.h"
#include <memory>

using namespace std;
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    Material(vec3 d);
    Material(vec3 d, vec3 s, vec3 a, float beta);
    void toGPU(shared_ptr<QGLShaderProgram> program);
    vec3 diffuse,especular,ambient;
    float shineness;
};

