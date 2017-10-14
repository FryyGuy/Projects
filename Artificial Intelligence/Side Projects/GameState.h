#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Move.h"

#include <iostream>
#include <deque>

using namespace std;

//============================================================
/// @ Description - GameState represents an FSM for a game
///
/// @ Field <rows> - the number of rows on the board
/// @ Field <cols> - the number of columns on the board
/// @ Field <board> - a 2D array representing the board
//============================================================
class GameState
{
	private:

		int *rows;
		int *cols;

		int ** board;

		void create_board(deque<int> *);
		void create_board();

		void parse_csv(deque<int> *, const char *);

	public:

		// default constructor
		GameState()
		{
			this->rows = 0;
			this->cols = 0;

			create_board();
		}

		// copy constructor
		GameState(const GameState &state)
		{
			this->rows = state.rows;
			this->cols = state.cols;

			this->board = state.board;
		}

		//destructor
		~GameState()
		{
			//delete this->rows;
			//delete this->cols;

			// for(int i = 0; i < *this->rows; i++)
			// 	delete[] this->board[i];

			delete[] this->board;
		}

		//============================================================
		/// @ Description - enums for the possible moves
		//============================================================
		enum STATES
		{
			GOAL = -1,
			EMPTY,
			WALL,
			MASTER_BRICK
		};

		// getters / setters
		int get_rows() const
		{
			return *this->rows;
		}

		void set_rows(int r)
		{
			*this->rows = r;
		}

		int get_cols() const
		{
			return *this->cols;
		}

		void set_cols(int c)
		{
			*this->cols = c;
		}

		int get_board_elem(int i, int j) const
		{
			return this->board[i][j];
		}

		void set_board_elem(int e, int i, int j)
		{
			this->board[i][j] = e;
		}

		void swap_board_elems(int x1, int y1, int x2, int y2) const
		{
			int swap = this->board[x2][y2];

			this->board[x2][y2] = this->board[x1][y1];
			this->board[x1][y1] = swap;
		}

		// prototypes: see .c file for details
		void display_state(char *);
		void display_state() const;

		void load_state(const char *);

		void normalize() const;
		void swapIdx(int, int) const;

		bool puzzle_solved(GameState) const;
		bool puzzle_solved() const;

		deque<int> get_all_pieces() const;

		bool operator ==(const GameState &) const;

		bool random_walk(const GameState &, int) const;
};

#endif
