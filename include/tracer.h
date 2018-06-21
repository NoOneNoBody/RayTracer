//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __TRACER_H
#define __TRACER_H

#define MAX_ITERATION 3
#define AMBIENT 0.3
#define SKY_LIGHT 0.1

#include <algorithm>
#include <cmath>
#include "scene.h"
#include "camera.h"
#include "rays.h"
#include "obj.h"
#include "colors.h"

class Tracer
{
private:
    Color CalculateLight(const Ray& ray, const Hit& hit, const Scene& scene) const;
    Color CalculateColor(const Ray& ray, const Hit& hit, const Scene& scene, unsigned int iteration) const;
    Color FindIntersections(const Ray& ray, const Scene& scene, unsigned int iteration = 0) const;
public:
    Tracer(){}
    void RenderImage(JiMP2::BMP& bmp, const Camera& cam, const Scene& scene);
    virtual ~Tracer(){}
};

#endif
