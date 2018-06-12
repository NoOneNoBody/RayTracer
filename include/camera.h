//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __CAMERA_H
#define __CAMERA_H

#include "bmp.h"
#include "rays.h"

class Camera
{
private:
    const JiMP2::BMP& bmp;
    double planeDist;
    double size;
    Vector<> position;
    Vector<> forward;
    Vector<> right;
    Vector<> up;
    Vector<> origin;
public:
    Camera(const JiMP2::BMP& b);
    Camera(const JiMP2::BMP& b, const Vector<>& pos, const Vector<>& f, const Vector<>& u, double dist = 0.5, double _size = 0.001);
    Camera(const Camera& c);
    void setCamera(const Vector<>& pos, const Vector<>& f, const Vector<>& u, double dist = 0.5, double _size = 0.001);
    Ray ConstructRay(int x, int y) const;
    virtual ~Camera(){}
};

#endif
