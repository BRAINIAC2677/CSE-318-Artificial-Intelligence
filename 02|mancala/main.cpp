#include <iostream>
using namespace std;

#include "GamePlay.hpp"
#include "Heuristic.hpp"

enum class GameType
{
    PLAY_AI_VS_AI,
    SIMULATE_AI_VS_AI,
    SIMULATE_HUMAN_VS_AI,
    SIMULATE_AI_VS_HUMAN
};

Heuristic *heuristics[] = {nullptr, new Heuristic1(), new Heuristic2, new Heuristic3, new Heuristic4};

// configurations
GameType game_type = GameType::PLAY_AI_VS_AI;
int player1_depth = 5;
int player2_depth = 5;
int game_count = 20;
int player1_heuristic = 2;
int player2_heuristic = 3;
// end of configurations

void print_game_configs()
{
    string divider = "----------------------------------------";
    cout << "\033[1;34m\nGame Configurations\033[0m\n";
    cout << divider << "\n";
    cout << "Player 1 heuristic: " << player1_heuristic << "\nPlayer 2 heuristic: " << player2_heuristic << "\n";
    cout << divider << "\n";
    cout << "Player 1 Depth: " << player1_depth << "\nPlayer 2 Depth: " << player2_depth << "\n";
    cout << divider << "\n";
}

int main()
{
    GamePlay *game_play = (new GamePlay())->set_player1_heuristic(heuristics[player1_heuristic])->set_player2_heuristic(heuristics[player2_heuristic])->set_player1_depth(player1_depth)->set_player2_depth(player2_depth);
    GameAnalytics game_analytics;

    switch (game_type)
    {
    case GameType::PLAY_AI_VS_AI:
        game_analytics = game_play->play_games(game_count);
        print_game_configs();
        break;
    case GameType::SIMULATE_AI_VS_AI:
        game_analytics = game_play->simulate_games(game_count);
        print_game_configs();
        break;
    case GameType::SIMULATE_AI_VS_HUMAN:
        game_analytics = game_play->play_manual_game(1);
        break;
    case GameType::SIMULATE_HUMAN_VS_AI:
        game_analytics = game_play->play_manual_game(0);
        break;
    default:
        break;
    }

    game_analytics.print();
    return 0;
}