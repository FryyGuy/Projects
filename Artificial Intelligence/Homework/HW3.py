import os
import sys
import random

import time

from GameState import GameState
from Move import Move
from Coordinates import Coordinates

from searching import BreadthFirstSearch
from searching import DepthFirstSearch
from searching import A_Star

user_level = None
alg = None
if len(sys.argv) != 3:
    print("ERROR: INCORRECT NUMBER OF ARGS. EXPECT: <level> <algorithm>")
else:
    user_level = sys.argv[1]
    alg = sys.argv[2]

selected_func = None
if alg == "bfs":
    selected_func = BreadthFirstSearch
elif alg == "dfs":
    selected_func = DepthFirstSearch
elif alg == "astar":
    selected_func = A_Star

game_start = GameState()

game_start.load_state(user_level)

start_1 = time.time()
search_info = selected_func(game_start)
end_1 = time.time() - start_1

print("Solution:\n")
for m in search_info:
    print(m.string())
print("A-Star Time for " + str(user_level) +  ": " + str(end_1))
