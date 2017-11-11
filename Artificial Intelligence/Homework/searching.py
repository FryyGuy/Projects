import collections

from GameState import GameState
from Move import Move

class Node(object):

    def __init__(self, state=None, parent=None, move=None):
        self.state = state
        self.parent = parent
        self.move = move
        
        if not state:
            return
        else:
            self.g = 0
            self.h = self.state.mhd()
            self.f = self.g + self.h

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

        return children

def BreadthFirstSearch(state):
    open = []
    explored = []
    nodes = 0

    open.append(Node(state, None,  Move()))

    while open is not None:
        current = open.pop()
        if current.state.board in explored:
            continue

        nodes += 1
        explored.append(current.state.board)

        if current.state.puzzle_solved():
            return (reconstruct_path(current), nodes)

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
    nodes = 0

    while open is not None:
        current = open.pop()
        if current.state.board in explored:
            continue

        nodes += 1
        explored.append(current.state.board)

        if current.state.puzzle_solved():
            return (reconstruct_path(current), nodes)

        moves = current.state.get_all_moves()
        for move in moves:
            new_state = current.state.copy()
            move.apply_move(new_state)
            child = Node(new_state, current, move)
            open.insert(0, child)
    
    return None

#class IterativeDeepening(object):

def A_Star(state):
    open = []
    closed = []

    initial_state = Node(state, None, Move())
    open.append(initial_state)

    while open is not None:
        cost_list = []
        q = get_least_cost(open)

        if q.state.board in closed:
            continue
        if q.state.puzzle_solved():
            return reconstruct_path(q)

        closed.append(q.state.board)
        moves = q.state.get_all_moves()
       
        for move in moves:
            new_state = q.state.copy()
            move.apply_move(new_state)
            child = Node(new_state, q, move)

            if child.state.board in closed:
                continue
            if child.state.puzzle_solved():
                return reconstruct_path(child)
            child.g = q.g + 1

            if child.state.board not in closed:
                open.append(child)
            else:
                continue
    return None

def get_least_cost(states):
    if states[0] is None or states is None:
        return 0
    least = states[0]
    for s in states:
        if s.f < least.f or s.f <= least.f:
            least = s
            states.remove(s)

    return least

def cost_listing(states):
    clist = []
    for s in states:
        clist.append(s.f)

    return clist

def unique_list(states):
    return set(cost_listing(states))

def reconstruct_path(current):
    path = []

    while current.parent is not None:
        path.insert(0, current.move)
        current = current.parent

    return path

