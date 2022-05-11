#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}


vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
    // TO DO Fase 1:
    // Mapeig del punt en coordenades reals a coordenades de mon virtual
    vec3 puntMonVirtual;
    // Cal posar el codi per a situar el punt del mon Real al Virtual
    // Cal canviar la següent línia
    float x_std = (puntMonReal.x - setup->Rxmin) / (setup->Rxmax - setup->Rxmin);
    float z_std = (puntMonReal.z - setup->Rzmin) / (setup->Rzmax - setup->Rzmin);
    puntMonVirtual.x=((setup->Vxmax - setup->Vxmin) * x_std) +setup->Vxmin;
    puntMonVirtual.y=puntMonReal.y;
    puntMonVirtual.z=-(((setup->Vzmax - setup->Vzmin) * z_std) +setup->Vzmin);
    //return puntMonVirtual
    return puntMonVirtual;
}


float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1:
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
      double valorMonVirtual,minVirtual,maxVirtual,minReal,maxReal;
      minVirtual= 0;
      //el valor por el que dividimos se puede cambiar
      maxVirtual = (setup->Vymax-setup->Vymin)/2;
      minReal = setup->propLimits[0].first;
      maxReal = setup->propLimits[0].second;
      valorMonVirtual = (((valorMonReal-minReal)*(maxVirtual-minVirtual))/(maxReal-minReal))+minVirtual;
      return valorMonReal;
}

//escalat per passar al mon virtual
shared_ptr<ScaleTG> Mapping::mapeigScale(){
    vec3 escalar;
    escalar.x = (setup->Vxmax - setup->Vxmin)/(setup->Rxmax - setup->Rxmin);
    escalar.y = 1.0;
    escalar.z = (setup->Vzmax - setup->Vzmin)/(setup->Rzmax - setup->Rzmin);
    return make_shared<ScaleTG>(escalar);
};

//traslladar al mon virtual
shared_ptr<TranslateTG> Mapping::mapeigTrasllada(){
    vec3 trasllada;
    trasllada.x = setup->Rxmin *(setup->Vxmax - setup->Vxmin)/(setup->Rxmax - setup->Rxmin) + setup->Vxmin;
    trasllada.y = 0.0;
    trasllada.z = setup->Rzmin *(setup->Vzmax - setup->Vzmin)/(setup->Rzmax - setup->Rzmin) + setup->Vzmin;
    return make_shared<TranslateTG>(trasllada);
};


shared_ptr<ColorMap> Mapping::getColorMap(ColorMapStatic::ColorMapType tCM) {
   auto cm = make_shared<ColorMapStatic>(ColorMapStatic::COLOR_MAP_TYPE_PLASMA);
   return cm;
}

shared_ptr<Material> Mapping::mapeigMaterial(int i, ColorMapStatic::ColorMapType tCM, double valorMonReal) {

    // TO DO Fase 2: Cal mapejar el color difus al color de la paleta o ColorMap segons el valorMonReal i
    // els valors minims i maxims de les propietats
    // Tens els valors minims i maxim de cada propietat a l'estructura de setup d'aquesta classe

    auto cm = getColorMap(tCM);

    int idx = 255*int(valorMonReal/(setup->propLimits[i].second-setup->propLimits[i].first));
    /*auto mat = make_shared<Metal>(cm->getColor(idx));
    mat->shineness = 500;
    mat->ambient = vec3(0.1,0.1,0.1);
    mat->especular = vec3(0.3,0.3,0.3);

    return mat;*/
    // TODO

}
