#include <iostream>
using namespace std;

#include "GameAnalytics.hpp"

GameAnalytics::GameAnalytics()
{
    this->games = vector<Game>();
}

void GameAnalytics::add_game(Game _game)
{
    this->games.push_back(_game);
}

int GameAnalytics::get_game_count()
{
    return this->games.size();
}

int GameAnalytics::get_draw_count()
{
    int draw_count = 0;
    for (int i = 0; i < this->get_game_count(); i++)
    {
        if (this->games[i].get_game_winner() == -1)
        {
            draw_count++;
        }
    }
    return draw_count;
}

int GameAnalytics::get_player1_win_count()
{
    int player1_win_count = 0;
    for (int i = 0; i < this->get_game_count(); i++)
    {
        if (this->games[i].get_game_winner() == 0)
        {
            player1_win_count++;
        }
    }
    return player1_win_count;
}

int GameAnalytics::get_player2_win_count()
{
    int player2_win_count = 0;
    for (int i = 0; i < this->get_game_count(); i++)
    {
        if (this->games[i].get_game_winner() == 1)
        {
            player2_win_count++;
        }
    }
    return player2_win_count;
}

float GameAnalytics::get_player1_win_percentage()
{
    return (float)this->get_player1_win_count() / (float)this->get_game_count() * 100;
}

float GameAnalytics::get_player2_win_percentage()
{
    return (float)this->get_player2_win_count() / (float)this->get_game_count() * 100;
}

void GameAnalytics::print()
{
    string divider = "----------------------------------------";

    cout << "\033[1;34m\nGame Analytics\033[0m"
         << "\n"
         << divider << "\n";
    cout << "Game Count: " << this->get_game_count() << "\n";
    cout << "Draw Count: " << this->get_draw_count() << "\n"
         << divider << "\n";
    cout << "Player 1 Win Count: " << this->get_player1_win_count() << "\n";
    cout << "Player 1 Win Percentage: " << this->get_player1_win_percentage() << "%"
         << "\n"
         << divider << "\n";
    cout << "Player 2 Win Count: " << this->get_player2_win_count() << "\n";
    cout << "Player 2 Win Percentage: " << this->get_player2_win_percentage() << "%"
         << "\n\n";
}
