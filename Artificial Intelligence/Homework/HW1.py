#!/usr/bin/python
import os
import sys
import random

from GameState import GameState
from Move import Move
from Coordinates import Coordinates

user_level = ""
n_walks = 0
if len(sys.argv) < 3:
    print("ERROR: Invalid arguments passed.")
    print("Expected: ./test LEVEL_FILE.txt\n")
    print("Using default level0.txt")
else:
    user_level = sys.argv[1]
    n_walks = sys.argv[2]

level_files = [filename for filename in os.listdir('.') if "level" in filename]
if user_level == "":
    user_level = [level for level in level_files if level.find("0") >= 0][0]

random_level = random.choice(level_files)

game = GameState()
test_game = GameState()

game.load_state(user_level)
game.random_walk(int(n_walks))
