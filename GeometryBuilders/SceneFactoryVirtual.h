#pragma once

#include "DataService/VirtualWorldReader.h"
#include "SceneFactory.h"

class SceneFactoryVirtual : public SceneFactory
{
public:
    SceneFactoryVirtual(shared_ptr<ConfigMappingReader> mapping);

    virtual shared_ptr<Scene>  createScene(QString nomFitxer);
    virtual shared_ptr<Scene>  createScene(QString nomFitxer, shared_ptr<Scene> scene_already_existent);
    virtual shared_ptr<Scene>  createScene();

private:
    void OneSphere(shared_ptr<Scene> s);
};


