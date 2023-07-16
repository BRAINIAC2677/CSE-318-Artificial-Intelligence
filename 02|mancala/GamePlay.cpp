#include <iostream>
using namespace std;

#include "GamePlay.hpp"

GamePlay::GamePlay()
{
    this->player1_depth = 5;
    this->player2_depth = 5;
    this->player1_heuristic = new Heuristic1();
    this->player2_heuristic = new Heuristic2();
}

GamePlay *GamePlay::set_player1_depth(int _player1_depth)
{
    this->player1_depth = max(1, _player1_depth);
    return this;
}

GamePlay *GamePlay::set_player2_depth(int _player2_depth)
{
    this->player2_depth = max(1, _player2_depth);
    return this;
}

GamePlay *GamePlay::set_player1_heuristic(Heuristic *_player1_heuristic)
{
    this->player1_heuristic = _player1_heuristic;
    return this;
}

GamePlay *GamePlay::set_player2_heuristic(Heuristic *_player2_heuristic)
{
    this->player2_heuristic = _player2_heuristic;
    return this;
}

int GamePlay::get_player1_depth()
{
    return this->player1_depth;
}

int GamePlay::get_player2_depth()
{
    return this->player2_depth;
}

Heuristic *GamePlay::get_player1_heuristic()
{
    return this->player1_heuristic;
}

Heuristic *GamePlay::get_player2_heuristic()
{
    return this->player2_heuristic;
}

Game GamePlay::play_game()
{
    Game game = Game(this->player1_depth, this->player2_depth, this->player1_heuristic, this->player2_heuristic);
    while (game.has_game_ended() == false)
    {
        game.make_move();
    }
    return game;
}

Game GamePlay::simulate_game()
{
    cout << "simulation\n";
    Game game = Game(this->player1_depth, this->player2_depth, this->player1_heuristic, this->player2_heuristic);
    while (game.has_game_ended() == false)
    {
        game.print_game_board();
        game.make_move();
    }
    game.print_game_board();
    return game;
}

GameAnalytics GamePlay::play_manual_game(int _human_player)
{
    Game game = Game(this->player1_depth, this->player2_depth, this->player1_heuristic, this->player2_heuristic);
    while (game.has_game_ended() == false)
    {
        game.print_game_board();
        if (game.get_current_game_state().get_current_player() == _human_player)
        {
            int pit;
            while (cin >> pit)
            {
                if (game.get_current_game_state().is_valid_move(pit))
                {
                    game.make_move(pit);
                    break;
                }
                cout << "Invalid move.\nValid moves for current player are:\n";
                for (int i = 0; i < 14; i++)
                {
                    if (game.get_current_game_state().is_valid_move(i))
                    {
                        cout << i << " ";
                    }
                }
                cout << "\n";
            }
        }
        else
        {
            game.make_move();
        }
    }
    game.print_game_board();
    GameAnalytics game_analytics;
    game_analytics.add_game(game);
    return game_analytics;
}

GameAnalytics GamePlay::play_games(int _game_count)
{
    GameAnalytics game_analytics;
    for (int i = 0; i < _game_count; i++)
    {
        Game game = this->play_game();
        game_analytics.add_game(game);
    }
    return game_analytics;
}

GameAnalytics GamePlay::simulate_games(int _game_count)
{
    GameAnalytics game_analytics;
    for (int i = 0; i < _game_count; i++)
    {
        cout << "\nGame " << i + 1 << "\n";
        Game game = this->simulate_game();
        game_analytics.add_game(game);
        cout << "Game " << i + 1 << " ended\n";
        cout << "Player 1 score: " << game.get_player1_score() << "\n";
        cout << "Player 2 score: " << game.get_player2_score() << "\n";
    }
    return game_analytics;
}
