import collections

from Gamestate import GameState
from Move import Move

class Node(object):

    def __init__(self, state=None, parent=None, move=None):
        self.state = state
        self.parent = parent
        self.move = move

    def equals(self, rhs):
        return self.state.equals(rhs)

    def __str__(self):
        return self.move.string()

    def get_children(self):
        children = []
        moves = self.state.get_all_moves()
        for move in moves:
            new_state = self.state.copy()
            move.apply_move(new_state)
            child = Node(new_state, self, move)

            if not children:
                children.append(child)
            else:
                for c in children:
                    if c.move.piece == child.move.piece:
                        continue
                    else:
                        children.append(child)

        return children

def BreadthFirstSearch(state):
    open = []
    explored = []

    open.append(Node(state, None,  Move()))

    while open is not None:
        current = open.pop()
        if current.state.board in explored:
            continue

        explored.append(current.state.board)
        current.state.display_state()
        if current.state.puzzle_solved():
            return reconstruct_path(current)

        moves = current.state.get_all_moves()
        for move in moves:
            new_state = current.state.copy()
            move.apply_move(new_state)
            child = Node(new_state, current, move)
            open.append(child)
    
    return None

def DepthFirstSearch(state):
    open = []
    explored = []

    open.append(Node(state, None,  Move()))

    while open is not None:
        current = open.pop()
        if current.state.board in explored:
            continue

        explored.append(current.state.board)
        current.state.display_state()
        if current.state.puzzle_solved():
            return reconstruct_path(current)

        moves = current.state.get_all_moves()
        for move in moves:
            new_state = current.state.copy()
            move.apply_move(new_state)
            child = Node(new_state, current, move)
            open.insert(0, child)
    
    return None

#class IterativeDeepening(object):

def reconstruct_path(current):
    path = []

    while current.parent is not None:
        path.insert(0, current.move)
        current = current.parent

    return path

