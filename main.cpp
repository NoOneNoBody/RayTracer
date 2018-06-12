//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#include <iostream>
#include <fstream>

#include "include/tracer.h"
#include "include/scene_loader.h"

void saveBmp(const JiMP2::BMP& bmp,const char* path)
{
    std::ofstream outfile(path, std::ofstream::binary);
    outfile << bmp;
}

void loadScene(const SceneLoader& loader, const char* path, Scene& scene, Camera& cam)
{
    try
    {
        loader.loadSceneFromFile(path, scene, cam);
    }
    catch(Exceptions& e)
    {
        e.printException();
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    unsigned int width = 1600;
    unsigned int height = 900;

    JiMP2::BMP bmp(width,height);

    Scene scene;
    Camera cam(bmp);
    Tracer tracer;
    SceneLoader loader;

    loadScene(loader, argv[1], scene, cam);

    tracer.RenderImage(bmp, cam, scene);

    saveBmp(bmp, "out.bmp");
    std::cout<<"Image generated!"<<std::endl;
    return 0;
}
