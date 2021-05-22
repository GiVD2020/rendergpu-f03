#include "Geometry/Scene.h"

/**
 * @brief Scene::Scene
 */
Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
    lightAmbientGlobal = vec3(0.3, 0.3, 0.3);


}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    objects.clear();
    lights.clear();
}

/**
 * @brief Scene::addObject
 * @param obj
 */
void Scene::addObject(shared_ptr<Object> obj) {
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief Scene::toGPU
 */
void Scene::toGPU(shared_ptr<QGLShaderProgram> p) {
    setAmbientToGPU(p);
    lightsToGPU(p);
    for(int i=0; i < objects.size(); i++){
        objects.at(i)->toGPU(p);
    }

}

/**
 * @brief Scene::draw
 */
void Scene::draw() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->draw();
    }
}

/**
 * @brief Scene::drawTexture
 */
void Scene::drawTexture() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->drawTexture();
    }
}

/**
 * @brief Scene::getLightActual
 * @return
 */
shared_ptr<Light> Scene::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief Scene::setLightActual
 * @param l
 */
void Scene::setLightActual(shared_ptr<Light> l){
    lights[lights.size()-1]=l;
}



/**
 * @brief Scene::lightsToGPU
 * @param program
 */
void Scene::lightsToGPU(shared_ptr<QGLShaderProgram> program){
    // TO DO: A implementar a la fase 1 de la practica 2
        for(int i=0; i < lights.size(); i++){
            lights.at(i)->LightsToGPU(program.get(), i);
        }
        qDebug() << "Num Lights" << this -> lights.size();
        GLuint numl;
        numl = program->uniformLocation(QString("numl"));
        glUniform1i(numl, this->lights.size());
    }

void Scene::addLight(shared_ptr<Light> l) {
    lights.push_back(l);

}

/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void Scene::setAmbientToGPU(shared_ptr<QGLShaderProgram> program){
    // TO DO: A implementar a la fase 1 de la practica 2
    vec3 lightAmbient;
    lightAmbient = program->uniformLocation(QString("lightAmbientGlobal[%1]. lightAmbientGlobal"));
    //glUniform3fv(lightAmbientGlobal,1,lightAmbientGlobal);
}


void Scene::setGround(shared_ptr<FittedPlane> g){
    theres_ground = true;
    this->ground = g;

}


void Scene::unSetGround(){
    theres_ground = false;
}

/**
 * @brief Scene::setCamera
 * @param Camera *
 */
void Scene::setCamera(shared_ptr<Camera> c) {
    camera = c;
}
/**
 * @brief Scene::calculCapsaMinCont3DEscena
 */

void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (objects.size()==1) {
        capsaMinima = objects[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<objects.size(); i++) {
       c = objects[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_pointer_cast<Animable>(objects[i]) ) objects[i]->update(nframe);
    }
}
