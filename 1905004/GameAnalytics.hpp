#ifndef GAME_ANALYTICS_HPP
#define GAME_ANALYTICS_HPP

#include <vector>
using namespace std;

#include "Game.hpp"

class GameAnalytics
{
private:
    vector<Game> games;

public:
    GameAnalytics();
    void add_game(Game _game);
    int get_game_count();
    int get_draw_count();
    int get_player1_win_count();
    int get_player2_win_count();
    float get_player1_win_percentage();
    float get_player2_win_percentage();
    void print();
};

#endif