#include "GeometryBuilders/Builder.h"

Builder::Builder(GLWidget *glWid)
{
    glWidget = glWid;
    scene = glWidget->getScene();

}

void Builder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            //canviar quan es vulguin carregar objectes mes pesats
            auto obj = make_shared<Object>(300000, fileName);
            scene->addObject(obj);
            scene->camera->actualitzaCamera(scene->capsaMinima);
            emit newObj(obj);
    }
}

void Builder::newVirtualScene() {
    // TO DO Fase 1: creació de la nova escena Virtual a partir d'un fitxer
    // de  a partir de les dades
    // del configMapping  i un fitxer .txt de tipus VIRTUALWORLD.
    // Nomes hi hauran fitxers de tipus BoundaryObject.
    // Usa el ConfigMappingReader i la teva SceneFactoryVirtual
    // per a construir l'escena tal i com feies a la practica 1

    //LO DEJO HARDCODEADO PARA QUE NO SE HAGA PESADO CARGAR DOS FICHEROS CADA VEZ
    //QString fileName_mapping = QFileDialog::getOpenFileName();

    QString fileName_mapping = "://resources/config_files/configMapping.txt";


    shared_ptr<ConfigMappingReader> mapping_reader = make_shared<ConfigMappingReader>(fileName_mapping);

    shared_ptr<SceneFactory> scene_factory = getFactory(mapping_reader, Scene::DATA_TYPES::VIRTUALWORLD);
    QString fileName_data = QFileDialog::getOpenFileName();
    scene_factory->createScene(fileName_data, scene);
    scene->camera->actualitzaCamera(scene->capsaMinima);
    emit newScene(scene);

}


void Builder::newDataScene()
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del configMapping i el fitxer .txt que conté les dades
    // Utilitza el ConfigMappingReader i la teva SceneFactoryData per a llegir els fitxers
    // i crear l'escena corresponent.

    // Opcionalment pots crear un dialeg per posar els valors del mapping

    QString fileName_mapping = "://resources/config_files/configMappingData.txt";
    shared_ptr<ConfigMappingReader> mapping_reader = make_shared<ConfigMappingReader>(fileName_mapping);

    shared_ptr<SceneFactory> scene_factory = getFactory(mapping_reader, Scene::DATA_TYPES::REALDATA);
    QString fileName_data = QFileDialog::getOpenFileName();
    scene_factory->createScene(fileName_data, scene);
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit newScene(scene);
}


shared_ptr<SceneFactory> Builder::getFactory(shared_ptr<ConfigMappingReader> cf, Scene::DATA_TYPES expected) {

    if(cf->dataType == expected && cf->dataType == Scene::DATA_TYPES::VIRTUALWORLD)
    {
        return make_shared<SceneFactoryVirtual>(cf);
    }
    else if(cf->dataType == expected && cf->dataType == Scene::DATA_TYPES::REALDATA)
    {
        return make_shared<SceneFactoryData>(cf);
    }else{
        std::cout << "fitxer de mapping no es correspon al boto polsat";
    }

    //TO DO:  Afegir les factories de dades temporals en les animacions
    return nullptr;
}

