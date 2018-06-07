//Wykonal Michal Warzecha I rok WEAIiB grupa 5b
#ifndef OBJ_H
#define OBJ_H

#include<vector>
#include "bmp.h"
#include "vectors.h"
#include "colors.h"

class Vertex
{
private:
    double x,y,z;
public:
    Vertex(double x = 0, double y = 0, double z = 0):x(x),y(y),z(z){};
    double getX() const{return x;}
    double getY() const{return y;}
    double getZ() const{return z;}
    Vector<> toVector() const {return Vector<>(x,y,z);}
};

class Face
{
private:
    int v1,v2,v3;
public:
    Face(int v1 = 0, int v2 = 0, int v3 = 0):v1(v1),v2(v2),v3(v3){};
    unsigned int getV1(){return v1;}
    unsigned int getV2(){return v2;}
    unsigned int getV3(){return v3;}
};

class Object
{
private:
    std::vector<Vertex> verts;
    std::vector<Face> faces;
public:
    Object(){}
    Vertex getVertex(unsigned int index) const;
    Face getFace(unsigned int index) const;
    int getVertCount() const{return verts.size();}
    int getFaceCount() const{return faces.size();}
    void saveToFile(const char* path);
    void loadFromFile(const char* path);
    ~Object();
};

void OrthogonalProjection(JiMP2::BMP& bmp, const Object& obj, int center_x, int center_y, int scale, unsigned char Red = 255, unsigned char Green = 0, unsigned char Blue = 0);

#endif // OBJ_H
