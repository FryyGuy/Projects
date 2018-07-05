#include "Coordinates.h"
#include "GameState.h"

#include <deque>


//============================================================
/// @ Description - adjacent returns a list of coordinates
///					where piece is adjacent to element on
///					in relation to the board
///
/// @ param[in] <state> - the game state. Needed for board
/// @ param[in] <piece> - the piece to look at in question
/// @ param[in] <element> - the element to check for adjaceny
/// @ return <map<char, coords>> - a map where,
///								key = direction
///								value = coordinates and value
//============================================================
deque<Coordinates> Coordinates::zero_list(const GameState state, int piece)
{
	Coordinates piece_coords;
	deque<Coordinates> zero_list;

	for(int i = 0; i < state.get_rows(); i++)
	{
		for(int j = 0; j < state.get_cols(); j++)
		{
			// have to find piece coordinates
			if(state.get_board_elem(i, j) == piece)
			{
				piece_coords.set_x(i);
				piece_coords.set_y(j);
				piece_coords.set_value(state.get_board_elem(i, j));
			}

			// have to find 0 coordinates
			if(state.get_board_elem(i, j) == GameState::EMPTY)
			{
				int elem = state.get_board_elem(i, j);
				zero_list.push_back(Coordinates(elem, i, j));
			}
		}
	}

	return zero_list;

	// for(int i = 0; i < zero_list.size(); i++)
	// {
	// 	cout << "get here" << list.size() <<  endl;
	// 	if(piece_coords.is_up(zero_list.at(i)))
	// 		list.insert(pair<int, Coordinates>(0, zero_list.at(i)));
	// 	else if(piece_coords.is_down(zero_list.at(i)))
	// 		list.insert(pair<int, Coordinates>(1, zero_list.at(i)));
	// 	else if(piece_coords.is_left(zero_list.at(i)))
	// 		list.insert(pair<int, Coordinates>(2, zero_list.at(i)));
	// 	else if(piece_coords.is_right(zero_list.at(i)))
	// 		list.insert(pair<int, Coordinates>(3, zero_list.at(i)));
	// }
}

//============================================================
/// @ Description - returns true if an up move is free
///
/// @ param[in] <piece> - the pieces coordinates
/// @ param[in] <element> - the elements coordinates
/// @ return <bool> - true if up is free
//============================================================
bool Coordinates::is_up(Coordinates element)
{
	if(element.get_value() == 0 && element.get_y() > this->get_y())
		return true;
	else
		return false;
}

//============================================================
/// @ Description - returns true if a down move is free
///
/// @ param[in] <piece> - the pieces coordinates
/// @ param[in] <element> - the elements coordinates
/// @ return <bool> - true if down is free
//============================================================
bool Coordinates::is_down(Coordinates element)
{
	if(element.get_value() == 0 && element.get_y() < this->get_y())
		return true;
	else
		return false;
}

//============================================================
/// @ Description - returns true if a left move is free
///
/// @ param[in] <piece> - the pieces coordinates
/// @ param[in] <element> - the elements coordinates
/// @ return <bool> - true if left is free
//============================================================
bool Coordinates::is_left(Coordinates element)
{
	if(element.get_value() == 0 && element.get_x() < this->get_x())
		return true;
	else
		return false;
}

//============================================================
/// @ Description - returns true if a right move is free
///
/// @ param[in] <piece> - the pieces coordinates
/// @ param[in] <element> - the elements coordinates
/// @ return <bool> - true if right is free
//============================================================
bool Coordinates::is_right(Coordinates element)
{
	if(element.get_value() == 0 && element.get_x() > this->get_x())
		return true;
	else
		return false;
}
