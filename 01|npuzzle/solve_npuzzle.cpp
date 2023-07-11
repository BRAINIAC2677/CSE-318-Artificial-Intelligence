#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
using namespace std;

class Board
{
private:
    int dimension;
    vector<vector<int>> grid;
    Board *parent;

public:
    Board();
    int get_dimension();
    vector<vector<int>> get_grid();
    Board *get_parent();
    Board *set_dimension(int _dimension);
    Board *set_grid(vector<vector<int>> _grid);
    Board *set_parent(Board *_parent);
    vector<int> get_linear_grid();
    int get_number_of_inversions();
    int get_blank_row_number(bool _from_last = true);
    bool is_solvable();
    int get_hamming_distance();
    int get_manhattan_distance();
    bool has_same_grid_as(vector<vector<int>> _other_grid);
    pair<int, int> get_blank_indices();
    vector<Board *> get_reachable_boards();
    bool is_goal_board();
    friend istream &operator>>(istream &_stream, Board &_board);
    friend ostream &operator<<(ostream &_stream, Board &_board);
};

Board::Board()
{
    this->parent = nullptr;
}

int Board::get_dimension()
{
    return this->dimension;
}

vector<vector<int>> Board::get_grid()
{
    return this->grid;
}

Board *Board::get_parent()
{
    return this->parent;
}

Board *Board::set_dimension(int _dimension)
{
    this->dimension = _dimension;
    return this;
}

Board *Board::set_grid(vector<vector<int>> _grid)
{
    this->grid = _grid;
    return this;
}

Board *Board::set_parent(Board *_parent)
{
    this->parent = _parent;
    return this;
}

vector<int> Board::get_linear_grid()
{
    vector<int> linear_grid;
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            linear_grid.push_back(this->grid[i][j]);
        }
    }
    return linear_grid;
}

int Board::get_number_of_inversions()
{
    vector<int> linear_grid = this->get_linear_grid();

    int number_of_inversions = 0, linear_grid_size = linear_grid.size();
    for (int i = 0; i < linear_grid_size; i++)
    {
        for (int j = i + 1; j < linear_grid_size; j++)
        {
            if (linear_grid[i] > 0 && linear_grid[j] > 0)
            {
                number_of_inversions += (linear_grid[j] < linear_grid[i]);
            }
        }
    }
    return number_of_inversions;
}

int Board::get_blank_row_number(bool _from_last)
{
    int blank_row;
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            if (this->grid[i][j] == 0)
            {
                blank_row = i + 1;
                break;
            }
        }
    }

    if (_from_last)
    {
        blank_row = this->dimension + 1 - blank_row;
    }
    return blank_row;
}

bool Board::is_solvable()
{
    if (this->dimension & 1)
    {
        return (this->get_number_of_inversions() % 2 == 0);
    }
    else
    {
        if (((this->get_blank_row_number() % 2 == 0) && (this->get_number_of_inversions() & 1)) || ((this->get_blank_row_number() & 1) && (this->get_number_of_inversions() % 2 == 0)))
        {
            return true;
        }
        return false;
    }
}

int Board::get_hamming_distance()
{
    int hamming_distance = 0;
    vector<int> linear_grid = this->get_linear_grid();
    for (int i = 0; i < linear_grid.size(); i++)
    {
        hamming_distance += (linear_grid[i] > 0 && linear_grid[i] != i + 1);
    }
    return hamming_distance;
}

int Board::get_manhattan_distance()
{
    int manhattan_distance = 0;
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            if (this->grid[i][j] > 0)
            {
                int value = this->grid[i][j] - 1;
                int expected_row = value / this->dimension;
                int expected_col = value % this->dimension;
                manhattan_distance += (abs(expected_row - i) + abs(expected_col - j));
            }
        }
    }
    return manhattan_distance;
}

bool Board::has_same_grid_as(vector<vector<int>> _other_grid)
{
    if (_other_grid.size() != _other_grid[0].size() || this->dimension != _other_grid[0].size())
    {
        return false;
    }

    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            if (this->grid[i][j] != _other_grid[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

pair<int, int> Board::get_blank_indices()
{
    pair<int, int> indices = {-1, -1};
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            if (this->grid[i][j] == 0)
            {
                indices = {i, j};
            }
        }
    }
    return indices;
}

vector<Board *> Board::get_reachable_boards()
{
    vector<Board *> reachable_boards;
    vector<pair<int, int>> delta_xy = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    pair<int, int> blank_indices = this->get_blank_indices();
    for (auto dxy : delta_xy)
    {
        pair<int, int> new_xy = {blank_indices.first + dxy.first, blank_indices.second + dxy.second};
        if (new_xy.first < 0 || new_xy.first >= this->dimension || new_xy.second < 0 || new_xy.second >= this->dimension)
        {
            continue;
        }
        auto new_grid = this->get_grid();
        swap(new_grid[blank_indices.first][blank_indices.second], new_grid[new_xy.first][new_xy.second]);
        if (this->get_parent() != nullptr && this->get_parent()->has_same_grid_as(new_grid))
        {
            continue;
        }
        Board *new_board = new Board();
        new_board->set_dimension(this->get_dimension());
        new_board->set_grid(new_grid);
        new_board->set_parent(this);
        reachable_boards.push_back(new_board);
    }
    return reachable_boards;
}

bool Board::is_goal_board()
{
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            if (this->grid[i][j] > 0 && this->grid[i][j] != i * this->dimension + j + 1)
            {
                return false;
            }
        }
    }
    return true;
}

istream &operator>>(istream &_stream, Board &_board)
{
    _stream >> _board.dimension;
    _board.grid.assign(_board.dimension, vector<int>(_board.dimension));
    for (int i = 0; i < _board.dimension; i++)
    {
        for (int j = 0; j < _board.dimension; j++)
        {
            _stream >> _board.grid[i][j];
        }
    }
    return _stream;
}

ostream &operator<<(ostream &_stream, Board &_board)
{
    _stream << "\n";
    for (int i = 0; i < _board.dimension; i++)
    {
        for (int j = 0; j < _board.dimension; j++)
        {
            _stream << _board.grid[i][j] << " \n"[j == _board.dimension - 1];
        }
    }
    return _stream;
}

void solve_npuzzle_hamming(Board *_initial_board, ostream &_cout = cout)
{

    if (!_initial_board->is_solvable())
    {
        _cout << "Unsolvable puzzle\n";
    }
    else
    {
        priority_queue<pair<int, Board *>, vector<pair<int, Board *>>, greater<pair<int, Board *>>> hamming_queue;
        int number_of_moves = 0, number_of_explored_boards = 0, number_of_expanded_boards = 0;
        Board *goal_board = nullptr;
        hamming_queue.push({_initial_board->get_hamming_distance(), _initial_board});
        while (!hamming_queue.empty())
        {
            Board *current_board = hamming_queue.top().second;
            int simple_distance = hamming_queue.top().first - current_board->get_hamming_distance();
            hamming_queue.pop();
            if (current_board->is_goal_board())
            {
                goal_board = current_board;
                break;
            }
            number_of_expanded_boards++;
            auto reachable_boards = current_board->get_reachable_boards();
            for (auto reachable_board : reachable_boards)
            {
                hamming_queue.push({simple_distance + 1 + reachable_board->get_hamming_distance(), reachable_board});
                number_of_explored_boards++;
            }
        }
        Board *current_move = goal_board;
        stack<Board *> moves;
        while (current_move != nullptr)
        {
            moves.push(current_move);
            current_move = current_move->get_parent();
        }
        number_of_moves = int(moves.size()) - 1;
        _cout << "\nMinimum number of moves: " << number_of_moves << "\nNumber of explored boards: " << number_of_explored_boards << "\nNumber of expanded boards: " << number_of_expanded_boards << "\n";
        while (!moves.empty())
        {
            _cout << *moves.top();
            moves.pop();
        }
    }
}

void solve_npuzzle_manhattan(Board *_initial_board, ostream &_cout = cout)
{
    if (!_initial_board->is_solvable())
    {
        _cout << "Unsolvable puzzle\n";
    }
    else
    {
        priority_queue<pair<int, Board *>, vector<pair<int, Board *>>, greater<pair<int, Board *>>> manhattan_queue;
        int number_of_moves = 0, number_of_explored_boards = 0, number_of_expanded_boards = 0;
        Board *goal_board = nullptr;
        manhattan_queue.push({_initial_board->get_manhattan_distance(), _initial_board});
        while (!manhattan_queue.empty())
        {
            Board *current_board = manhattan_queue.top().second;
            int simple_distance = manhattan_queue.top().first - current_board->get_manhattan_distance();
            manhattan_queue.pop();
            if (current_board->is_goal_board())
            {
                goal_board = current_board;
                break;
            }
            number_of_expanded_boards++;
            auto reachable_boards = current_board->get_reachable_boards();
            for (auto reachable_board : reachable_boards)
            {
                manhattan_queue.push({simple_distance + 1 + reachable_board->get_manhattan_distance(), reachable_board});
                number_of_explored_boards++;
            }
        }
        Board *current_move = goal_board;
        stack<Board *> moves;
        while (current_move != nullptr)
        {
            moves.push(current_move);
            current_move = current_move->get_parent();
        }
        number_of_moves = int(moves.size()) - 1;
        _cout << "\nMinimum number of moves: " << number_of_moves << "\nNumber of explored boards: " << number_of_explored_boards << "\nNumber of expanded boards: " << number_of_expanded_boards << "\n";
        // _cout << "\nMinimum number of moves: " << number_of_moves << "\n";
        while (!moves.empty())
        {
            _cout << *moves.top();
            moves.pop();
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    Board *initial_board = new Board();
    cin >> (*initial_board);
    // solve_npuzzle_hamming(initial_board);
    solve_npuzzle_manhattan(initial_board);
    return 0;
}