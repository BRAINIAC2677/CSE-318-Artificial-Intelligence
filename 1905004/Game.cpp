#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

#include "Game.hpp"

#define MAX 1000000

Game::Game(int _player1_depth, int _player2_depth, Heuristic *_player1_heuristic, Heuristic *_player2_heuristic)
{
    this->move_count = 0;
    this->previous_game_state = GameState();
    this->current_game_state = GameState();
    this->next_game_state = GameState();
    this->player1_depth = max(1, _player1_depth);
    this->player2_depth = max(1, _player2_depth);
    this->player1_heuristic = _player1_heuristic;
    this->player2_heuristic = _player2_heuristic;
}

int Game::get_move_count()
{
    return this->move_count;
}

GameState Game::get_current_game_state()
{
    return this->current_game_state;
}

int Game::minimax_max(GameState _game_state, int _depth, int _alpha, int _beta)
{
    this->visited_node_count++;
    int depth = this->get_current_depth();
    Heuristic *heuristic = this->get_current_player_heuristic();
    if (_game_state.has_next_state() == false || _depth == depth)
    {
        return heuristic->evaluate(_game_state, this->current_game_state.get_current_player());
    }

    int alpha = _alpha;
    int beta = _beta;

    auto next_game_states = _game_state.get_next_game_states();
    random_device rd;
    mt19937 rd_engine(rd());
    shuffle(next_game_states.begin(), next_game_states.end(), rd_engine);

    for (auto next_game_state : next_game_states)
    {
        int score;
        if (next_game_state.get_current_player() == _game_state.get_current_player())
        {
            score = minimax_max(next_game_state, _depth + 1, alpha, beta);
        }
        else
        {
            score = minimax_min(next_game_state, _depth + 1, alpha, beta);
        }
        if (score > alpha)
        {
            if (_depth == 0)
            {
                this->next_game_state = next_game_state;
            }
            alpha = score;
        }
        if (alpha >= beta)
        {
            return alpha;
        }
    }
    return alpha;
}

int Game::minimax_min(GameState _game_state, int _depth, int _alpha, int _beta)
{
    this->visited_node_count++;
    int depth = this->get_current_depth();
    Heuristic *heuristic = this->get_current_player_heuristic();
    if (_game_state.has_next_state() == false || _depth == depth)
    {
        return heuristic->evaluate(_game_state, this->current_game_state.get_current_player());
    }

    int alpha = _alpha;
    int beta = _beta;

    auto next_game_states = _game_state.get_next_game_states();
    random_device rd;
    mt19937 rd_engine(rd());
    shuffle(next_game_states.begin(), next_game_states.end(), rd_engine);

    for (auto next_game_state : next_game_states)
    {
        if (next_game_state.get_current_player() == _game_state.get_current_player())
        {
            beta = min(beta, minimax_min(next_game_state, _depth + 1, alpha, beta));
        }
        else
        {
            beta = min(beta, minimax_max(next_game_state, _depth + 1, alpha, beta));
        }
        if (alpha >= beta)
        {
            return beta;
        }
    }
    return beta;
}

Heuristic *Game::get_current_player_heuristic()
{
    if (this->current_game_state.get_current_player() == 0)
    {
        return this->player1_heuristic;
    }
    else
    {
        return this->player2_heuristic;
    }
}

int Game::get_current_depth()
{
    if (this->current_game_state.get_current_player() == 0)
    {
        return this->player1_depth;
    }
    else
    {
        return this->player2_depth;
    }
}

bool Game::has_game_ended()
{
    return this->current_game_state.has_next_state() == false;
}

long long Game::make_move()
{
    if (this->has_game_ended())
    {
        return -1;
    }
    this->visited_node_count = 0;
    this->minimax_max(this->current_game_state, 0, -MAX, MAX);
    this->previous_game_state = this->current_game_state;
    this->current_game_state = this->next_game_state;
    this->move_count++;
    return this->visited_node_count;
}

long long Game::make_move(int _pit)
{
    if (this->has_game_ended())
    {
        return -1;
    }
    this->visited_node_count = 0;
    this->previous_game_state = this->current_game_state;
    this->current_game_state = this->current_game_state.get_next_game_state(_pit);
    this->move_count++;
    return this->visited_node_count;
}

int Game::get_player1_score()
{
    return this->current_game_state.get_mancala(0);
}

int Game::get_player2_score()
{
    return this->current_game_state.get_mancala(1);
}

int Game::get_game_winner()
{
    if (this->get_player1_score() > this->get_player2_score())
    {
        return 0;
    }
    else if (this->get_player1_score() < this->get_player2_score())
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void Game::print_stone(int _idx)
{
    if (this->current_game_state.get_board()[_idx] < this->previous_game_state.get_board()[_idx])
    {
        cout << "\033[1;31m" << this->current_game_state.get_board()[_idx] << "\033[0m"
             << " ";
    }
    else if (this->current_game_state.get_board()[_idx] > this->previous_game_state.get_board()[_idx])
    {
        cout << "\033[1;32m" << this->current_game_state.get_board()[_idx] << "\033[0m"
             << " ";
    }
    else
    {
        cout << this->current_game_state.get_board()[_idx] << " ";
    }
}

void Game::print_game_board()
{
    string divider = "\033[1;34m----------------------\033[0m";
    if (this->move_count != 0)
    {
        cout << "\n\033[1;34m"
             << "After move " << this->move_count << "\nSearched: " << this->visited_node_count << "\033[0m\n";
    }
    cout << divider << "\n    ";
    for (int i = 12; i >= 7; i--)
    {
        this->print_stone(i);
    }
    cout << "\n";
    this->print_stone(13);
    cout << "                 ";
    this->print_stone(6);
    cout << "\n    ";
    for (int i = 0; i < 6; i++)
    {
        this->print_stone(i);
    }
    cout << "\n"
         << divider << "\n";
}