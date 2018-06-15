//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#include "../include/scene_loader.h"

SceneLoader::SceneLoader()
{
    //ctor
}

SceneLoader::~SceneLoader()
{
    //dtor
}

void SceneLoader::setCamera(std::istringstream& iss, Camera& cam, const unsigned int& lineCounter) const
{
    double v[11];
    int i = 0;
    char tmp;
    for(i;i<11&&(iss>>v[i]);++i);
    if(i==11 && !(iss >> tmp))
    {
        cam.setCamera(Vector<>(v[0],v[1],v[2]), Vector<>(v[3],v[4],v[5]), Vector<>(v[6],v[7],v[8]), v[9], v[10]);
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::setBackground(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    double v[3];
    int i = 0;
    char tmp;
    for(i;i<3&&(iss>>v[i]);++i);
    if(i==3 && !(iss >> tmp))
    {
        scene.setBackground(Color(v[0],v[1],v[2]));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::addSphere(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    double v[9];
    int i = 0;
    char tmp;
    for(i;i<9&&(iss>>v[i]);++i);
    if(i==9 && !(iss >> tmp))
    {
        scene.addObject(new SphereObject(Vector<>(v[0],v[1],v[2]), v[3], Material(Color(v[4],v[5],v[6]), v[7], v[8])));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::addPlane(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    double v[11];
    int i = 0;
    char tmp;
    for(i;i<11&&(iss>>v[i]);++i);
    if(i==11 && !(iss >> tmp))
    {
        scene.addObject(new PlaneObject(Vector<>(v[0],v[1],v[2]), Vector<>(v[3],v[4],v[5]), Material(Color(v[6],v[7],v[8]), v[9], v[10])));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::addObject(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    std::string path;
    iss >> path;
    double v[9];
    int i = 0;
    char tmp;
    for(i;i<9&&(iss>>v[i]);++i);
    if(i==9 && !(iss >> tmp))
    {
        Object obj;
        try
        {
            obj.loadFromFile(path.c_str());
        }
        catch(Exceptions& e)
        {
            e.printException();
            throw ExceptionWrongCommand(lineCounter);
        }
        scene.addObject(new MeshObject(new Object(obj), Vector<>(v[0],v[1],v[2]), v[3], Material(Color(v[4],v[5],v[6]), v[7], v[8])));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::addLightP(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    double v[8];
    int i = 0;
    char tmp;
    for(i;i<8&&(iss>>v[i]);++i);
    if(i==8 && !(iss >> tmp))
    {
        scene.addLight(new PointLight(Vector<>(v[0],v[1],v[2]), v[3], v[4], Color(v[5],v[6],v[7])));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::addLightD(std::istringstream& iss, Scene& scene, const unsigned int& lineCounter) const
{
    double v[7];
    int i = 0;
    char tmp;
    for(i;i<7&&(iss>>v[i]);++i);
    if(i==7 && !(iss >> tmp))
    {
        scene.addLight(new DirectionalLight(Vector<>(v[0],v[1],v[2]), v[3], Color(v[4],v[5],v[6])));
    }
    else
    {
        throw ExceptionWrongCommand(lineCounter);
    }
}

void SceneLoader::getNextLine(std::istringstream& iss, std::string& command, std::string& line, unsigned int& lineCounter) const
{
    iss.clear();
    iss.str(line);
    command = std::string();
    iss>>command;
    ++lineCounter;
}

Scene& SceneLoader::loadSceneFromFile(const char* path, Scene& scene, Camera& cam) const
{
    unsigned int lineCounter = 0;
    std::ifstream inputStream;
    std::istringstream iss;
    std::string command;
    std::string line;
    inputStream.open(path);
    if (inputStream.is_open()) {
    	std::getline(inputStream, line);
        getNextLine(iss, command, line, lineCounter);
        if(!command.compare("C"))
        {
            setCamera(iss, cam, lineCounter);
        }
        else
        {
            throw ExceptionWrongCommand(lineCounter);
        }
        while (std::getline(inputStream, line)) {
            getNextLine(iss, command, line, lineCounter);
            switch(command[0])
            {
            case '#':
                continue;
            case 'B':
                {
                    if(!command.compare("B"))
                    {
                        setBackground(iss, scene, lineCounter);
                    }
                    else
                    {
                        throw ExceptionWrongCommand(lineCounter);
                    }
                    break;
                }
            case 'S':
                {
                    if(!command.compare("S"))
                    {
                        addSphere(iss, scene, lineCounter);
                    }
                    else
                    {
                        throw ExceptionWrongCommand(lineCounter);
                    }
                    break;
                }
            case 'P':
                {
                    if(!command.compare("P"))
                    {
                        addPlane(iss, scene, lineCounter);
                    }
                    else
                    {
                        throw ExceptionWrongCommand(lineCounter);
                    }
                    break;
                }
            case 'O':
                {
                    if(!command.compare("O"))
                    {
                        addObject(iss, scene, lineCounter);
                    }
                    else
                    {
                        throw ExceptionWrongCommand(lineCounter);
                    }
                    break;
                }
            case 'L':
                {
                    if(!command.compare("LP"))
                    {
                        addLightP(iss, scene, lineCounter);
                    }
                    else if(!command.compare("LD"))
                    {
                        addLightD(iss, scene, lineCounter);
                    }
                    else
                    {
                        throw ExceptionWrongCommand(lineCounter);
                    }
                    break;
                }
            default:
                throw ExceptionWrongCommand(lineCounter);
            }
        }
    }
    else
    {
        throw ExceptionCantOpenFile(path);
    }
    inputStream.close();
    return scene;
}
