// cpplibstring: библиотека содержащая функционал строк
// License: © Mak

#ifndef _STRING_
#define _STRING_

#include "macros.h"
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
        for (int iter(0); iter < _length; iter++)
            cout << _str_ptr[iter] << " : " << iter << "\n";
        cout << "String Length: " << _length;
    }
    
#endif
    
    String() : _str_ptr(new char(0)), _length(0) {  }
    
    String(charset _str_ptr) : _length(std::strlen(_str_ptr)),
                             _str_ptr(new char(_length))
    {
        _insert(_str_ptr, 0, _length);
    }
    
    String(const String& _str_cls) : _length(std::strlen(_str_cls._str_ptr)),
                             _str_ptr(new char(_length))
    {
        _insert(_str_cls._str_ptr, 0, _length);
    }
    
    // Присваивание
    String& operator= (charset _str_ptr)
    {
        if (!_check_string(_str_ptr, _str_ptr))
        {
            _length = std::strlen(_str_ptr);
            _str_ptr = new char(_length);
            _insert(_str_ptr, 0, _length);
        }
        return *this;
    }
    
    String& operator= (const String& _str_cls)
    {
        if (!_check_string(_str_ptr, _str_cls._str_ptr))
        {
            _length = std::strlen(_str_cls._str_ptr);
            _str_ptr = new char(_length);
            _insert(_str_cls._str_ptr, 0, _length);
        }
        return *this;
    }
    
    cpplibMethod("APPEND");
    // APPEND. Добавляет в строку новый ряд символов
    String& append(charset _str_ptr)
    {
        _add_str(_str_ptr);
        return *this;
    }
    
    String& append(const String& _str_cls)
    {
        _add_str(_str_cls._str_ptr);
        return *this;
    }
    
    // +=. Аналог метода append
    String& operator+= (charset _str_ptr)
    {
        _add_str(_str_ptr);
        return *this;
    }
    
    String& operator+= (const String& _str_cls)
    {
        _add_str(_str_cls._str_ptr);
        return *this;
    }
    
    // +. Создаёт новую строку из 2
    String operator+ (charset _str_ptr)
    {
        String new_string = _str_ptr;
        new_string += _str_ptr;
        return new_string;
    }
    
    String operator+ (const String& _str_cls)
    {
        String new_string = _str_ptr;
        new_string += _str_cls._str_ptr;
        return new_string;
    }
    
    // ==. Сравнивает две строки
    bool operator== (charset _str_ptr)
    {
        return _check_string(_str_ptr, _str_ptr);
    }
    
    bool operator== (const String& _str_cls)
    {
        return _check_string(_str_cls._str_ptr, _str_ptr);
    }
    
    // !=, Аналог оператора ==, только наоборот
    bool operator!= (charset _str_ptr)
    {
        return !_check_string(_str_ptr, _str_ptr);
    }
    
    bool operator!= (const String& _str_cls)
    {
        return !_check_string(_str_cls._str_ptr, _str_ptr);
    }
    
    // []. Вернёт ссылку на элемент строки по индексу
    char& operator[](int index)
    {
        return _str_ptr[index];
    }
    
    cpplibMethod("AT");
    // AT. Аналог оператора []
    char& at(int index)
    {
        return _str_ptr[index];
    }
    
private:
    
    // Структура возвращаемого типа в search
    struct _search_result
    {
        int start;  // Начало строки
        int end;    // Конец строки
        
        bool is_try = true;  // Найдена ли строка (всегда true)
        
        _search_result(int _s, int _e, bool _r) : start(_s), end(_e), is_try(_r)
            {  };
    };
    
    // Ищет ряд символов внутри строки
    _search_result _search(charset _string, int _h_)
    {
        char* buffer = new char(std::strlen(_string));
        int buffer_index = 0;
        
        int start = 0;  // Старт позиция
        int end = 0;    // Конец позиция
        
        for (int iter(0); iter < _length; iter++)
        {
            if (_string[buffer_index] == _str_ptr[iter])
            {
                buffer[buffer_index] = _str_ptr[iter];
                start = iter;
                buffer_index++;
            }
            else
            {
                buffer_index = 0;
                buffer = new char(std::strlen(_string));
                start = 0;
            }
            
            if (_check_string(_string, buffer)) return _search_result(
                start, iter, true
            );
        }
        
        return _search_result(0, 0, false);
    }
    
public:

    cpplibMethod("SEARCH");
    // Вернёт совпадение: есть ли набор символов в строке
    bool search(charset _string)
    {
        return _search(_string, 0).is_try;
    }
    
    bool search(const String& _str_cls)
    {
        return _search(_str_cls._str_ptr, 0).is_try;
    }
    
    cpplibProperty("LENGTH");
    // get: _length. Вернет размер строки
    int const& length = _length;
    
private:

    // Вставляет строку с позиции A до позиции B
    void _insert(charset _string, int _a, int _b)
    {
        for (int iter(_a); iter < _b; iter++)
            _str_ptr[iter] = _string[iter - _a];
    }
    
    void _insert(char _char, int _a)
    {
        _str_ptr[_a] = _char;
    }
    
    // Добавляет строку в конец
    void _add_str(charset _string)
    {
        char* buffer_ptr = _str_ptr;
        int new_length = std::strlen(buffer_ptr) + std::strlen(_string);
        
        _str_ptr = new char(new_length);
        _length = new_length;
        _insert(buffer_ptr, 0, std::strlen(buffer_ptr));
        _insert(_string, std::strlen(buffer_ptr), new_length);
    }
    
    // Проверяет 2 строки на равенство
    bool _check_string(charset _string, charset _string2)
    {
        if (std::strlen(_string) != std::strlen(_string2)) return false;
        
        for (int iter(0); iter < std::strlen(_string); iter++)
            if (_string2[iter] != _string[iter]) return false;
            
        return true;
    }
    
private:

    int _length;       // длинна строки
    char* _str_ptr;    // строка в виде динамического массива
};

#endif
