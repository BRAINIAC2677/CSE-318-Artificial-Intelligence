#include <iostream>
using namespace std;

#include "GamePlay.hpp"
#include "Heuristic.hpp"

int main()
{
    Heuristic *player1_heuristic = new Heuristic1();
    Heuristic *player2_heuristic = new Heuristic2();
    GamePlay *game_play = (new GamePlay())->set_player1_heuristic(player1_heuristic)->set_player2_heuristic(player2_heuristic)->set_player1_depth(3)->set_player2_depth(2);
    // GameAnalytics game_analytics = game_play->simulate_games(2);
    GameAnalytics game_analytics = game_play->play_games(100);
    game_analytics.print();
    GameState game_state = GameState();
}