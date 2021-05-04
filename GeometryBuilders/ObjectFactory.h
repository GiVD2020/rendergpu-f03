#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "Geometry/Object.h"
#include "Geometry/ScaleTG.h"
#include "Geometry/TranslateTG.h"

class ObjectFactory
{
    ObjectFactory(){};

public:
    enum  OBJECT_TYPES{
        SPHERE,
        PLANE,
        TRIANGLE,
        BR_OBJECT,
        FITTEDPLANE,
        CILINDRE,
        SPHERE_LATTICE
    };

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(QString filename, OBJECT_TYPES t);

    //create object per sphere, plane
    //translate object para virtual world
    shared_ptr<Object> createObject(QString filename, vec3 v, OBJECT_TYPES t);
    shared_ptr<Object> createObject(vec3 v, double aux, float data, OBJECT_TYPES t);
    //create object per fittedPlane
    //shared_ptr<Object> createObject(vec3 v, double aux, float data,float xmin, float xmax, float zmin,float zmax,OBJECT_TYPES t);
    //create object pel triangle
    //shared_ptr<Object> createObject(vec3 p1, vec3 p2, vec3 p3, OBJECT_TYPES t);
    //create usant les matrius d'escalat i traslladat(NO FUNCIONA CORRECTAMENT)
    //shared_ptr<Object> createObject(shared_ptr<ScaleTG>escalat, shared_ptr<TranslateTG>trasllat, OBJECT_TYPES t);
    //create pel br_object
    //sphere lattice
    //shared_ptr<Object> createObject(vec3 v, double aux, double aux2, float data, OBJECT_TYPES t);


};

#endif

