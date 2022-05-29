#include "MyErrors.h"

Error::Error(const char *str)
{
    message = str;
}

void Error::print_message()
{
    cout << message << endl << endl;
}

InputError::InputError(const char *str) : Error(str)
{};

AccessError::AccessError(const char *str) : Error(str)
{};

MathError::MathError(const char *str) : Error(str)
{};

AllocError::AllocError(const char *str) : Error(str)
{};