#include "Field.hpp"

#include <iostream>
#include <string>

void Field::draw(char input_mark)
{
    if(mark != ' ')
        throw std::string("Podane pole jest juz zajete. Wybierz inne pole.");
    if(input_mark != 'X' && input_mark != 'O')
        throw std::string("Niepozadany znak.");
    mark = input_mark;
}