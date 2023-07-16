#include "Heuristic.hpp"

int Heuristic1::evaluate(GameState _game_state, int _player)
{
    int w1 = 1;
    return w1 * _game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player);
}

int Heuristic2::evaluate(GameState _game_state, int _player)
{
    int w1 = 20;
    int w2 = 1;
    return w1 * (_game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player)) + w2 * (_game_state.get_side(_player) - _game_state.get_side(1 - _player));
}

int Heuristic3::evaluate(GameState _game_state, int _player)
{
    int w1 = 40;
    int w2 = 2;
    int w3 = 4;
    return w1 * (_game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player)) + w2 * (_game_state.get_side(_player) - _game_state.get_side(1 - _player)) + w3 * _game_state.get_bonus_move_count(_player);
}

int Heuristic4::evaluate(GameState _game_state, int _player)
{
    int w1 = 40;
    int w2 = 2;
    int w3 = 4;
    int w4 = 1;
    return w1 * (_game_state.get_mancala(_player) - _game_state.get_mancala(1 - _player)) + w2 * (_game_state.get_side(_player) - _game_state.get_side(1 - _player)) + w3 * _game_state.get_bonus_move_count(_player) + w4 * _game_state.get_captured_stone_count(_player);
}
