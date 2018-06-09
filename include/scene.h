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
    bool operator<(const Hit& hit) const {return dist<hit.dist;}
    bool operator>(const Hit& hit) const {return dist>hit.dist;}
};

class Light
{
public:
    Light(){}
    virtual Vector<> getDirection(const Vector<>& pos) const = 0;
    virtual double getIntensity() const = 0;
    virtual Color getColor() const = 0;
    virtual double getDistance(const Vector<>& pos) const = 0;
};

class DirectionalLight : public Light
{
private:
    Vector<> direction;
    double intensity;
    Color color;
public:
    DirectionalLight(Vector<> d, double i, Color c): direction(d), intensity(i), color(c){}
    Vector<> getDirection(const Vector<>& pos) const {return direction.normalize();}
    double getIntensity() const {return intensity;}
    Color getColor() const {return color;}
    double getDistance(const Vector<>& pos) const {return INF;}
};

class PointLight : public Light
{
private:
    Vector<> position;
    double intensity;
    double range;
    Color color;
public:
    PointLight(Vector<> p, double i, double r, Color c): position(p), intensity(i), range(r), color(c){}
    Vector<> getDirection(const Vector<>& pos) const
    {
        Vector<> dist = (pos-position);
        return (dist.normalize()*(std::max(0.,(range - dist.magnitude()))/range));
    }
    double getIntensity() const {return intensity;}
    Color getColor() const {return color;}
    double getDistance(const Vector<>& pos) const {return (pos-position).magnitude();}
};

class SceneObject
{
public:
    SceneObject(){}
    virtual Hit CheckHit(const Ray& ray) const = 0;
    virtual bool CheckIfHits(const Ray& ray) const = 0;
    virtual ~SceneObject(){}
};

class MeshObject: public SceneObject
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
    MeshObject(const Object& o): obj(o), scale(1){}
    MeshObject(const Object& o, const Vector<double>& offs, double s, Material m = Material()): obj(o), offset(offs), scale(s), mat(m){}
    Vector<> getVertexWorldPos(unsigned int index) const {return ((obj.getVertex(index).toVector()*scale)+offset);}
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
    Hit CheckHit(const Ray& ray) const;
    bool CheckIfHits(const Ray& ray) const;
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
    std::vector<const Light*> lights;
    Color background;
public:
    Scene(){}
    Scene(const std::vector<const Light*>& l): lights(l){}
    Scene(const std::vector<const SceneObject*>& objs): objects(objs){}
    Scene(const std::vector<const SceneObject*>& objs, const std::vector<const Light*>& l): lights(l), objects(objs){}
    unsigned int getCount() const {return objects.size();}
    void setBackground(Color col){background = col;}
    Color getBackground() const {return background;}
    void addObject(const SceneObject& ob){objects.push_back(&ob);}
    void addLight(const Light& l){lights.push_back(&l);}
    void pop_backObj(){objects.pop_back();}
    const SceneObject* getObject(const size_t& i) const {return objects[i];}
    size_t getLightCount() const {return lights.size();}
    const Light& getLight(const size_t& i) const {return (*(lights[i]));}
    bool isLighted(const Vector<>& pos, const Light& light) const;
    virtual ~Scene(){}
};

#endif
