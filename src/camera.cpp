//Wykonal Michal Warzecha I rok WEAIiB grupa 5b
#include "../include/camera.h"


Camera::Camera(const JiMP2::BMP& b, const Vector<>& pos, const Vector<>& f, const Vector<>& u, double dist, double _size): bmp(b), origin(pos), forward(f), up(u), planeDist(dist), size(_size)
{
    forward = forward.normalize();
    up = up.normalize();
    position = origin + (forward.normalize()*planeDist);
    right = (forward * up).normalize();
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
