#ifndef SCALE_H
#define SCALE_H
#include "TG.h"



class ScaleTG : public TG
{
public:
    vec3 vscale;
    float factor;
    ScaleTG(vec3 scale_);
    ScaleTG(float factor);
    ~ScaleTG();
};

#endif // SCALE_H
