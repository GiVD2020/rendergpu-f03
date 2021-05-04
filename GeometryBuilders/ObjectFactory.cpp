#include "ObjectFactory.h"

//! createObject
/*!
  \sa testMe()
  \param x coordenada x on cal colocar el centre de l'objecte en el món virtual
  \param y coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param z coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param aux paràmetre addicional per codificar el radi de l'esfera o la d del pla.
  \param v valor d'escalaque cal aplicar a l'objecte
  \param t tipus d'objecte a construir: SPHERE, PLANE, ....
*/

shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, float data, OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    switch (t) {
        case BR_OBJECT:{
            o = make_shared<Object>(300000,"://resources/models/sphere1.obj");
            shared_ptr<ScaleTG> tTG1 = make_shared<ScaleTG>(aux);
            o->aplicaTG(tTG1);

            vec3 translate_en_y(0,-aux/4,0);
            v += translate_en_y;
            shared_ptr<TranslateTG> tTG = make_shared<TranslateTG>(v);
            o->aplicaTG(tTG);
            break;
        }
        default:
            break;
    }
    return o;
}

shared_ptr<Object> ObjectFactory::createObject(QString filename ,vec3 v, OBJECT_TYPES t){
    shared_ptr<Object> o;
    switch (t) {
        case BR_OBJECT:{
            o = make_shared<Object>(300000,filename);
            shared_ptr<TranslateTG> tTG = make_shared<TranslateTG>(v);
            o->aplicaTG(tTG);
            break;
        }
        default:
            break;
    }
    return o;
}


/*shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, float data,float xmin, float xmax, float zmin,float zmax, OBJECT_TYPES t){
    shared_ptr<Object> o;
    switch (t) {
    case FITTEDPLANE:
         //o = make_shared<FittedPlane>(v,aux,xmin,xmax,zmin,zmax,data);
        break;
    default:
        break;
    }

    return NULL;
}*/


/*shared_ptr<Object> ObjectFactory::createObject(vec3 p1, vec3 p2, vec3 p3, OBJECT_TYPES t){
    shared_ptr<Object> o;
    switch (t) {
    case TRIANGLE:
        //o = make_shared<Triangle>(p1, p2, p3);
    default:
        break;
    }

    return NULL;
}*/

shared_ptr<Object> ObjectFactory::createObject(QString filename, OBJECT_TYPES t){
    shared_ptr<Object> o;
    switch (t) {
        case BR_OBJECT:
            //change the number for bigger (heavier) .obj
            o = make_shared<Object>(300000, filename);
        default:
            break;
    }
    return o;
}

/*shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, double aux2, float data, OBJECT_TYPES t){
    shared_ptr<Object> o;
    switch (t) {
    case SPHERE_LATTICE:
        //o = make_shared<SphereLattice>(v, aux, aux2, data);
        break;
    default:
        break;
    }

    return NULL;

}*/


//creamos un objeto unitario, lo escalamos con los valores al mundo virtual, lo trasladamos al punto que nos dan y luego trasladamos al virtual??
/*shared_ptr<Object> ObjectFactory::createObject(shared_ptr<ScaleTG>escalat, shared_ptr<TranslateTG>trasllat, OBJECT_TYPES t){
    shared_ptr<Object> o;
    vec3 v{0.0f,0.0f,0.0f};
    vec3 p1{1.0f,0.0f,0.0f};
    vec3 p2{0.0f,1.0f,0.0f};
    vec3 p3{0.0f,0.0f,1.0f};
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE:
        //o = make_shared<Sphere>(v, 1, 0.0f);
        break;
    case PLANE:
        break;
    case BR_OBJECT:
        break;
    case TRIANGLE:
        //o = make_shared<Triangle>(p1, p2, p3);
    case FITTEDPLANE:
        break;
    //case CILINDRE:
      //  break;
    default:
        break;
    }
    o->aplicaTG(escalat);
    o->aplicaTG(trasllat);
    return NULL;
}*/

