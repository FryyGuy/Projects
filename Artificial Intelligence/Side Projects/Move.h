#ifndef MOVE_H
#define MOVE_H

#include "GameState.h"
#include "Coordinates.h"

// #include <deque>
#include <map>

using namespace std;

//============================================================
/// @ Description - represents a Move on a game_board
///
/// @ Field <piece> - the piece in question
/// @ Field <direction> - the direction to move
//============================================================
class Move
{
	private:
		int piece;
		int direction;
		Coordinates coords;

		// deque<Move> move_list;

	public:

		// default constructor
		Move()
		{
			this->piece = 0;
			this->direction = '#';
		}

		// Basic constructor
		Move(int &piece, const int &direction, Coordinates &coords)
		{
			this->piece = piece;
			this->direction = direction;
			this->coords = coords;
		}

		// destructor
		~Move()
		{}

		// basic getters and setters
		int get_piece() const
		{
			return this->piece;
		}

		void set_piece(int p)
		{
			this->piece = p;
		}

		int get_direction() const
		{
			return this->direction;
		}

		void set_direction(int d)
		{
			this->direction = d;
		}

		Coordinates get_coords() const
		{
			return this->coords;
		}

		void set_coordinates(Coordinates c)
		{
			this->coords = c;
		}

		//============================================================
		/// @ Description - enums for the possible moves
		//============================================================
		enum MOVES
		{
			UP = 1,
			DOWN = 2,
			LEFT = 3,
			RIGHT = 4
		};

		// prototypes: see .c file for details
		deque<Move> get_piece_moves(const GameState&, int) const;
		deque<Move> get_all_moves(const GameState&) const;

		void print_move();
		void print_all_moves(const GameState) const;

		void apply_move(const GameState&, Move) const;
		GameState apply_move_cloning(const GameState &, Move) const;
};

#endif
