#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include "GameState.hpp"

class Heuristic
{
public:
    virtual int evaluate(GameState _game_state, int _player) = 0;
};

class Heuristic1 : public Heuristic
{
public:
    int evaluate(GameState _game_state, int _player);
};

class Heuristic2 : public Heuristic
{
public:
    int evaluate(GameState _game_state, int _player);
};

#endif