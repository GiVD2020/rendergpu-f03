#pragma once

#include <string.h>

#include "DataService/ConfigMappingReader.h"
#include "Geometry/ColorMap.h"
#include "Geometry/ColorMapStatic.h"
#include "Geometry/Material.h"
#include "Geometry/ScaleTG.h"
#include "Geometry/TranslateTG.h"

#include <QString>

using namespace std;



class Mapping
{
public:

    Mapping();
    Mapping(const shared_ptr<ConfigMappingReader> configMapping);

    vec3  mapeigPunt(vec3 puntMonReal);
    float mapeigValor(float valorMonReal);
    shared_ptr<ScaleTG> mapeigScale();
    shared_ptr<TranslateTG> mapeigTrasllada();
    shared_ptr<Material> mapeigMaterial(int i, ColorMapStatic::ColorMapType tCM, double valorReal);

    int getNumProps() { return setup->numProp; };


    ObjectFactory::OBJECT_TYPES getObjectTypeProp(int i) {
        return setup->props[i].first;
    }

    ColorMapStatic::ColorMapType getColorMapProp(int i) {
        return setup->props[i].second;
    }

    shared_ptr<ColorMap> getColorMap(ColorMapStatic::ColorMapType tCM);
    shared_ptr<ConfigMappingReader> getSetup(){return setup;}


private:
    shared_ptr<ConfigMappingReader> setup;
};

