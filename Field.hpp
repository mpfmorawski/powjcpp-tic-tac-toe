#ifndef FIELD_HPP
#define FIELD_HPP

class Field
{
    public:
        Field() : mark{' '} {}

        char getMark() const {return mark;}
        void draw(char);

    private:
        char mark;

};

#endif