//Wykonal Michal Warzecha Informatyka EAIiIB grupa 5b
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<iostream>

class Exceptions
{
    public:
        Exceptions(){}
        virtual ~Exceptions(){}
        virtual void printException()=0;
    protected:

    private:
};


class ExceptionCantOpenFile: public Exceptions
{
private:
    const char* path;
public:
    ExceptionCantOpenFile(const char* p): path(p){}
    void printException()
    {
        std::cerr<<"Cannot open file "<<path<<std::endl;
    }
};

class ExceptionWrongCommand: public Exceptions
{
private:
    unsigned int line;

public:
    ExceptionWrongCommand(unsigned int _line):Exceptions(), line(_line){}
    void printException()
    {
        std::cerr<<"Wrong command at line: "<<line<<std::endl;
    }
};

class ExceptionDivisionByZero: public Exceptions
{
private:

public:
    ExceptionDivisionByZero():Exceptions(){}
    void printException()
    {
        std::cerr<<"Division by zero"<<std::endl;
    }
};

#endif // EXCEPTIONS_H
