//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef __VECTORS_H
#define __VECTORS_H

#include <iostream>
#include <math.h>
#include "exceptions.h"

template<typename T = double>
class Vector
{
    private:
        T x,y,z;

    public:
    Vector():x(0),y(0),z(0){}
    Vector(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector(const Vector& vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    T getX() const
    {
        return this->x;
    }

    T getY() const
    {
        return this->y;
    }

    T getZ() const
    {
        return this->z;
    }

    void setX(T val)
    {
        this->x = val;
    }

    void setY(T val)
    {
        this->y = val;
    }

    void setZ(T val)
    {
        this->z = val;
    }

    void operator=(const Vector& vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    Vector operator+(const Vector& vec) const
    {
        Vector result = Vector(this->x + vec.x, this->y + vec.y, this->z + vec.z);
        return result;
    }

    Vector operator-(const Vector& vec) const
    {
        Vector result = Vector(this->x - vec.x, this->y - vec.y, this->z - vec.z);
        return result;
    }

    Vector operator-() const
    {
        return Vector(-x,-y,-z);
    }

    Vector operator*(double s) const
    {
        Vector result = Vector(this->x * s, this->y * s, this->z * s);
        return result;
    }

    Vector operator*(const Vector& vec) const
    {
        Vector result = Vector((this->y * vec.z) - (this->z * vec.y),
                        (this->z * vec.x) - (this->x * vec.z),
                        (this->x * vec.y) - (this->y * vec.x));
        return result;
    }

    Vector operator/(double s) const
    {
        if(s == 0)throw ExceptionDivisionByZero();
        Vector result = Vector(this->x / s, this->y / s, this->z / s);
        return result;
    }

    double dotProduct(const Vector& vec) const
    {
        return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
    }

    double magnitude() const
    {
        return sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
    }

    double squareMagnitude() const
    {
        return (pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
    }

    Vector normalize() const
    {
        double len = sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
        Vector result = Vector(this->x/len, this->y/len, this->z/len);
        return result;
    }

    bool operator==(const Vector& vec) const
    {
        return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
    }
    bool operator!=(const Vector& vec) const
    {
        return !(*this == vec);
    }
    friend Vector operator*(T s, const Vector& vec)
    {
        return vec*s;
    }
};

#endif
