import os
import sys
import time

from GameState import GameState
from Move import Move
from Coordinates import Coordinates
from searching import Node
from searching import BreadthFirstSearch
from searching import DepthFirstSearch

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


game_start = GameState()

game_start.load_state(user_level)
game_start.display_state()

test_level = GameState()
test_level.load_state(user_level)

move = Move(2, 2, None)
move.apply_move(test_level)
test_level.display_state()

node = Node(test_level, None, None)


#start_1 = time.time()
#search_info = selected_func(game_start)
#end_1 = time.time() - start_1

#print("Solution:\n")
#for m in search_info[0]:
#    print(m.string())
#print("Breadth First Search Time for " + str(user_level) +  ": " + str(end_1))
#print("Number of Nodes visited: " + str(search_info[1]))