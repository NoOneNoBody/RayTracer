//Wykonal Michal Warzecha I rok WEAIiB grupa 5b
#include "scene.h"

Vector<> TriangleFaceObject::CalculateNormal(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3) const
{
    Vector<> vec1 = v3 - v2;
    Vector<> vec2 = v1 - v2;
    return (vec1 * vec2).normalize();
}
bool TriangleFaceObject::CheckSide(const Ray& ray, const Vector<>& t1, const Vector<>& t2) const
{
    Vector<> v1 = t1 - ray.origin;
    Vector<> v2 = t2 - ray.origin;
    Vector<> n1 = (v2 * v1).normalize();
    if(ray.direction.dotProduct(n1)<=0)
    {
        return false;
    }
    if(ray.direction.dotProduct(v1)<=0 && ray.direction.dotProduct(v2)<=0)
    {
        return false;
    }
    return true;
}
bool TriangleFaceObject::CheckIfHitsTris(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3) const
{
    return (CheckSide(ray,v1,v2) && CheckSide(ray,v2,v3) && CheckSide(ray,v3,v1));
}
Hit TriangleFaceObject::CalculateDistance(const Ray& ray, const Vector<>& v1, const Vector<>& v2, const Vector<>& v3, const Material& mat) const
{
    Vector<> normal = CalculateNormal(ray,v1,v2,v3);
    double d = - v2.dotProduct(normal);
    double t = - (ray.origin.dotProduct(normal)+d)/(ray.direction.dotProduct(normal));
    Vector<> p = ray.origin + (ray.direction * t);
    return Hit{t,normal,p,mat};
}

Hit TriangleFaceObject::CheckHit(const Ray& ray) const
{
    Hit min_dist = Hit{INF};
    for(unsigned int j=0; j < obj.getFaceCount(); ++j)
    {
        Face currentFace = obj.getFace(j);
        Vector<> v1 = getVertexWorldPos(currentFace.getV1()-1);
        Vector<> v2 = getVertexWorldPos(currentFace.getV2()-1);
        Vector<> v3 = getVertexWorldPos(currentFace.getV3()-1);
        if(CheckIfHitsTris(ray, v1, v2, v3))
        {
            Hit hit = CalculateDistance(ray, v1, v2, v3, mat);
            if(hit.dist > MIN)
            {
                min_dist = std::min(min_dist, hit);
            }
        }
    }
    return min_dist;
}

bool TriangleFaceObject::CheckIfHits(const Ray& ray) const
{
    for(unsigned int j=0; j < obj.getFaceCount(); ++j)
    {
        Face currentFace = obj.getFace(j);
        Vector<> v1 = getVertexWorldPos(currentFace.getV1()-1);
        Vector<> v2 = getVertexWorldPos(currentFace.getV2()-1);
        Vector<> v3 = getVertexWorldPos(currentFace.getV3()-1);
        if(CheckIfHitsTris(ray, v1, v2, v3))
        {
            return true;
        }
    }
    return false;
}

Hit SphereObject::CheckHit(const Ray& ray) const
{
    Vector<> Q = ray.origin - position;
    double a = 1;
    double b = 2*Q.dotProduct(ray.direction);
    double c = Q.squareMagnitude() - pow(radius,2);
    double delta = pow(b,2) - (4*a*c);
    double t = INF;
    if(0 == delta)
    {
        t = - b/2.;
    }
    else if(0 < delta)
    {
        double sqrt_delta = sqrt(delta);
        double t1 = (-b-sqrt_delta)/2.;
        double t2 = (-b+sqrt_delta)/2.;
        t1 = (t1>MIN)?t1:INF;
        t2 = (t2>MIN)?t2:INF;
        t = std::min(t1,t2);
    }
    Vector<> p = ray.origin + (ray.direction * t);
    Vector<> normal = (p-position).normalize();
    return Hit{t,normal,p,mat};
}

bool SphereObject::CheckIfHits(const Ray& ray) const
{
    Vector<> Q = ray.origin - position;
    double a = 1;
    double b = 2*Q.dotProduct(ray.direction);
    double c = Q.squareMagnitude() - pow(radius,2);
    double delta = pow(b,2) - (4*a*c);
    double t = INF;
    if(0 == delta)
    {
        t = - b/2.;
    }
    else if(0 < delta)
    {
        double sqrt_delta = sqrt(delta);
        double t1 = (-b-sqrt_delta)/2.;
        double t2 = (-b+sqrt_delta)/2.;
        t1 = (t1>MIN)?t1:INF;
        t2 = (t2>MIN)?t2:INF;
        t = std::min(t1,t2);
    }
    return (t>MIN && t<INF);
}
