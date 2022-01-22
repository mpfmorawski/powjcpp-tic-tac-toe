#ifndef BOARD_HPP
#define BOARD_HPP

#include "Field.hpp"
#include <array>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

class Board
{   
    public:
        Board() = default;
        Board(const Board&) = default;

        void print() const;

        int check_rows(char) const;
        int check_columns(char) const;
        int check_diagonals(char) const;
        int check_state(char) const;

        // example of using std::pair
        std::pair<int, int> convert_index_to_coords(int) const;
        void draw_mark(char, int);

        // example of using std::pair in a std::vector container
        std::vector<std::pair<Board, int>> possible_next_boards(char);

        bool is_tie(char) const;
        
    private:
        // example of using a std::array container in a std::array container
        std::array<std::array<Field, 3>, 3> state;
};



#endif