#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
using namespace std;

class GameState
{
private:
    int current_player;
    vector<int> board;

public:
    GameState();

    int get_current_player();
    vector<int> get_board();
    void set_current_player(int _current_player);
    void set_board(vector<int> _board);

    int get_mancala(int _player);
    int get_side(int _player);

    bool has_next_state();
    vector<GameState> get_next_game_states();
};

#endif