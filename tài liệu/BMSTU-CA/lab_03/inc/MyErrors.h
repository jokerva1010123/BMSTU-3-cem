#ifndef MYERRORS_H
#define MYERRORS_H

#include <iostream>
#include <exception>

using namespace std;

class Error : public exception
{
protected:
    const char *message;
public:
    Error(const char *str);

    virtual void print_message();
};

class InputError : public Error
{
public:
    InputError(const char *str);
};

class AccessError : public Error
{
public:
    AccessError(const char *str);
};

class MathError : public Error
{
public:
    MathError(const char *str);
};

class AllocError : public Error
{
public:
    AllocError(const char *str);
};

#endif 
