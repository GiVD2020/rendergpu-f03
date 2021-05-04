#include "VirtualWorldReader.h"


VirtualWorldReader::VirtualWorldReader(shared_ptr<Scene> s)
{
    scene = s;
}

void VirtualWorldReader::readFile(QString fileName, shared_ptr<Mapping> map) {

    mapping = map;
    std::cout << fileName.toStdString()<<std::endl;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes

void VirtualWorldReader::fileLineRead (QString lineReaded) {
    QStringList fields = lineReaded.split(",");



    if (QString::compare("brobject", fields[0], Qt::CaseInsensitive) == 0)
    {
        brObjectFound(fields);
        return;
    }


     std::cerr << "Element unknown by reading objects in virtual world aqui" << std::endl;
     return;
}


void VirtualWorldReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    //  brobject, nomDelFitxer, propietats del material, textura

    if (fields.size() != 2 && fields.size() != 5) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }

    shared_ptr<Object> o;

    if(fields.size() == 2){
        o = ObjectFactory::getInstance().createObject(fields[1],ObjectFactory::OBJECT_TYPES::BR_OBJECT);
    }
    else{
        vec3 t(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble());
        o = ObjectFactory::getInstance().createObject(fields[1],t,ObjectFactory::OBJECT_TYPES::BR_OBJECT);

    }

    scene->objects.push_back(o);
    return;
}

