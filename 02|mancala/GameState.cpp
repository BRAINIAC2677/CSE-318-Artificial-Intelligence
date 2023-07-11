#include <iostream>
using namespace std;

#include "GameState.hpp"

GameState::GameState()
{
    current_player = 0;
    board = vector<int>(14, 4);
    board[6] = 0;
    board[13] = 0;
}

int GameState::get_current_player()
{
    return current_player;
}

vector<int> GameState::get_board()
{
    return board;
}

void GameState::set_current_player(int _current_player)
{
    current_player = _current_player;
}

void GameState::set_board(vector<int> _board)
{
    board = _board;
}

int GameState::get_mancala(int _player)
{
    return board[6 + _player * 7];
}

int GameState::get_side(int _player)
{
    int side = 0;
    for (int i = 0; i < 6; i++)
    {
        side += board[i + _player * 7];
    }
    return side;
}

bool GameState::has_next_state()
{
    return this->get_next_game_states().size() > 0;
}

vector<GameState> GameState::get_next_game_states()
{
    vector<GameState> next_game_states;
    if (this->get_side(1 - current_player) == 0 && this->get_side(current_player) != 0)
    {
        GameState next_game_state = *this;
        for (int i = 0; i < 6; i++)
        {
            next_game_state.board[6 + current_player * 7] += next_game_state.board[i + current_player * 7];
            next_game_state.board[i + current_player * 7] = 0;
        }
        next_game_state.current_player = current_player;
        next_game_states.push_back(next_game_state);
        return next_game_states;
    }
    for (int i = 0; i < 6; i++)
    {
        if (board[i + current_player * 7] != 0)
        {
            GameState next_game_state = *this;
            int current_index = i + current_player * 7;
            int current_value = next_game_state.board[current_index];
            next_game_state.board[current_index] = 0;
            while (current_value > 0)
            {
                current_index = (current_index + 1) % 14;
                if (current_index == 6 + (1 - current_player) * 7)
                {
                    continue;
                }
                next_game_state.board[current_index]++;
                current_value--;
            }
            if (current_index == 6 + current_player * 7 && next_game_state.get_side(current_player))
            {
                next_game_state.current_player = current_player;
            }
            else
            {
                next_game_state.current_player = 1 - current_player;
            }
            next_game_states.push_back(next_game_state);
        }
    }
    return next_game_states;
}
