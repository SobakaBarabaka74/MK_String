// MK_String/Tests/Main.cpp
// Точка входа для консольной программы

#include <iostream>
#include "String.h"

int main(void) 
{
    String str = "Hi!";

    // поиск в строке
    std::cout << str.search("H") << "\n";

    // длинна строки изменяется динамически
    str = "Ho!";
    std::cout << str.length;
}
