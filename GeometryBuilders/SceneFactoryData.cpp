#include "SceneFactoryData.h"

SceneFactoryData::SceneFactoryData(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);
}

shared_ptr<Scene> SceneFactoryData::createScene(QString filename, shared_ptr<Scene> scene_already_existent){
    scene_already_existent->objects.clear();

    auto rdr = make_shared<RealDataReader>(scene_already_existent);
    rdr->readFile(filename, map);

    shared_ptr<FittedPlane> ground = make_shared<FittedPlane>(map->getSetup()->Vxmin, map->getSetup()->Vxmax, map->getSetup()->Vzmin, map->getSetup()->Vzmax);
    ground->make();
    scene_already_existent->objects.push_back(ground);

   // scene_already_existent->setGround(ground);

    return scene_already_existent;
}

shared_ptr<Scene> SceneFactoryData::createScene(QString filename){

}

/*shared_ptr<Scene>  SceneFactoryData::createScene(QString filename) {

    auto ground = make_shared<FittedPlane>(map->getSetup()->normalPlaBase,-map->getSetup()->dPlaBase,map->getSetup()->Vxmin,map->getSetup()->Vxmax,map->getSetup()->Vzmin,map->getSetup()->Vzmax,0);
    Texture * t = new Texture(map->getSetup()->textura);

    if(t->isloaded == false){
        auto mat = make_shared<Lambertian>(vec3(0.7,0.4,0.4),
                vec3(0,0,0),
                vec3(0.1,0.1,0.1),(float)10);

        ground->setMaterial(mat);


    }else{
        auto mat = make_shared<MaterialTextura>(vec3(1,1,1),
                vec3(0,0,0),
                vec3(0,0,0),(float)10);
        mat->setObjectTexture(MaterialTextura::Textures_objectes::PLANE);
        mat->setTexture(new Texture(map->getSetup()->textura));
        ground->setMaterial(mat);
    }

    auto scene = make_shared<Scene>(ground);
    //auto scene = make_shared<Scene>();
    auto rdr = make_shared<RealDataReader>(scene);
    // TODO: Fase 1: construccio de l'escena dins de dataReader
    rdr->readFile(filename, map);
    return scene;
}*/

shared_ptr<Scene> SceneFactoryData::createScene() {
    auto scene= make_shared<Scene>();

    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui

    return scene;
}
