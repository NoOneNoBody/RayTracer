//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __COLORS_H
#define __COLORS_H

#include "vectors.h"

class Color
{
private:
    void fixColor()
    {
        if(rgb.getX()>255){rgb.setX(255);}
        if(rgb.getY()>255){rgb.setY(255);}
        if(rgb.getZ()>255){rgb.setZ(255);}
        if(rgb.getX()<0){rgb.setX(0);}
        if(rgb.getY()<0){rgb.setY(0);}
        if(rgb.getZ()<0){rgb.setZ(0);}
    }
    Vector<int> rgb;
public:
    Color(){}
    Color(int r, int g, int b): rgb(Vector<int>(r,g,b)){}
    Color(const Color& col): rgb(col.rgb){}
    Color operator+(const Color& col) const
    {
        Color result;
        result.rgb = this->rgb + col.rgb;
        result.fixColor();
        return result;
    }
    Color operator-(const Color& col) const
    {
        Color result;
        result.rgb = this->rgb - col.rgb;
        result.fixColor();
        return result;
    }
    Color operator+=(const Color& col)
    {
        (*this) = (*this) + col;
        return (*this);
    }
    Color operator-=(const Color& col)
    {
        (*this) = (*this) - col;
        return (*this);
    }
    Color operator*(const Color& col) const
    {
        Color result;
        double r1 = this->rgb.getX() / 255.0;
        double g1 = this->rgb.getY() / 255.0;
        double b1 = this->rgb.getZ() / 255.0;
        double r2 = col.rgb.getX() / 255.0;
        double g2 = col.rgb.getY() / 255.0;
        double b2 = col.rgb.getZ() / 255.0;
        double r3 = r1*r2*255.0;
        double g3 = g1*g2*255.0;
        double b3 = b1*b2*255.0;
        result.rgb = Vector<int>(r3,g3,b3);
        result.fixColor();
        return result;
    }
    Color operator*(double s) const
    {
        Color result;
        result.rgb = this->rgb*s;
        result.fixColor();
        return result;
    }
    friend Color operator*(double s, const Color& col)
    {
        Color result;
        result.rgb = col.rgb*s;
        result.fixColor();
        return result;
    }
    unsigned char getR(){return rgb.getX();}
    unsigned char getG(){return rgb.getY();}
    unsigned char getB(){return rgb.getZ();}
    void setR(unsigned char r){rgb.setX((int)r);}
    void setG(unsigned char g){rgb.setX((int)g);}
    void setB(unsigned char b){rgb.setX((int)b);}
};

#endif
