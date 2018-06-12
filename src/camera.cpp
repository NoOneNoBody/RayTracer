//Wykonal Michal Warzecha I rok WEAIiB grupa 5b
#include "../include/camera.h"

Camera::Camera(const JiMP2::BMP& b): bmp(b), planeDist(0.5), size(0.001)
{
    origin = Vector<>(0,0,0);
    forward = Vector<>(0,0,1);
    up = Vector<>(0,1,0);
    right = Vector<>(1,0,0);
    position = origin + (forward.normalize()*planeDist);
}

Camera::Camera(const JiMP2::BMP& b, const Vector<>& pos, const Vector<>& f, const Vector<>& u, double dist, double _size):
    bmp(b), origin(pos), forward(f), up(u), planeDist(dist), size(_size)
{
    forward = forward.normalize();
    up = up.normalize();
    position = origin + (forward.normalize()*planeDist);
    right = (forward * up).normalize();
    up = (right * forward).normalize();
}

Camera::Camera(const Camera& c):
    bmp(c.bmp), origin(c.origin), position(c.position), forward(c.forward), up(c.up), right(c.right), planeDist(c.planeDist), size(c.size)
{

}

void Camera::setCamera(const Vector<>& pos, const Vector<>& f, const Vector<>& u, double dist, double _size)
{
    planeDist = dist;
    size = _size;
    origin = pos;
    up = u.normalize();
    forward = f.normalize();
    position = origin + (forward.normalize()*planeDist);
    right = (forward * up).normalize();
    up = (right * forward).normalize();
}

Ray Camera::ConstructRay(int x, int y) const
{
    if(x>=0 && x<bmp.getWidth() && y>=0 && y<bmp.getHeight())
    {
        Vector<> P = position - ((x-(bmp.getWidth()/2.0))*size*right) - ((y-(bmp.getHeight()/2.0))*size*up);
        Vector<> dir = (P-origin).normalize();
        return Ray{origin,dir};
    }
    return Ray();
}
