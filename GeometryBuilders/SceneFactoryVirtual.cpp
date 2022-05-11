#include "SceneFactoryVirtual.h"


SceneFactoryVirtual::SceneFactoryVirtual(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);
}

/*shared_ptr<Scene> SceneFactoryVirtual::createScene(QString filename) {
    auto ground = make_shared<FittedPlane>(map->getSetup()->normalPlaBase,map->getSetup()->dPlaBase,map->getSetup()->Vxmin,map->getSetup()->Vxmax,map->getSetup()->Vzmin,map->getSetup()->Vzmax,0);
    Texture * t = new Texture(map->getSetup()->textura);

    if(t->isloaded == false){
        auto mat = make_shared<Lambertian>(vec3(0.7,0.4,0.4),
                vec3(0,0,0),
                vec3(0.1,0.1,0.1),(float)10);

        ground->setMaterial(mat);


    }else{
        auto mat = make_shared<MaterialTextura>(vec3(0.7,0.4,0.4),
                vec3(0,0,0),
                vec3(0.1,0.1,0.1),(float)10);
        mat->setObjectTexture(MaterialTextura::Textures_objectes::PLANE);
        mat->setTexture(new Texture(map->getSetup()->textura));
        ground->setMaterial(mat);
    }



    shared_ptr<VirtualWorldReader> vwr = make_shared<VirtualWorldReader>(scene);
    vwr->readFile(filename, map);
    return scene;
}*/

shared_ptr<Scene> SceneFactoryVirtual::createScene(QString filename, shared_ptr<Scene> scene_already_existent) {
    scene_already_existent->objects.clear();
    shared_ptr<VirtualWorldReader> vwr = make_shared<VirtualWorldReader>(scene_already_existent);
    vwr->readFile(filename, map);
    return scene_already_existent;
}

shared_ptr<Scene> SceneFactoryVirtual::createScene() {

}

shared_ptr<Scene> SceneFactoryVirtual::createScene(QString filename) {

}

/*void SceneFactoryVirtual::OneSphere(shared_ptr<Scene> s) {
    auto sphere = make_shared<Sphere>(vec3(0, 0, -1), 0.5, 1.0);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));

    // CODI EXEMPLE PER FER ANIMACIONS

    //    shared_ptr<Animation> anim = make_shared<Animation>();
    //    anim->transf =  make_shared<Translate>(vec3(0.2));
    //    sphere->addAnimation(anim);

    s->objects.push_back(sphere);

}*/
