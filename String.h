#ifndef __STRING__
#define __STRING__

#include <cstring>
#define __debug_cppString__

#ifdef  __debug_cppString__
#include <iostream>
using std::cout;
#endif

class String
{
    typedef const char* charset;
    
public:

#ifdef __debug_cppString__
    
    void show_info()
    {
        for (int iter(0); iter < __length; iter++)
            cout << __str_ptr[iter] << " : " << iter << "\n";
        cout << "String Length: " << __length;
    }
    
#endif
    
    String() : __str_ptr(new char(0)), __length(0) {  }
    
    String(charset _str_ptr) : __length(std::strlen(_str_ptr)),
                             __str_ptr(new char(__length))
    {
        __insert(_str_ptr, 0, __length);
    }
    
    String(const String& _str_cls) : __length(std::strlen(_str_cls.__str_ptr)),
                             __str_ptr(new char(__length))
    {
        __insert(_str_cls.__str_ptr, 0, __length);
    }
    
    // APPEND. Добавляет в строку новый ряд символов
    String& append(charset _str_ptr)
    {
        __add_str(_str_ptr);
        return *this;
    }
    
    String& append(const String& _str_cls)
    {
        __add_str(_str_cls.__str_ptr);
        return *this;
    }
    
    // +=. Аналог метода append
    String& operator+= (charset _str_ptr)
    {
        __add_str(_str_ptr);
        return *this;
    }
    
    String& operator+= (const String& _str_cls)
    {
        __add_str(_str_cls.__str_ptr);
        return *this;
    }
    
    // +. Создаёт новую строку из 2
    String operator+ (charset _str_ptr)
    {
        String new_string = __str_ptr;
        new_string += _str_ptr;
        return new_string;
    }
    
    String operator+ (const String& _str_cls)
    {
        String new_string = __str_ptr;
        new_string += _str_cls.__str_ptr;
        return new_string;
    }
    
    // ==. Сравнивает две строки
    bool operator== (charset _str_ptr)
    {
        return __check_string(_str_ptr, __str_ptr);
    }
    
    bool operator== (const String& _str_cls)
    {
        return __check_string(_str_cls.__str_ptr, __str_ptr);
    }
    
    // !=, Аналог оператора ==, только наоборот
    bool operator!= (charset _str_ptr)
    {
        return !__check_string(_str_ptr, __str_ptr);
    }
    
    bool operator!= (const String& _str_cls)
    {
        return !__check_string(_str_cls.__str_ptr, __str_ptr);
    }
    
    // []. Вернёт ссылку на элемент строки по индексу
    char& operator[](int index)
    {
        return __str_ptr[index];
    }
    
    // AT. Аналог оператора []
    char& at(int index)
    {
        return __str_ptr[index];
    }
    
private:
    
    // Структура возвращаемого типа в search
    struct __search_result
    {
        int start;  // Начало строки
        int end;    // Конец строки
        
        bool is_try = true;  // Найдена ли строка (всегда true)
        
        __search_result(int _s, int _e, bool _r) : start(_s), end(_e), is_try(_r)
            {  };
    };
    
    // Ищет ряд символов внутри строки
    __search_result __search(charset _string, int __h__)
    {
        char* buffer = new char(std::strlen(_string));
        int buffer_index = 0;
        
        int start = 0;  // Старт позиция
        int end = 0;    // Конец позиция
        
        for (int iter(0); iter < __length; iter++)
        {
            if (_string[buffer_index] == __str_ptr[iter])
            {
                buffer[buffer_index] = __str_ptr[iter];
                start = iter;
                buffer_index++;
            }
            else
            {
                buffer_index = 0;
                buffer = new char(std::strlen(_string));
                start = 0;
            }
            
            if (__check_string(_string, buffer)) return __search_result(
                start, iter, true
            );
        }
        
        return __search_result(0, 0, false);
    }
    
public:

    // Вернёт совпадение: есть ли набор символов в строке
    bool search(charset _string)
    {
        return __search(_string, 0).is_try;
    }
    
    bool search(const String& _str_cls)
    {
        return __search(_str_cls.__str_ptr, 0).is_try;
    }
    
    // get: __lengh. Вернет размер строки
    int const& length = __length;
    
private:

    // Вставляет строку с позиции A до позиции B
    void __insert(charset _string, int _a, int _b)
    {
        for (int iter(_a); iter < _b; iter++)
            __str_ptr[iter] = _string[iter - _a];
    }
    
    void __insert(char _char, int _a)
    {
        __str_ptr[_a] = _char;
    }
    
    // Добавляет строку в конец
    void __add_str(charset _string)
    {
        char* buffer_ptr = __str_ptr;
        int new_length = std::strlen(buffer_ptr) + std::strlen(_string);
        
        __str_ptr = new char(new_length);
        __length = new_length;
        __insert(buffer_ptr, 0, std::strlen(buffer_ptr));
        __insert(_string, std::strlen(buffer_ptr), new_length);
    }
    
    // Проверяет 2 строки на равенство
    bool __check_string(charset _string, charset _string2)
    {
        if (std::strlen(_string) != std::strlen(_string2)) return false;
        
        for (int iter(0); iter < std::strlen(_string); iter++)
            if (_string2[iter] != _string[iter]) return false;
            
        return true;
    }
    
private:

    int __length;       // длинна строки
    char* __str_ptr;    // строка в виде динамического массива
};

#endif