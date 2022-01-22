#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Board.hpp"

class Game
{
public:
    Game() : player_mark{'X'}, ai_mark{'O'} {}
    void print_introduction() const;
    void print_info() const;
    void print_player_info() const;
    void print_end_info() const;
    void player_move();
    void player_select_mark();

    void run();
    
    std::pair<int, int> minimax(Board&, int, char, bool);

private:
    char player_mark, ai_mark;
    Board board;
};

#endif