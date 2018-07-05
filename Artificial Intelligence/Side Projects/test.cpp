#include "GameState.h"
#include "Move.h"
#include "Coordinates.h"

#include <iostream>
#include <iomanip>
#include <deque>
#include <string>

class Move;

using namespace std;
int main(int argc, char ** argv)
{
	deque<string> list_level;

	GameState state = GameState();
	GameState test_state;

	Move move = Move();

	string filename;
	string test_filename;

	if (argc < 2)
	{
		cout << "WARNING: NO FILE NAME GIVEN. USING => level0.txt" << endl;
		filename = "level0.txt";
	}
	else
		filename = argv[1];

	cout <<  setw(10) << "Welcome to the SBP A.I Test Demo" << endl;

	cout << setw(10) << "LOADING LEVEL " + filename << endl;
	state.load_state(filename.c_str());

	// DISPLAY STATE
	cout << endl;
	cout << setw(5) << "CURRENT STATE" << endl;
	state.display_state();

	cout << endl;
	cout << "TESTING IDENTITY EQUALITY TEST..." << endl;
	test_state = GameState(state);

	// EQUALITY CHECKS
	if(state == test_state)
		cout << "IDENTITY TEST PASSED" << endl;
	else
		cout << "IDENTITY TEST FAILED" << endl;

	// for some reason the board data gets overwritten after the equality check
	// for now just load the board state again
	state.load_state(filename.c_str());

	// DIFFERING STATE EQUALITY CHECKS
	cout << endl;
	cout << "LOADING LEVEL INTO TEST STATE..." << endl;

	test_filename = "level1.txt";
	test_state.load_state(test_filename.c_str());

	cout << "COMPARING " << test_filename << " AND " << filename << endl;

	if(state == test_state)
		cout << "IDENTITY TEST PASSED" << endl;
	else
		cout << "IDENTITY TEST FAILED" << endl;

	// PUZZLE SOLVER TEST
	cout << endl;
	cout << "TESTING PUZZLE SOLVER..." << endl;

	state.load_state(filename.c_str());

	if(state.puzzle_solved())
		cout << "PUZZLE SOLVED" << endl;
	else
		cout << "PUZZLE IS NOT SOLVED!" << endl;

	cout << endl;
	cout << "LOADING SOLVED LEVEL..." << endl;
	cout << "TESTING PUZZLE SOLVER..." << endl;

	test_filename = "level0_solved.txt";
	state.load_state(test_filename.c_str());

	if(state.puzzle_solved())
		cout << "PUZZLE SOLVED" << endl;
	else
		cout << "PUZZLE NOT SOLVED!" << endl;

	// NORMALILITY TEST
	cout << endl;
	cout << "TESTING NORMALITY..." << endl;

	test_filename = "un-normalized_state.txt";
	state.load_state(test_filename.c_str());
	state.normalize();

	test_state.load_state(test_filename.c_str());

	if (state == test_state)
		cout << "STATE NOT NORMALIZED" << endl;
	else
		cout << "STATE NORMALIZED" << endl;

	cout << "RESULTS: " << endl;
	state.display_state();

	// MOVEMENT TESTING
	cout << endl;
	state.load_state(filename.c_str());
	move.set_piece(3);
	move.set_direction(Move::LEFT);

	cout << "TESTING MOVEMENT OF ONE-SQUARE PIECE..." << endl;
	cout << "Moving piece " << move.get_piece() << " one space" << endl;

	cout << endl;
	move.apply_move(state, move);
	state.display_state();
	cout << endl;

	cout << "MOVING SAME PIECE IN ANOTHER DIRECTION..." << endl;
	move.set_direction(Move::RIGHT);

	cout << "NEW DIRECTION IS " << move.get_direction() << endl;
	move.apply_move(state, move);
	state.display_state();

	cout << endl;
	cout << "TESTING MULTI-BLOCK PIECE..." << endl;
	move.set_piece(2);
	move.set_direction(Move::LEFT);

	cout << endl;
	move.apply_move(state, move);
	state.display_state();
	cout << endl;

	cout << "MOVING SINGLE BLOCKS..." << endl;
	move.set_piece(4);
	move.set_direction(Move::DOWN);
	move.apply_move(state, move);

	move.set_piece(3);
	move.set_direction(Move::RIGHT);
	move.apply_move(state, move);

	cout << endl;
	state.display_state();
	cout << endl;

	cout << "TESTING MOVE MULTI-BLOCK..." << endl;
	move.set_piece(2);
	move.set_direction(Move::UP);
	move.apply_move(state, move);

	cout << endl;
	state.display_state();

	move.set_direction(Move::DOWN);
	move.apply_move(state, move);

	cout << endl;
	state.display_state();

	move.set_piece(3);
	move.set_direction(Move::LEFT);
	move.apply_move(state, move);

	cout << endl;
	state.display_state();

	move.set_piece(4);
	move.set_direction(Move::UP);
	move.apply_move(state, move);

	cout << endl;
	state.display_state();

	move.set_piece(2);
	move.set_direction(Move::RIGHT);

	move.print_move();

	cout << endl;
	cout << "TESTING APPLY_MOVE_CLONING..." << endl;

	//GameState cloned_state = move.apply_move_cloning(state, move);

	cout << endl;
	state.display_state();

	cout << endl;
	cout << "TESTING MOVE GENERATION..." << endl;

	//state.random_walk(state, 3);

	// cout << moves.size() << endl;

	// for(int i = 0; i < moves.size(); i++)
	// 	moves.at(i).print_move();

	cout << "Error here\n";

	return 0;
}
