#include <iostream>
#include <cassert>
using namespace std;

#include "GameState.hpp"

GameState::GameState()
{
    current_player = 0;
    board = vector<int>(14, 4);
    board[6] = board[13] = 0;
    bonus_move_count.assign(2, 0);
    captured_stone_count.assign(2, 0);
}

GameState &GameState::operator=(const GameState &_game_state)
{
    current_player = _game_state.current_player;
    board = _game_state.board;
    bonus_move_count = _game_state.bonus_move_count;
    captured_stone_count = _game_state.captured_stone_count;
    return *this;
}

int GameState::get_current_player()
{
    return current_player;
}

vector<int> GameState::get_board()
{
    return board;
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

int GameState::get_bonus_move_count(int _player)
{
    return bonus_move_count[_player];
}

int GameState::get_captured_stone_count(int _player)
{
    return captured_stone_count[_player];
}

void GameState::set_current_player(int _current_player)
{
    current_player = _current_player;
}

void GameState::set_board(vector<int> _board)
{
    board = _board;
}
bool GameState::has_next_state()
{
    return this->get_next_game_states().size() > 0;
}

bool GameState::is_valid_move(int _pit)
{
    if (_pit < 7 * this->get_current_player() || _pit >= 6 + 7 * this->get_current_player())
    {
        return false;
    }
    if (this->board[_pit] == 0)
    {
        return false;
    }
    return true;
}

GameState GameState::get_next_game_state(int _pit)
{
    assert(this->is_valid_move(_pit));
    int current_index = _pit;
    GameState next_game_state = *this;
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
    if (current_index < 6 + current_player * 7 && current_index >= 7 * current_player && next_game_state.board[current_index] == 1 && next_game_state.board[12 - current_index] != 0)
    {
        next_game_state.board[6 + current_player * 7] += next_game_state.board[12 - current_index] + 1;
        next_game_state.captured_stone_count[current_player] += next_game_state.board[12 - current_index] + 1;
        next_game_state.board[current_index] = 0;
        next_game_state.board[12 - current_index] = 0;
    }
    if (this->get_side(1 - current_player) == 0 && this->get_side(current_player) != 0)
    {
        for (int i = 0; i < 6; i++)
        {
            next_game_state.board[6 + current_player * 7] += next_game_state.board[i + current_player * 7];
            next_game_state.board[i + current_player * 7] = 0;
        }
    }
    if (this->get_side(current_player) == 0 && this->get_side(1 - current_player) != 0)
    {
        for (int i = 0; i < 6; i++)
        {
            next_game_state.board[6 + current_player * 7] += next_game_state.board[i + current_player * 7];
            next_game_state.board[i + current_player * 7] = 0;
        }
    }
    if (current_index == 6 + current_player * 7 && next_game_state.get_side(current_player))
    {
        next_game_state.current_player = current_player;
        next_game_state.bonus_move_count[current_player]++;
    }
    else
    {
        next_game_state.current_player = 1 - current_player;
    }
    return next_game_state;
}

vector<GameState> GameState::get_next_game_states()
{
    vector<GameState> next_game_states;
    for (int i = 0; i < 6; i++)
    {
        if (this->is_valid_move(i + current_player * 7))
        {
            next_game_states.push_back(this->get_next_game_state(i + current_player * 7));
        }
    }
    return next_game_states;
}
