#!/usr/bin/python
import os
import sys
import random

from Gamestate import GameState
from Move import Move
from Coordinates import Coordinates

from searching import BreadthFirstSearch
from searching import DepthFirstSearch
from searching import Node

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

game_start = GameState()

game_start.load_state(user_level)

node = Node(game_start, None, None)
#children = node.get_children()
#for child in children:
#    print(str(child))
#moves = game_start.get_all_moves()
#for m in moves:
#    print(m.string())
path = BreadthFirstSearch(game_start)
for p in path:
    print(str(p.string()))
