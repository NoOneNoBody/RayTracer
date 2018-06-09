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

int main()
{
    unsigned int width = 1600;
    unsigned int height = 900;

//    Object obj1;
//    Object obj2;
//    loadObj(obj1, "cow.obj");
//    loadObj(obj2, "example.obj");

//    MeshObject s_obj1(obj1, Vector<>(0,0,300), 10, Material(Color(255,0,0),0.5,0.5));
//    MeshObject s_obj2(obj2, Vector<>(20,50,295), 30, Material(Color(0,255,0),1));
    PlaneObject s_plane(Vector<>(0,-50,0), Vector<>(0,1,0), Material(Color(100,200,100)));
    PlaneObject s_wall(Vector<>(0,0,400), Vector<>(0,0,-1), Material(Color(200,100,100)));
    SphereObject s_sphere(Vector<>(-50,0,280), 50, Material(Color(20,20,255),0.5, 0.5));
    SphereObject s_sphere1(Vector<>(50,0,280), 20, Material(Color(0,0,0),1,1));

    DirectionalLight dir_light(Vector<>(-1,-1,1).normalize(), 1, Color(255,255,255));
    PointLight pt_light(Vector<>(-50,50,200), 1, 1000, Color(255,255,255));

    Scene scene;
    scene.addLight(dir_light);
    scene.addLight(pt_light);
//    scene.addObject(s_obj1);
//    scene.addObject(s_obj2);
    scene.addObject(s_plane);
    scene.addObject(s_wall);
    scene.addObject(s_sphere);
    scene.addObject(s_sphere1);
    scene.setBackground(Color(0,200,255));

    JiMP2::BMP bmp(width,height);
    Camera cam(bmp, Vector<>(0,100,-300), Vector<>(0,-0.1,1), Vector<>(0,1,0), 0.2, 0.0001);
    Tracer tracer;

    tracer.RenderImage(bmp, cam, scene);

    saveBmp(bmp, "out1.bmp");
    std::cout<<"Image generated!"<<std::endl;
    return 0;
}
