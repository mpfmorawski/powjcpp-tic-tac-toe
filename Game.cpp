#include "Game.hpp"
#include <random>

void Game::print_introduction() const
{
    std::cout << "Kolko i krzyzyk" << std::endl;
    std::cout << "———————————————" << std::endl;
    std::cout << "Przed Toba rozgrywka w kolko i krzyzyk." << std::endl;
    std::cout << "Twoim rywalem bedzie arcymistrz - komputer TicTacToe-Master2021," << std::endl;
    std::cout << "ktory jeszcze nigdy nie przegral." << std::endl;
    std::cout << "Chcialbys byc pierwszym, ktory go pokona?" << std::endl;
    std::cout << "Ostrzegam, ze nie bedzie to proste." << std::endl << std::endl;
    std::cout << "Krotka instrukcja:" << std::endl;
    print_info();
    std::cout << "Zaczynajmy!" << std::endl << std::endl;
}

void Game::print_info() const
{
    std::cout << "Aby narysowac znak w odpowiednim polu," << std::endl;
    std::cout << "podaj liczbe z zakresu od 1 do 9." << std::endl;
    std::cout << "Skorzystaj ze schematu: " << std::endl << std::endl;
    std::cout << "1|2|3" << std::endl << "—————" << std::endl;
    std::cout << "4|5|6" << std::endl << "—————" << std::endl;
    std::cout << "7|8|9" << std::endl << std::endl;
}

void Game::print_player_info() const
{
    std::cout << "Podaj liczbe od 1 do 9 oznaczajaca wolne pole" << std::endl; 
}

void Game::print_end_info() const
{
    std::cout << "A nie mowilem? Niestety nie wygrales. :(" << std::endl;
    std::cout << "Moze uda sie nastepnym razem!" << std::endl;
}

void Game::player_move()
{   
    print_player_info();
    bool end = false;
    int input;
    while(!end)
    {
        try
        {   
            std::cin >> input;
            while(std::cin.fail())
            {
                std::cout << "To nie jest liczba." << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input;
            }
            board.draw_mark(player_mark, input);
            board.print();
            end = true;

        }
        catch(const std::string s)
        {
            std::cout << s << std::endl;
        }
        
    }
}

void Game::player_select_mark()
{
    std::cout << "Wybierasz krzyzyk (X) czy kolko (O)?" << std::endl;
    std::cout << "Pamietaj, ze krzyzyk (X) zaczyna." << std::endl << std::endl;
    std::cout << "Wprowadz liczbe opisujaca wybrany znak:" << std::endl << std::endl;
    std::cout << "X - 1\t O - 2" << std::endl;
    bool end = false;
    int input;
    while(!end)
    {
        std::cin >> input;
        while(std::cin.fail())
        {
            std::cout << "To nie jest liczba." << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input;
        }
        if(input == 1 || input == 2)
            end = true;
        else
            std::cout << "Wprowadz liczbe 1 (X) lub liczbe 2 (O)." << std::endl;
    }
    if(input == 1)
    {
        player_mark = 'X';
        ai_mark = 'O';
        std::cout << "Wybrales X, wiec zaczynasz." << std::endl;
    }
    else
    {
        player_mark = 'O';
        ai_mark = 'X';
        std::cout << "Wybrales O, wiec zaczyna komputer." << std::endl;
    }
    
}

void Game::run()
{
    print_introduction();
    player_select_mark();
    if(player_mark == 'X')
        player_move();
    bool end = false;
    while(!end)
    {
        std::cout << "Ruch wykonuje komputer" << std::endl;
        board.draw_mark(ai_mark, minimax(board, 9, ai_mark, true).first);
        board.print();
        if(board.check_state(ai_mark) != 0 || board.is_tie(ai_mark))
            end = true;
        else
        {
            player_move();
            if(board.check_state(player_mark) != 0 || board.is_tie(player_mark))
                end = true;
        }
    }
    print_end_info();
}

std::pair<int, int> Game::minimax(Board& b, int depth, char player, bool isMaxMove)
{   
    char opponent = (player == 'X') ? 'O' : 'X';
    char which_move;
    if(isMaxMove)
        which_move = player;
    else
        which_move = opponent;

    std::pair<int, int> best_move;
    best_move.first = 0;
    // check if there is an final state or depth <= 0
    int score = b.check_state(player);
    if(score != 0 || depth <= 0 || b.is_tie(player) == true)
    {
        best_move.second = score;
        return best_move;
    }
    // if not final state or depth <= 0, then check: MAX or MIN
    if(isMaxMove)
    {
        std::vector<std::pair<int, int>> moves_and_scores;
        for(auto boards : b.possible_next_boards(which_move))
        {
            std::pair<int, int> mv_and_scr;
            mv_and_scr.first = boards.second;
            mv_and_scr.second = minimax(boards.first, depth-1, player, !isMaxMove).second;
            moves_and_scores.push_back(mv_and_scr);
        }
        int max_score = -2;
        for(auto move_and_score : moves_and_scores)
        {
            if(move_and_score.second > max_score)
                max_score = move_and_score.second;
        }
        std::vector<int> max_moves;
        for(auto move_and_score : moves_and_scores)
        {
            if(move_and_score.second == max_score)
                max_moves.push_back(move_and_score.first);
        }
        std::random_device random_device;
        std::mt19937 engine{random_device()};
        std::uniform_int_distribution<int> dist(0, max_moves.size() - 1);

        best_move.first = max_moves[dist(engine)];
        best_move.second = max_score;
        return best_move;
    }
    else
    {
        std::vector<std::pair<int, int>> moves_and_scores;
        for(auto boards : b.possible_next_boards(which_move))
        {
            std::pair<int, int> mv_and_scr;
            mv_and_scr.first = boards.second;
            mv_and_scr.second = minimax(boards.first, depth-1, player, !isMaxMove).second;
            moves_and_scores.push_back(mv_and_scr);
        }
        int min_score = 2;
        for(auto move_and_score : moves_and_scores)
        {
            if(move_and_score.second < min_score)
                min_score = move_and_score.second;
        }
        std::vector<int> min_moves;
        for(auto move_and_score : moves_and_scores)
        {
            if(move_and_score.second == min_score)
                min_moves.push_back(move_and_score.first);
        }
        std::random_device random_device;
        std::mt19937 engine{random_device()};
        std::uniform_int_distribution<int> dist(0, min_moves.size() - 1);

        best_move.first = min_moves[dist(engine)];
        best_move.second = min_score;
        return best_move;
    }
    
}