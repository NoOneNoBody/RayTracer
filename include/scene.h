//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __SCENE_H
#define __SCENE_H

#include<vector>
#include "obj.h"
#include "rays.h"
#include "colors.h"
#include "vectors.h"
#include "limits.h"

struct Material
{
    Color color;
    double spec;
    double gloss;
    Material(){}
    Material(Color col, double s = 0, double g = 0): color(col), spec(s), gloss(g){}
};

struct Hit
{
    double dist;
    Vector<> normal;
    Vector<> pos;
    Material mat;
    bool operator<(const Hit& hit) const
    {
        return dist<hit.dist;
    }
    bool operator>(const Hit& hit) const
    {
        return dist>hit.dist;
    }
};

struct Light
{
    Vector<> direction;
    double intencity;
    Color color;
};

class SceneObject
{
public:
    SceneObject(){}
    virtual Hit CheckHit(const Ray& ray) const = 0;
    virtual bool CheckIfHits(const Ray& ray) const = 0;
    virtual ~SceneObject(){}
};

class TriangleFaceObject: public SceneObject
{
private:
    const Object& obj;
    Vector<> offset;
    double scale;
    Material mat;
    Vector<> CalculateNormal(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3) const;
    bool CheckSide(const Ray& ray, const Vector<>& t1, const Vector<>& t2) const;
    bool CheckIfHitsTris(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3) const;
    Hit CalculateDistance(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3, const Material& mat) const;
public:
    TriangleFaceObject(const Object& o): obj(o), scale(1){}
    TriangleFaceObject(const Object& o, const Vector<double>& offs, double s, Material m = Material()): obj(o), offset(offs), scale(s), mat(m){}
    Vector<> getVertexWorldPos(unsigned int index) const { return ((obj.getVertex(index).toVector()*scale)+offset);}
    Hit CheckHit(const Ray& ray) const;
    bool CheckIfHits(const Ray& ray) const;
};

class PlaneObject: public SceneObject
{
private:
    Vector<> position;
    Vector<> normal;
    Material mat;
public:
    PlaneObject(): position(), normal(Vector<>(0,1,0)), mat(){}
    PlaneObject(const Vector<>& pos, const Vector<>& norm,const Material& m = Material()): position(pos), normal(norm), mat(m){}
    Hit CheckHit(const Ray& ray) const
    {
        double d = - position.dotProduct(normal);
        double t = - (ray.origin.dotProduct(normal)+d)/(ray.direction.dotProduct(normal));
        Vector<> p = ray.origin + (ray.direction * t);
        return Hit{t,normal,p,mat};
    }
    bool CheckIfHits(const Ray& ray) const
    {
        double d = - position.dotProduct(normal);
        double t = - (ray.origin.dotProduct(normal)+d)/(ray.direction.dotProduct(normal));
        return t>MIN;
    }
};

class SphereObject: public SceneObject
{
private:
    Vector<> position;
    double radius;
    Material mat;
public:
    SphereObject(): position(), radius(1), mat(){}
    SphereObject(const Vector<>& p, double r,const Material& m = Material()): position(p), radius(r), mat(m){}
    Hit CheckHit(const Ray& ray) const;
    bool CheckIfHits(const Ray& ray) const;
};

class Scene
{
private:
    std::vector<const SceneObject*> objects;
    Light light;
    Color background;
public:
    Scene(Vector<> lDir, double lIntence, Color col): light{lDir, lIntence, col}{}
    Scene(const std::vector<const SceneObject*>& objs): objects(objs){}
    unsigned int getCount() const {return objects.size();}
    void setBackground(Color col){background = col;}
    Color getBackground() const {return background;}
    void addObject(const SceneObject& ob){objects.push_back(&ob);}
    void pop_backObj(){objects.pop_back();}
    const SceneObject* operator[](size_t i) const {return objects[i];}
    const Light& getLight()const {return light;}
    bool IsLighted(const Vector<>& pos) const
    {
        Hit min_t = Hit{INF};
        for(unsigned int i=0; i < objects.size(); ++i)
        {
            const SceneObject* current = objects[i];
            if(current->CheckIfHits(Ray(pos,-light.direction)))
            {
                return false;
            }
        }
        return true;
    }
    virtual ~Scene(){}
};

#endif
