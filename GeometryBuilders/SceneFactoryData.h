#pragma once


#include "DataService/RealDataReader.h"
#include "SceneFactory.h"

class SceneFactoryData : public SceneFactory
{
public:
    SceneFactoryData(shared_ptr<ConfigMappingReader> mapping);
    virtual shared_ptr<Scene>  createScene(QString nomFitxer);
    virtual shared_ptr<Scene>  createScene(QString nomFitxer, shared_ptr<Scene> scene_already_existent);
    virtual shared_ptr<Scene>  createScene();
};


