#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "Game.hpp"
#include "Heuristic.hpp"
#include "GameAnalytics.hpp"

class GamePlay
{
private:
    int player1_depth;
    int player2_depth;
    Heuristic *player1_heuristic;
    Heuristic *player2_heuristic;

    Game play_game();
    Game simulate_game();

public:
    GamePlay();

    GamePlay *set_player1_depth(int _player1_depth);
    GamePlay *set_player2_depth(int _player2_depth);
    GamePlay *set_player1_heuristic(Heuristic *_player1_heuristic);
    GamePlay *set_player2_heuristic(Heuristic *_player2_heuristic);

    int get_player1_depth();
    int get_player2_depth();
    Heuristic *get_player1_heuristic();
    Heuristic *get_player2_heuristic();

    GameAnalytics play_manual_game(int _human_player);
    GameAnalytics play_games(int _game_count);
    GameAnalytics simulate_games(int _game_count);
};

#endif