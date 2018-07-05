#!/usr/bin/python
import os
import sys
import random

from GameState import GameState
from Move import Move
from Coordinates import Coordinates

user_level = ""
if sys.argv < 2 or sys.argv > 2:
    print("ERROR: Invalid arguments passed.")
    print("Expected: ./test LEVEL_FILE.txt\n")
    print("Using default level0.txt")
else:
    user_level = sys.argv[1]

level_files = [filename for filename in os.listdir('.') if "level" in filename]
if user_level == "":
    user_level = [level for level in level_files if level.find("0") >= 0][0]

print user_level

random_level = random.choice(level_files)

game = GameState()
test_game = GameState()

move = Move(-1, -1, None)

print("\n")
print("Loading Level...")
print("Done!")
game.load_state(user_level)
game.display_state()

print("\n")
print("Comparing differing Levels...")
test_game.load_state(random_level)
test_game.display_state()

if game.equals(test_game):
    print("Level 1 and Level 2 are the same")
else:
    print("Level 1 and Level 2 are different")

print("\n")
print("Testing Puzzle Solver...")
if game.puzzle_solved():
    print("Level 1 Solved!\n")
else:
    print("Level 1 Not Solved!")

print("\n")
print("Loading valid solved puzzle...")
game.load_state("solved.txt")
game.display_state()

if game.puzzle_solved():
    print("Puzzle Solved! Congratulations!\n")
else:
    print("Level 1 not solved...\n")

print("\n")
print("Checking Normality...")
game.load_state("un-normalized_state.txt")
game.display_state()
game.normalize()

print("\n")
print("Normalized State Achieved!\n")
game.display_state()

print("\n")
print("Testing Moves...")
game.load_state(user_level)

# do enough moves to get a winning board and check again for solved
move.piece = 2
move.direction = 2

move.apply_move(game)
game.display_state()

move.piece = 4
move.direction = 1

move.apply_move(game)
game.display_state()

move.piece = 3
move.direction = 3

move.apply_move(game)
game.display_state()

move.piece = 2
move.direction = 0

move.apply_move(game)
game.display_state()

move.piece = 4
move.direction = 3

move.apply_move(game)
game.display_state()

move.piece = 3
move.direction = 1

move.apply_move(game)
game.display_state()

move.piece = 2
move.direction = 3

move.apply_move(game)
game.display_state()

print("\n")
print("Testing Apply Move Cloning...")
new_state = move.apply_move_cloning(game)

print("\n")
print("Calling display from Clone...")
new_state.display_state()

move.apply_move(new_state)
new_state.display_state()

if new_state.puzzle_solved():
     print("Level 1 Solved! Congratulations!")
else:
    print("Level 1 not Solved!")

print("\n")
print("Testing Move Generation...")
new_state.load_state(random_level)
new_state.display_state()

move.piece = 3
move_list = move.get_piece_moves(new_state, move.piece)

print("Possible moves for piece " + str(move.piece) + " ...\n")
if move_list is None:
    print("No moves available for " + str(move.piece))
else:
    for move in move_list:
        move.string()

print("\n")
print("Getting all moves for the board...")
all_moves = move.get_all_moves(new_state)

print("All available moves: ")
if all_moves is None:
    print("No moves")
else:
    for move in all_moves:
        move.string()

print("\n")
print("Testing Random Walking for 5 iterations")
print("Original Board")
new_state.display_state()

print("\n")
print("Walking...")
new_state.random_walk(5)
