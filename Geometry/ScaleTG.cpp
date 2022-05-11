#include "ScaleTG.h"

ScaleTG::ScaleTG(vec3 scale_)
{
    vscale = scale_;
    matTG = Scale(scale_);

}

ScaleTG::ScaleTG(float factor){
    this->factor = factor;
    matTG=Scale(vec3(factor,factor,factor));
}
ScaleTG::~ScaleTG()
{

}
