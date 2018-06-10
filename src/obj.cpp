//Wykonal Michal Warzecha I rok WEAIiB grupa 5b
#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <cmath>
#include "../include/obj.h"
#include "../include/exceptions.h"

void Object::loadFromFile(const char* path)
{
    verts.clear();
    faces.clear();
    unsigned int line = 0;
    std::ifstream myObjFile;
    std::string textLine;
    std::istringstream iss;
    std::string command;
    myObjFile.open(path);
    if (myObjFile.is_open()) {
        while (!myObjFile.eof()) {
            std::getline(myObjFile, textLine);
            iss.clear();
            iss.str(textLine);
            command = std::string();
            iss>>command;
            ++line;
            switch(command[0])
            {
            case 'v':
                {
                    if(command[1] == '\0')
                    {
                        double v[3];
                        int i=0;
                        for(i;i<3&&!iss.eof();++i){iss>>v[i];}
                        if(i==3 && iss.eof())
                        {
                            this->verts.push_back(Vertex(v[0],v[1],v[2]));
                        }
                        else
                        {
                            throw ExceptionWrongCommand(line);
                        }
                    }
                    else
                    {
                        continue;
                    }
                    break;
                }
            case 'f':
                {
                    if(command[1] == '\0')
                    {
                        unsigned int v[3];
                        std::string garbage;
                        int i=0;
                        for(i;i<3&&!iss.eof();++i){iss>>v[i];}
                        if(i==3 && iss.eof())
                        {
                            this->faces.push_back(Face(v[0],v[1],v[2]));
                        }
                        else
                        {
                            throw ExceptionWrongCommand(line);
                        }
                    }
                    else
                    {
                        continue;
                    }
                    break;
                }
            default:
                continue;
            }
        }
    }
    else
    {
        throw ExceptionCantOpenFile(path);
    }
    myObjFile.close();
}

void Object::saveToFile(const char* path)
{
    std::ofstream myfile;
    myfile.open (path);
    for(unsigned int i=0; i<verts.size(); ++i)
    {
        myfile<<"v "<<verts[i].getX()<<" "<<verts[i].getY()<<" "<<verts[i].getZ()<<std::endl;
    }
    for(unsigned int i=0; i<faces.size(); ++i)
    {
        myfile<<"f "<<faces[i].getV1()<<"//"<<i+1<<" "<<faces[i].getV2()<<"//"<<i+1<<" "<<faces[i].getV3()<<"//"<<i+1<<std::endl;
    }
    myfile.close();
}

Vertex Object::getVertex(unsigned int index) const
{
    if(index<verts.size())
    {
        return verts[index];
    }
    else
    {
        return Vertex(0,0,0);
    }
}

Face Object::getFace(unsigned int index) const
{
    if(index<faces.size())
    {
        return faces[index];
    }
    else
    {
        return Face(0,0,0);
    }
}

Object::~Object()
{
    verts.clear();
    faces.clear();
}


void DrawLine(JiMP2::BMP& bmp, int start_x, int start_y, int end_x, int end_y, unsigned char r, unsigned char g, unsigned char b)
{
    int dist_x = std::abs(start_x-end_x);
    int dist_y = std::abs(start_y-end_y);
    if(dist_x > dist_y)
    {
        for (int i = 0; i < dist_x; ++i)
        {
            bmp.setPixel(start_x+(i*(start_x<end_x?1:-1)), start_y+(((i*float(dist_y))/dist_x)*(start_y<end_y?1:-1)), r, g, b);
        }
    }
    else
    {
        for (int i = 0; i < dist_y; ++i)
        {
            bmp.setPixel(start_x+(((i*float(dist_x))/dist_y)*(start_x<end_x?1:-1)), start_y+(i*(start_y<end_y?1:-1)), r, g, b);
        }
    }
}

void OrthogonalProjection(JiMP2::BMP& bmp, const Object& obj, int center_x, int center_y, int scale, unsigned char Red, unsigned char Green, unsigned char Blue)
{
    for(int i=0; i<obj.getFaceCount(); ++i)
    {
        int v1_x = (obj.getVertex(obj.getFace(i).getV1()-1).getX()*scale);
        int v1_y = (obj.getVertex(obj.getFace(i).getV1()-1).getY()*scale);
        int v2_x = (obj.getVertex(obj.getFace(i).getV2()-1).getX()*scale);
        int v2_y = (obj.getVertex(obj.getFace(i).getV2()-1).getY()*scale);
        int v3_x = (obj.getVertex(obj.getFace(i).getV3()-1).getX()*scale);
        int v3_y = (obj.getVertex(obj.getFace(i).getV3()-1).getY()*scale);
        DrawLine(bmp, center_x + v1_x, center_y + v1_y, center_x + v2_x, center_y + v2_y, Red, Green, Blue);
        DrawLine(bmp, center_x + v2_x, center_y + v2_y, center_x + v3_x, center_y + v3_y, Red, Green, Blue);
        DrawLine(bmp, center_x + v3_x, center_y + v3_y, center_x + v1_x, center_y + v1_y, Red, Green, Blue);
    }
}
