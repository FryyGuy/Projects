#!/usr/bin/python
from math import fabs
from Move import Move
from brick import Brick
import copy
from random import randint

GOAL = -1
EMPTY = 0
WALL = 1
MASTER_BRICK = 2

class GameState(object):

    # ========================================
    # @ Description - FSM Object representation
    # ========================================
    def __init__(self):
        self.rows = 0
        self.cols = 0
        self.board = []

    # ========================================
    # @ Description - copy construtor
    # ========================================
    def copy(self):
        #state = GameState()
        #state.rows = self.rows
        #state.cols = self.cols
        #state.board = self.board
        state = copy.deepcopy(self)

        return state

    # ========================================
    # @ Description - loads a state from file
    # @ param[in] <filename> - file to load
    # @ return <void>
    # ========================================
    def load_state(self, filename):

        if self.board is not None:
            del self.board[:]

        # read
        with open(filename) as f:
            content = f.readlines()

        # parse
        board_data = []
        for line in content:
            data = line.rstrip(",\r\n")
            board_data.append(data.split(','))

        # get rows and cols
        matrix_data = board_data[0]
        self.cols = int(matrix_data[0])
        self.rows = int(matrix_data[1])

        board_data.remove(matrix_data)

        # and we got a board
        for line in board_data:
            self.board.append(list(map(int, line)))

    # ========================================================
    # @ Description - calculates manhattan distance to goal
    #               from position of master brick
    # @ return <integer> - the distance to goal from master
    # ========================================================
    def mhd(self):
        x_goal = 0
        y_goal = 0

        move = Move()
        tar_coords = move.get_piece_coords(self, 2)
        dest_coords = move.get_piece_coords(self, -1)

        x_tar = tar_coords[0].x
        y_tar = tar_coords[0].y

        if not dest_coords:
            return 0
        else:
            x_goal = dest_coords[0].x
            y_goal = dest_coords[0].y

        x_diff = fabs(x_tar - x_goal)
        y_diff = fabs(y_tar - y_goal)

        return x_diff + y_diff

    def manhattan_distance(self, node):
        move = Move()

        node_mhd = node.state.mhd()
        self_mhd = self.mhd()

        mhd_diff = fabs(self_mhd - node_mhd)

        return mhd_diff



    # ========================================
    # @ Description - swaps two indexes
    # @ param[in] <idx1> - index1
    # @ param[in] <idx2> - index 2
    # @ return <void>
    # ========================================
    def swapIdx(self, idx1, idx2):
        for i in range(0, self.rows):
            for j in range(0, self.cols):
                if self.board[i][j] == idx1:
                    self.board[i][j] = idx2
                elif self.board[i][j] == idx2:
                    self.board[i][j] = idx1


    # ========================================
    # @ Description - normalizes board
    # @ return <void>
    # ========================================
    def normalize(self):
        next_idx = 3
        for i in range(0, self.rows):
            for j in range(0, self.cols):
                if self.board[i][j] == next_idx:
                    next_idx += 1
                elif self.board[i][j] > next_idx:
                    self.swapIdx(next_idx, self.board[i][j])

    # ========================================
    # @ Description - determines if puzzel is solved
    # @ return <bool> - true if solved.
    # ========================================
    def puzzle_solved(self):
        for i in range(0, self.rows):
            for j in range(0, self.cols):
                if self.board[i][j] == -1:
                    return False
        return True

    # ========================================
    # @ Description - Generates all moves,
    #               picks and executes n moves.
    # @ param[in] <n> - number of moves to execute
    # @ return <bool> - true if puzzle is solved
    # ========================================
    def random_walk(self, n):
        solved = -1

        initial_moves = self.get_all_moves()

        for i in range(0, n):
            solved = self.puzzle_solved()

            if solved == True:
                break
            else:
                rand_num = randint(0, len(initial_moves) - 1)

                move = initial_moves[rand_num]
                move.apply_move(self)

                move.string()
                self.display_state()
                print("\n")

                self.normalize()
                initial_moves = self.get_all_moves()

        return solved

    # ========================================
    # @ Description - determines if two states are equal
    # @ param[in] <rhs> - ride side state
    # @ return <bool> - true if states are equals
    # ========================================
    def equals(self, rhs):
        if rhs.rows != self.rows or rhs.cols != self.cols:
            return False
        else:
            for i in range(0, self.rows):
                for j in range(0, self.cols):
                    if rhs.board[i][j] != self.board[i][j]:
                        return False
        return True

    # ========================================
    # @ Description - swaps elems at indexes
    # @ params [x1, y1] - first elem coordinates
    # @ params [x2, y2] - second elem coordinates
    # @ return <void>
    # ========================================
    # swap board elements
    def swap_board_elems(self, x1, y1, x2, y2):
        swap = self.board[x2][y2]

        self.board[x2][y2] = self.board[x1][y1]
        self.board[x1][y1] = swap

    # ========================================
    # @ Description - calls swap and sets to zero_list
    # @ return <void>
    # ========================================
    def replace_zero(self, x1, y1, x2, y2):
        self.swap_board_elems(x1, y1, x2, y2)
        self.board[x1][y1] = 0

    # ========================================
    # @ Description - gets all board pieces
    # @ return <list<int>>
    # ========================================
    def get_all_pieces(self):
        pieces = []
        for i in range(0, self.rows):
            for j in range(0, self.cols):
                if self.board[i][j] == GOAL\
                or self.board[i][j] == EMPTY\
                or self.board[i][j] == WALL:
                    continue
                else:
                    pieces.append(self.board[i][j])

        return pieces

    # ========================================
    # @ Description - gets all available moves
    # @ param[in] <state> - the state in question
    # @ return <list<Move>>
    # ========================================
    def get_all_moves(self):
        pieces = list(set(self.get_all_pieces()))
        all_move_list = []

        for piece in pieces:
            piece_move_list = Move()
            piece_move_list = piece_move_list.get_piece_moves(self, piece)

            if piece_move_list is None:    
                all_move_list.append(str(piece) + " has no moves")
            else:
                for move in piece_move_list:
                    all_move_list.append(move)

        return all_move_list

    # ========================================
    # @ Description - displays a state
    # @ return <void>
    # ========================================
    def display_state(self):

        print("============================")
        for i in range(0, self.rows):
            print(self.board[i])
        print("============================")
