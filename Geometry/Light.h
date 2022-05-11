#pragma once

#include "library/Common.h"
#include <QGLShaderProgram>

#define MAX 8
using namespace Common;

// Tipus de Lights
enum LightType {Puntual, Direccional, Spot};

// Classe que representa els atributs d'una Light
// TO DO: A la fase 1 has d'incloure els atributs necessaris per codificar una llum

class Light {
    public:
        //atributos
        LightType type_;
        vec4 position_;
        vec3 iA_;
        vec3 iD_;
        vec3 iS_;
        vec3 coeficients_;

        //atributos de los opcionales
        vec4 direction_;
        float angle_;

        //métodos
        Light(LightType l);
        Light(LightType l, vec4 position, vec3 iA, vec3 iD, vec3 iS, vec3 coeficients, vec4 direction, float angle);

        vec4 getLightPosition();
        void setLightPosition(vec4 v);

        vec3 getIa() const;
        void setIa(const vec3 &value);

        vec3 getId();
        void setId(vec3 i);

        vec3 getIs() const;
        void setIs(const vec3 &value);

        vec3 getCoeficients() const;
        void setCoeficients(const vec3 &value);

        LightType getTipusLight() const;
        void setTipusLight(const LightType &value);

        vec4 getLightDirection();
        void setLightDirection(vec4 direction);

        float getLightAngle();
        void setLightAngle(float angle);

        void LightsToGPU(QGLShaderProgram *program, int i);
};

