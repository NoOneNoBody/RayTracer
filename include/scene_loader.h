//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <cstring>
#include <sstream>
#include <fstream>
#include "scene.h"
#include "camera.h"
#include "exceptions.h"

class SceneLoader
{
    public:
        SceneLoader();
        virtual ~SceneLoader();
        Scene& loadSceneFromFile(const char* path, Scene& scene, Camera& cam) const;
    protected:

    private:
        void getNextLine(std::istringstream& iss, std::string& command, std::string& line, unsigned int& lineCounter) const;
        void setCamera(std::istringstream& iss, Camera& cam, const unsigned int& lineCounter) const;
        void setBackground(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
        void addSphere(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
        void addPlane(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
        void addObject(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
        void addLightP(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
        void addLightD(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const;
};

#endif // SCENE_LOADER_H
