from GameState import GameState
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


def BreadthFirstSearch(state, start, goal):
    open = []
    open.append(Node(start, None,  Move()))

    while open is not None:
        current = open.remove(0)
        if current.puzzle_solved():
            return reconstruct_path(current)

        moves = state.get_all_moves()
        for move in moves:
            child = Node(state, current, move)
            open.append(child)
    
   return None


def DepthFirstSearch(state, start, goal):
    open = []
    closed = []

    open.append(Node(start, None,  Move()))

    while open is not None:
        current = open.remove(0)
        if current.puzzle_solved():
            return reconstruct_path(current)
        closed.append(current)

        moves = state.get_all_moves()
        for move in moves:
            child = Node(state, current, move)
            if child not in closed:
                open.insert(0, child)
    
   return None

#class IterativeDeepening(object):

def reconstruct_path(current):
    path = []

    while current.parent is not None:
        path.insert(0, current.move)
        current = current.parent

    return path

