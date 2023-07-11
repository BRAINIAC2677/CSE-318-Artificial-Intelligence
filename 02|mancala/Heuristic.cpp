#include "Heuristic.hpp"

int Heuristic1::evaluate(GameState _game_state, int _player)
{
    return _game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player);
}

int Heuristic2::evaluate(GameState _game_state, int _player)
{
    return (_game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player)) + (_game_state.get_side(_player) - _game_state.get_side(1 - _player));
}