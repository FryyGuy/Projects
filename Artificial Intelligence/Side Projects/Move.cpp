#include "Move.h"

class Cooridnates;
class GameState;

#include <iostream>
#include <map>

//============================================================
/// @ Description - generates all moves for a given piece
///
/// @ param[in] <state> - the board state
/// @ param[in] <piece> - the piece to consider
/// @ return<deque<move>> - the move_list
//============================================================
deque<Move> Move::get_piece_moves(const GameState &state, int piece) const
{
	deque<Move> move_list;
	Coordinates piece_coords;

	deque<Coordinates> zero_list = Coordinates::zero_list(state, piece);
	cout << "zero list size " << zero_list.size() << endl;
	for(int i = 0; i < state.get_rows(); i++)
	{
		for(int j = 0; j < state.get_cols(); j++)
		{
			cout << "state " << &state << endl;
			int elem = state.get_board_elem(i, j);
			cout << "piece move error2\n";
			if(state.get_board_elem(i, j) == piece)
			{
				piece_coords.set_value(piece);
				piece_coords.set_x(i);
				piece_coords.set_y(j);

				zero_list.push_back(piece_coords);
			}
		}
	}

	for(int i = 0; i < zero_list.size(); i++)
	{
		Move move;
		if (piece_coords.is_up(zero_list.at(i)))
			move = Move(piece, Move::UP, piece_coords);
		else if (piece_coords.is_down(zero_list.at(i)))
			move = Move(piece, Move::DOWN, piece_coords);
		else if (piece_coords.is_left(zero_list.at(i)))
			move = Move(piece, Move::LEFT, piece_coords);
		else if (piece_coords.is_right(zero_list.at(i)))
			move = Move(piece, Move::RIGHT, piece_coords);

		move_list.push_back(move);
	}

	return move_list;
}

//============================================================
/// @ Description - returns all moves for a given board state
///
/// @ param[in] <state> - the state to consider
/// @ return <deque<Move>> - a deque of all moves
//============================================================
deque<Move> Move::get_all_moves(const GameState &state) const
{
	cout << "ge here\n";
	deque<int> pieces = state.get_all_pieces();

	deque<Move> piece_move_list;

	for(int i = 0; i < pieces.size(); i++)
	{
		cout << "get here\n";
		deque<Move> piece_move_list = Move::get_piece_moves(state, pieces.at(i));

		// cout << "Adj List size " << zero_list.size() << endl;
		// for(map<int, Coordinates>::iterator iter = adjacent_list.begin(); iter != adjacent_list.end(); ++iter)
		// {
		// 	Move new_move = Move(pieces.at(i), iter->first, iter->second);
		// 	this->move_list.push_back(new_move);
		// }
	}

	return piece_move_list;
}

//============================================================
/// @ Description - apply_move applies the move to the state
///
/// @ param[in] <state> - the state to apply move to
/// @ param[in] <move> - the move to apply_move
/// @ return <void>
//============================================================
void Move::apply_move(const GameState &state, Move move) const
{
	int target = move.get_piece();
	deque<Coordinates> coordinate_list;

	for (int i = 0; i < state.get_rows(); i++)
		for(int j = 0; j < state.get_cols(); j++)
			if(state.get_board_elem(i, j) == target)
				coordinate_list.push_back(Coordinates(target, i, j));

	// shift the piece the appropriate amount
	for(int i = 0; i < coordinate_list.size(); i++)
	{
		Coordinates coord = coordinate_list.at(i);

		int x = coord.get_x();
		int y = coord.get_y();

		if(state.get_board_elem(x, y) == move.get_piece()
		|| state.get_board_elem(x, y) == GameState::EMPTY)
		{
			if(move.get_direction() == Move::UP
			&& state.get_board_elem((x - 1), y) == GameState::EMPTY)
				state.swap_board_elems(x, y, x - 1, y);

			if(move.get_direction() == Move::DOWN
			&& state.get_board_elem((x + 1), y) == GameState::EMPTY)
				state.swap_board_elems(x, y, x + 1, y);

			if(move.get_direction() == Move::LEFT
			&& state.get_board_elem(x, (y - 1)) == GameState::EMPTY)
				state.swap_board_elems(x, y, x, y - 1);

			if(move.get_direction() == Move::RIGHT
			&& state.get_board_elem(x, (y + 1)) == GameState::EMPTY)
				state.swap_board_elems(x, y, x, y + 1);
		}
	}
}

//============================================================
/// @ Description - clones the given state and applies the move
///
/// @ param[in] <state> - the state to clone and apply move to
/// @ param[in] <move> - the move to apply
/// @ return <GameState> - a new state with the applied move
//============================================================
GameState Move::apply_move_cloning(const GameState &state, Move move) const
{
	GameState new_state = GameState(state);

	move.apply_move(new_state, move);

	return new_state;
}

//============================================================
/// @ Description - print move formats and prints the move
///
/// @ return <void>
//============================================================
void Move::print_move()
{
	if(this->direction == Move::UP)
		cout << "(" << this->piece << ", " << "up" << ")" << endl;
	else if(this->direction == Move::DOWN)
		cout << "(" << this->piece << ", " << "down" << ")" << endl;
	else if(this->direction == Move::LEFT)
		cout << "(" << this->piece << ", " << "left" << ")" << endl;
	else if(this->direction == Move::RIGHT)
		cout << "(" << this->piece << ", " << "right" << ")" << endl;
}

//============================================================
/// @ Description - prints all moves for state
///
/// @ param[in] <state> - the state in question
/// @ return <void>
//============================================================
void Move::print_all_moves(const GameState state) const
{
	Move move;
	cout << "Error here\n";
	deque<Move> moves = move.get_all_moves(state);

	for(int i = 0; i < moves.size(); i++)
		moves.at(i).print_move();
}
