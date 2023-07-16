#ifndef GAME_HPP
#define GAME_HPP

#include "Heuristic.hpp"

class Game
{
private:
    int move_count;
    int player1_depth;
    int player2_depth;
    int visited_node_count;
    GameState previous_game_state;
    GameState current_game_state;
    GameState next_game_state;
    Heuristic *player1_heuristic;
    Heuristic *player2_heuristic;

    int minimax_max(GameState _game_state, int _depth, int _alpha, int _beta);
    int minimax_min(GameState _game_state, int _depth, int _alpha, int _beta);
    Heuristic *get_current_player_heuristic();
    int get_current_depth();
    void print_stone(int _idx);

public:
    Game(int _player1_depth, int _player2_depth, Heuristic *_player1_heuristic, Heuristic *_player2_heuristic);
    int get_move_count();
    GameState get_current_game_state();
    bool has_game_ended();
    long long make_move();
    long long make_move(int _pit);
    int get_player1_score();
    int get_player2_score();
    int get_game_winner();
    void print_game_board();
};

#endif