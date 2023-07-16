#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
using namespace std;

class GameState
{
private:
    int current_player;
    vector<int> board;
    vector<int> bonus_move_count;
    vector<int> captured_stone_count;

public:
    GameState();
    GameState &operator=(const GameState &_game_state);
    int get_current_player();
    vector<int> get_board();
    int get_mancala(int _player);
    int get_side(int _player);
    int get_bonus_move_count(int _player);
    int get_captured_stone_count(int _player);

    void set_current_player(int _current_player);
    void set_board(vector<int> _board);

    bool has_next_state();
    bool is_valid_move(int _pit);
    GameState get_next_game_state(int _pit);
    vector<GameState> get_next_game_states();
};

#endif