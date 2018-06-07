//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __RAYS_H
#define __RAYS_H

#include "vectors.h"

struct Ray
{
    Vector<> origin;
    Vector<> direction;

    Ray(): origin(), direction(Vector<>(0,0,1)){}
    Ray(const Vector<>& o, const Vector<>& d): origin(o), direction(d){}
};

#endif
