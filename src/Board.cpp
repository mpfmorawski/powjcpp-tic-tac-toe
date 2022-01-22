#include "Board.hpp"

void Board::print() const
{   
    std::stringstream output_row, output;
    std::string output_str;
    std::string dash_line = "———————————";
    for(const std::array<Field, 3> row : state)
    {
        for(const Field field : row)
            output_row << " " << field.getMark() << " |";
        output_str = output_row.str();
        output_row.str(std::string());
        output_str.pop_back();
        output << output_str << std::endl;
        output << dash_line << std::endl;
    }
    output_str = output.str();

    // example of using std::find_end algorithm
    output_str.erase(std::find_end(output_str.begin(), output_str.end(), dash_line.begin(), dash_line.end()), output_str.end());

    std::cout << output_str;
}

int Board::check_rows(char player) const
{
    char opponent = (player == 'X') ? 'O' : 'X';
    for(const std::array<Field, 3> row : state)
    {   
        // example of using std::count_if algorithm
        if(std::count_if(row.begin(), row.end(), [&](Field f){return f.getMark() == player;}) == 3)
            return 1;
        // example of using std::count_if algorithm
        if(std::count_if(row.begin(), row.end(), [&](Field f){return f.getMark() == opponent;}) == 3)
            return -1;
    }
    return 0;
}

int Board::check_columns(char player) const
{   
    char opponent = (player == 'X') ? 'O' : 'X';

    std::string column;
    for(int i = 0; i < 3; i++)
    {
        for(const std::array<Field, 3> row : state)
            column.push_back(row[i].getMark());

        // example of using std::count_if algorithm
        if(std::count_if(column.begin(), column.end(), [&](char c){return c == player;}) == 3)
            return 1;
        // example of using std::count_if algorithm
        if(std::count_if(column.begin(), column.end(), [&](char c){return c == opponent;}) == 3)
            return -1;
        column = "";
    }
    return 0;
}

int Board::check_diagonals(char player) const
{   
    char opponent = (player == 'X') ? 'O' : 'X';
    // example of using a std::vector container
    std::vector<int> index1{0, 1, 2};
    std::vector<int> index2{0, 1, 2};
    std::string diagonal;
    for(int i = 0; i < 2; i++)
    {
        for(const int ind : index1)
            diagonal.push_back(state[ind][index2[ind]].getMark());
        // example of using std::count_if algorithm
        if(std::count_if(diagonal.begin(), diagonal.end(), [&](char c){return c == player;}) == 3)
            return 1;
        // example of using std::count_if algorithm
        if(std::count_if(diagonal.begin(), diagonal.end(), [&](char c){return c == opponent;}) == 3)
            return -1;
        diagonal = "";
        // example of using std::reverse algorithm 
        std::reverse(index2.begin(), index2.end());
    }
    return 0;
}


int Board::check_state(char player) const
{   
    if(check_rows(player) != 0)
        return check_rows(player);
    if(check_columns(player) != 0)
        return check_columns(player);
    if(check_diagonals(player) != 0)
        return check_diagonals(player);
    return 0;
}

std::pair<int, int> Board::convert_index_to_coords(int index) const
{
    // example of using std::pair
    std::pair<int, int> coords;
    coords.first = (index - 1) / 3;
    coords.second = index - (coords.first * 3) - 1;
    return coords;
}

void Board::draw_mark(char mark, int index)
{
    if(index < 1 || index > 9)
        throw std::string("Indeks poza zakresem.");
    std::pair<int, int> coords = convert_index_to_coords(index);
    state[coords.first][coords.second].draw(mark);
}

 std::vector<std::pair<Board, int>> Board::possible_next_boards(char player)
{
    Board current_board{*this};
    std::vector<std::pair<Board, int>> next_boards;
    std::pair<Board, int> temp_board;
    for(int i = 1; i < 10; i++)
    {   
        try
        {   
            current_board = *this;
            current_board.draw_mark(player, i);
            temp_board.first = current_board;
            temp_board.second = i;
            next_boards.push_back(temp_board);
        }
        catch(const std::string s)
        {
            // field is occupied
        }

    }
    return next_boards;
}

bool Board::is_tie(char player) const
{
    for(const std::array<Field, 3> row : state)
    {   
        // example of using std::count_if algorithm
        if(std::find_if(row.begin(), row.end(), [&](Field f){return f.getMark() == ' ';}) != row.end())
            return false;
    }
    if(check_state(player) == 0)
        return true;
    else
        return false;
}