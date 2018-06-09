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
    Color CalculateLight(const Ray& ray, const Hit& hit, const Scene& scene) const
    {
        Color color;
        Color diffColor;
        Color specColor;
        for(size_t i=0; i<scene.getLightCount(); ++i)
        {
            double diff = 0;
            double spec = 0;
            if(scene.isLighted(hit.pos, scene.getLight(i)))
            {
                const Vector<> lightDir = scene.getLight(i).getDirection(hit.pos);
                double lightIntensity = scene.getLight(i).getIntensity() * lightDir.magnitude();
                const Vector<> h = (ray.direction.normalize() + lightDir.normalize()).normalize();
                diff = (std::max(0.,lightDir.dotProduct(-hit.normal)) * lightIntensity);
                diff = std::min(diff, 1.0);
                double nh = std::max(0.,h.dotProduct(-hit.normal));
                spec = (std::pow(nh, 48.0) * lightIntensity);
            }
            diffColor += (diff * scene.getLight(i).getColor());
            specColor += (hit.mat.spec * scene.getLight(i).getColor() * spec);
        }
        diffColor += Color(255,255,255) * AMBIENT;
        color = (hit.mat.color * diffColor) + specColor + (scene.getBackground()*SKY_LIGHT);
        return color;
    }
    Color CalculateColor(const Ray& ray, const Hit& hit, const Scene& scene, unsigned int iteration) const
    {
        if(hit.dist != INF)
        {
            Color color = CalculateLight(ray, hit, scene);
            if(iteration < MAX_ITERATION && (hit.mat.gloss*(1.0/(++iteration))) > 0.1)
            {
                Vector<> reflection = (ray.direction - (2*ray.direction.dotProduct(hit.normal)* hit.normal)).normalize();
                color +=  (hit.mat.gloss*(1.0/iteration)) * FindIntersections(Ray(hit.pos, reflection), scene, iteration);
            }
            return color;
        }
        else
        {
            return scene.getBackground();
        }
    }
    Color FindIntersections(const Ray& ray, const Scene& scene, unsigned int iteration = 0) const
    {
        Hit min_t = Hit{INF};
        for(unsigned int i=0; i < scene.getCount(); ++i)
        {
            const SceneObject* current = scene.getObject(i);
            Hit hit = current->CheckHit(ray);
            if(hit.dist > MIN)
            {
                min_t = std::min(min_t, hit);
            }
        }
        return CalculateColor(ray, min_t, scene, iteration);
    }
public:
    Tracer(){}
    void RenderImage(JiMP2::BMP& bmp, const Camera& cam, const Scene& scene)
    {
        unsigned int width = bmp.getWidth();
        unsigned int height = bmp.getHeight();

        for(unsigned int y = 0; y < height; ++y)
        {
            for(unsigned int x = 0; x < width; ++x)
            {
                Ray ray = cam.ConstructRay(x,y);
                Color col = FindIntersections(ray, scene);
                bmp.setPixel(x,y,col.getR(),col.getG(),col.getB());
            }
        }
    }
    virtual ~Tracer(){}
};

#endif
