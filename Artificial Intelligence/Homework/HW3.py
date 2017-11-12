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
all_levels = [filename for filename in os.listdir('.') if "SBP-level" in filename]

alg = None
if len(sys.argv) != 3:
    alg = sys.argv[1]
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

if user_level is not None:
    game_start.load_state(user_level)

    start_1 = time.time()
    search_info = selected_func(game_start)
    end_1 = time.time() - start_1

    print("Solution:\n")
    for m in search_info:
        print(m.string())
    print("A-Star Time for " + str(user_level) +  ": " + str(end_1))
    #print("Number of Nodes visited: " + str(search_info[1]))
    sys.exit()
else:
    for f in all_levels:
        game_start.load_state(f)

        start_1 = time.time()
        search_info = selected_func(game_start)
        end_1 = time.time() - start_1

        outfile = open("output-hw3.txt", "a")

        outfile.write("Solution:\n")
        for m in search_info[0]:
            outfile.write(m.string())
        outfile.write("A-Star Time for " + str(f) +  ": " + str(end_1) + "\n")
        outfile.write("Number of Nodes visited: " + str(search_info[1]) + "\n")
        outfile.write("Solution Length: " + str(len(search_info[0])) + "\n")
        print("Done Level: " + str(f) + "\n")


sys.exit()
