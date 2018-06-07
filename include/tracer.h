//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __TRACER_H
#define __TRACER_H

#define MAX_ITERATION 3

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
    const Scene& scene;
    Color CalculateColor(const Ray& ray, const Hit& hit, unsigned int iteration) const
    {
        if(hit.dist != INF)
        {
            Vector<> h = (ray.direction + scene.getLight().direction).normalize();
            double diff = std::max(0.,scene.getLight().direction.dotProduct(-hit.normal));
            double nh = std::max(0.,h.dotProduct(-hit.normal));
            diff = std::min((diff+0.3), 1.0);
            double spec = std::pow(nh, 48.0);
            Color color;
            if(scene.IsLighted(hit.pos))
            {
                color = (hit.mat.color * scene.getLight().color * diff * scene.getLight().intencity) + (hit.mat.spec*scene.getLight().color * spec * scene.getLight().intencity) + (scene.getBackground()*0.1);
            }
            else
            {
                color = (hit.mat.color * 0.3) + (scene.getBackground()*0.1);
            }
            if(iteration < MAX_ITERATION && (hit.mat.gloss*(1.0/(iteration+1.0))) > 0.1)
            {
                Vector<> reflection = (ray.direction - (2*ray.direction.dotProduct(hit.normal)* hit.normal)).normalize();
                color = color + (hit.mat.gloss*(1.0/(iteration+1.0))) * FindIntersections(Ray(hit.pos, reflection),++iteration);
            }
            return color;
        }
        else
        {
            return scene.getBackground();
        }
    }
public:
    Tracer(const Scene& s): scene(s){}
    Color FindIntersections(const Ray& ray, unsigned int iteration = 0) const
    {
        Hit min_t = Hit{INF};
        for(unsigned int i=0; i < scene.getCount(); ++i)
        {
            const SceneObject* current = scene[i];
            Hit hit = current->CheckHit(ray);
            if(hit.dist > MIN)
            {
                min_t = std::min(min_t, hit);
            }
        }
        return CalculateColor(ray, min_t, iteration);
    }
    virtual ~Tracer(){}
};

#endif
