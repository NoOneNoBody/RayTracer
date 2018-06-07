//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#include <iostream>
#include <fstream>
#include "tracer.h"

void saveBmp(const JiMP2::BMP& bmp,const char* path)
{
    std::ofstream outfile(path, std::ofstream::binary);
    outfile << bmp;
}

void loadObj(Object& obj,const char* path)
{
    try
    {
        obj.loadFromFile(path);
    }
    catch(Exceptions& e)
    {
        e.printException();
        exit(0);
    }
}

void RenderImage(JiMP2::BMP& bmp, const Camera& cam, const Tracer& tracer)
{
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();

    int pixelsCount = width*height;
    int currentPixel = 0;

    for(unsigned int y = 0; y < height; ++y)
    {
        for(unsigned int x = 0; x < width; ++x)
        {
            Ray ray = cam.ConstructRay(x,y);
            Color col = tracer.FindIntersections(ray);
            bmp.setPixel(x,y,col.getR(),col.getG(),col.getB());
            //std::cout<<".";
            ++currentPixel;
            std::cout<<currentPixel<<"/"<<pixelsCount<<std::endl;
        }
    }
}

int main()
{
    unsigned int width = 800;
    unsigned int height = 600;

    Object obj1;
 //   Object obj2;
    loadObj(obj1, "cow.obj");
 //   loadObj(obj2, "example.obj");

    TriangleFaceObject s_obj1(obj1, Vector<>(0,0,300), 10, Material(Color(255,0,0),0.5,0.5));
  //  TriangleFaceObject s_obj2(obj2, Vector<>(2,0,295), 10, Color(0,255,0));
    PlaneObject s_plane(Vector<>(0,-50,0), Vector<>(0,1,0), Material(Color(100,200,100)));
 //   SphereObject s_sphere(Vector<>(-50,0,280), 20, Color(20,20,255));
 //   SphereObject s_sphere1(Vector<>(50,0,280), 20, Material(Color(0,0,0),1,1));

    Scene scene(Vector<>(-1,-1,1).normalize(), 1, Color(255,255,255));
    scene.addObject(s_obj1);
 //   scene.addObject(s_obj2);
    scene.addObject(s_plane);
 //   scene.addObject(s_sphere);
 //   scene.addObject(s_sphere1);
    scene.setBackground(Color(0,200,255));

    JiMP2::BMP bmp(width,height);
    Camera cam(bmp, Vector<>(0,0,0), Vector<>(0,0,1), Vector<>(0,1,0), 1, 0.001);
    Tracer tracer(scene);

    RenderImage(bmp, cam, tracer);

    saveBmp(bmp, "out1.bmp");
    std::cout<<"Image generated!"<<std::endl;
    return 0;
}
