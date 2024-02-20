// MK_String/Tests/Main.cpp
// Точка входа для консольной программы

#include <iostream>
#include "String.h"

int main(void) 
{
    String str = "Hi!";
    std::cout << str.search("H");
}
