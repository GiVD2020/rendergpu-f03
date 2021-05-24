#include "Geometry/Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    // TO DO: A canviar a la fase 1 de la practica 2
    type_=t;

    iD_=vec3(0.8,0.8,0.8);

    iS_=vec3(1,1,1);

    iA_=vec3(0.2,0.2,0.2);

    coeficients_=vec3(0,0,1);

    position_ = vec4(10,10,20,0);

    angle_ = 15.0;

    direction_ = vec4(1.0,1.0,1.0,1.0);
}

Light::Light(LightType t, vec4 position, vec3 iA, vec3 iD, vec3 iS, vec3 coeficients, vec4 direction, float angle) {
    // TO DO: A canviar a la fase 1 de la practica 2
    setLightPosition(position);
    setIa(iA);
    setId(iD);
    setIs(iS);
    setCoeficients(coeficients);
    setTipusLight(t);

    //opcionales
    setLightDirection(direction);
    setLightAngle(angle);
}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   return iD_;
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    // TO DO: A canviar a la fase 1 de la practica 2
    iD_ = i;

}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return position_;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    // TO DO: A canviar a la fase 1 de la practica 2
    position_ = v;
}


/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return iA_;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    iA_ = value;

}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return iS_;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    iS_ = value;
}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return coeficients_;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    coeficients_ = value;
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    return type_;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    type_ = value;
}

vec4 Light::getLightDirection() {
    return direction_;
}

void Light::setLightDirection(vec4 direction) {
    direction_ = direction;
}

float Light::getLightAngle() {
    return angle_;
}

void Light::setLightAngle(float angle) {
    angle_ = angle;
}

void Light::LightsToGPU(QGLShaderProgram *program, int i) {
    //declaramos un vector de identificadores
        struct lights_Id
        {
            GLuint position;
            GLuint iA;
            GLuint iD;
            GLuint iS;
            GLuint coeficients;
            GLuint type;
            GLuint direction;
            GLuint angle;
        };
        lights_Id lights_IdVect[MAX];

        //obtenemos los identificadores de la GPU
        lights_IdVect[i].position=program->uniformLocation(QString("lights[%1].position_g").arg( i ));
        lights_IdVect[i].iA=program->uniformLocation(QString("lights[%1].iA_g").arg( i ));
        lights_IdVect[i].iD=program->uniformLocation(QString("lights[%1].iD_g").arg( i ));
        lights_IdVect[i].iS=program->uniformLocation(QString("lights[%1].iS_g").arg( i ));
        lights_IdVect[i].coeficients=program->uniformLocation(QString("lights[%1].coeficients_g").arg( i ));
        lights_IdVect[i].type=program->uniformLocation(QString("lights[%1].type_g").arg( i ));
        lights_IdVect[i].direction=program->uniformLocation(QString("lights[%1].direction_g").arg( i ));
        lights_IdVect[i].angle=program->uniformLocation(QString("lights[%1].angle_g").arg( i ));

        //Bind de las zonas de memoria que correspondan

        glUniform1i(lights_IdVect[i].type,type_);
        glUniform4fv(lights_IdVect[i].position,1,position_);
        glUniform3fv(lights_IdVect[i].iA,1,iA_);
        glUniform3fv(lights_IdVect[i].iD,1,iD_);
        glUniform3fv(lights_IdVect[i].iS,1,iS_);
        glUniform3fv(lights_IdVect[i].coeficients,1,coeficients_);
        glUniform4fv(lights_IdVect[i].direction,1,direction_);
        glUniform1f(lights_IdVect[i].angle,angle_);
        qDebug() << "Angle" << this -> angle_;
}
