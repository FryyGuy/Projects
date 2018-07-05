#include "GameState.h"
class Move;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

//============================================================
/// @ Description - display_state displays the game board_data
///					of the filename given
///
/// @ param[in] <filename> - the filename referencing the game
/// @ return <void>
//============================================================
void GameState::display_state(char *filename)
{
	string line;
	ifstream input(filename, ios::in);

	cout << "===============================" << endl;
	if(input.is_open())
	{
		while(!input.eof())
		{
			getline(input, line);
			cout << setw(5) << line << endl;
		}
	}
	cout << "===============================" << endl;
}

//============================================================
/// @ Description - display_state displays the game board_data
///					this state object's board
///
/// @ return <void>
//============================================================
void GameState::display_state() const
{
	cout << "===============================" << endl;
	for (int i = 0; i < this->get_rows(); i++)
	{
		for (int j = 0; j < this->get_cols(); j++)
			cout << setw(5) << this->board[i][j];

		cout << endl;
	}
	cout << "===============================" << endl;
}

//============================================================
/// @ Description - load_state loads the game state from file
///
/// @ param[in] <filename> - the file to load from
/// @ return <void>
//============================================================
void GameState::load_state(const char *filename)
{
	deque<int> *board_data = new deque<int>();
	parse_csv(board_data, filename);

	// first and second characters are the matrix dimensions
	this->rows = new int;
	this->cols = new int;

	// set and pop...
	this->set_cols(board_data->front());
	board_data->pop_front();

	this->set_rows(board_data->front());
	board_data->pop_front();

	this->create_board(board_data);
}

//============================================================
/// @ Description - creates the baord for the game
///
/// @ param[in] <board> - the game board to be allocated
/// @ return <void>
//============================================================
void GameState::create_board(deque<int> *board_data)
{
	int row = 0, col = 0, i = 0;
	int total = this->get_rows() * this->get_cols();

	//this creates our 2D board as a deque of a deque of ints
	// shooouuuulllllddd be memory efficient. We'll see.
	this->board = new int*[this->get_rows()];
	for(i = 0; i < this->get_rows(); i++)
		this->board[i] = new int[this->get_cols()];

	// loop over the board data and assign it to the 2d array
	for (i = 0; i < this->get_rows(); i++)
	{
		for (int j = 0; j < this->get_cols(); j++)
		{
			int linear_index = (j % this->get_cols()) + (i * this->get_cols());
			this->board[i][j] = board_data->at(linear_index);
		}
	}
}

//============================================================
/// @ Description - creates the baord for the game

/// @ return <void>
//============================================================
void GameState::create_board()
{
	//this creates our 2D board as a deque of a deque of ints
	// shooouuuulllllddd be memory efficient. We'll see.
	this->board = new int*[this->get_rows()];
	for(int i = 0; i < this->get_rows(); i++)
		this->board[i] = new int[this->get_cols()];
}

//============================================================
/// @ Description - parses the game board from the file
///
/// @ param[in] <board> - the csv to parse
/// @ return <void>
//============================================================
void GameState::parse_csv(deque<int> *board_data, const char *filename)
{
	string line;
	ifstream input(filename);

	// For practical purposes, assume file to be CSV
	// Have to parse out data first
	if (input.is_open())
	{
		while (!input.eof())
		{
			getline(input, line);
			stringstream line_stream(line);

			string cell;
			while (getline(line_stream, cell, ','))

				// stupid fucking carriage returns
				if(cell[0] != '\r' && cell[0] != '\n')
					board_data->push_back(atoi(cell.c_str()));
		}
	}
}

//============================================================
/// @ Description - normalizes the state
///
/// @ return<void>
//============================================================
void GameState::normalize() const
{
	int next_idx = 3;
	for(int i = 0; i < this->get_rows(); i++)
	{
		for(int j = 0; j < this->get_cols(); j++)
		{
			if(this->board[j][i] == next_idx)
				next_idx++;
			else if(this->board[j][i] > next_idx)
			{
				this->swapIdx(next_idx, this->board[j][i]);
				next_idx++;
			}
		}
	}
}

//============================================================
/// @ Description - swaps numbers to create normal state
///
/// @ param[in] <idx1> - the first number
/// @ param[in] <idx2> - the second number
/// @return <void>
//============================================================
void GameState::swapIdx(int idx1, int idx2) const
{
	for(int i = 0; i < this->get_rows(); i++)
	{
		for(int j = 0; j < this->get_cols(); j++)
		{
			if(this->board[j][i] == idx1)
				this->board[j][i] = idx2;
			else if(this->board[j][i] == idx2)
				this->board[j][i] = idx1;
		}
	}
}

//============================================================
/// @ Description - overloaded equals
///
/// @ param[in] <rhs> - the right hand side to compare to
/// @ return <bool>
//============================================================
bool GameState::operator ==(const GameState &rhs) const
{
	if(this->get_rows() != rhs.get_rows()
	|| this->get_cols() != rhs.get_cols())
		return false;

	// int total_elems = this->get_rows() * this->get_cols();
	// if(memcmp(this->board, rhs.board, total_elems) == 0)
	// 	return false;
	for(int i = 0; i < this->get_rows(); i++)
		for(int j = 0; j < this->get_cols(); j++)
			if(this->get_board_elem(i, j) != rhs.get_board_elem(i, j))
				return false;

	return true;
}

//============================================================
/// @ Description - determines if the puzzle has been solved
///
/// @ param[in] <state> - not sure why we need this yet
/// @ return <bool> - true if any piece is a -1
//============================================================
bool GameState::puzzle_solved(GameState state) const
{
	for (int i = 0; i < state.get_rows(); i++)
		for (int j = 0; j < state.get_cols(); j++)
			if (state.get_board_elem(i, j) == -1)
				return false;

	return true;
}

//============================================================
/// @ Description - determines if the puzzle has been solved
///
/// @ return <bool> - true if any piece is a -1
//============================================================
bool GameState::puzzle_solved() const
{
	for (int i = 0; i < this->get_rows(); i++)
		for (int j = 0; j < this->get_cols(); j++)
			if (this->board[i][j] == -1)
				return false;

	return true;
}

//============================================================
/// @ Description - attempts N moves on state until n is hit
///					or the goal state is reached.
///
///	@ param[in] <state> - the state to run on
/// @ param[in] <num_rounds> - number of moves to make
/// @ return <bool> - true if puzzle is solved
//============================================================
bool GameState::random_walk(const GameState &state, int num_moves) const
{
	int solved = false;

	Move move = Move();
	deque<Move> all_moves = move.get_all_moves(state);

	int rand_num;
	for(int i = 0; i < num_moves; i++)
	{
		solved = state.puzzle_solved();
		rand_num = rand() % (all_moves.size() - 1) + 1;

		Move move = all_moves.at(rand_num);
		move.apply_move(state, move);
		state.normalize();

		// print stuff
		move.print_move();
		state.display_state();
	}

	return solved;
}

//============================================================
/// @ Description - gets all the pieces on the board
///
/// @ return <deque<int>> - a deque of all pieces
//============================================================
deque<int> GameState::get_all_pieces() const
{
	deque<int> pieces;

	for(int i = 0; i < this->get_rows(); i++)
	{
		for(int j = 0; j < this->get_cols(); j++)
		{
			if(this->board[i][j] == GameState::GOAL || this->board[i][j] == GameState::EMPTY
			|| this->board[i][j] == GameState::WALL)
				continue;
			else
				pieces.push_back(this->board[i][j]);
		}
	}

	return pieces;
}
