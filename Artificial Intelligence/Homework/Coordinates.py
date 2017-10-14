#!/usr/bin/python
class Coordinates(object):

    # ========================================
    # @ Descipion - xy coordinate and value
    # ========================================
    def __init__(self, v, x, y):
        self.x = x
        self.y = y

        self.value = v

    # ========================================
    # @ Description - determines if up is free
    # @ param[in] <coords> - 0 coordinates
    # @ param[in] <state> - the game state
    # @ return <bool> true if up is free
    # ========================================
    def up_free(self, coords, state):
        board_elem = state.board[self.x - 1][self.y]

        if board_elem != 0:
            return False
        elif coords.y != self.y:
            return False
        elif coords.x > self.x:
            return False
        else:
            return True

    # ========================================
    # @ Description - determines if down is free
    # @ param[in] <coords> - 0 coordinates
    # @ param[in] <state> - the game state
    # @ return <bool> true if down is free
    # ========================================
    def down_free(self, coords, state):
        board_elem = state.board[self.x + 1][self.y]

        if board_elem != 0:
            return False
        elif coords.y != self.y:
            return False
        elif coords.x < self.x:
            return False
        else:
            return True

    # ========================================
    # @ Description - determines if left is free
    # @ param[in] <coords> - 0 coordinates
    # @ param[in] <state> - the game state
    # @ return <bool> true if left is free
    # ========================================
    def left_free(self, coords, state):
        board_elem = state.board[self.x][self.y - 1]

        if board_elem != 0:
            return False
        elif coords.x != self.x:
            return False
        elif coords.x > self.x:
            return False
        else:
            return True

    # ========================================
    # @ Description - determines if right is free
    # @ param[in] <coords> - 0 coordinates
    # @ param[in] <state> - the game state
    # @ return <bool> true if right is free
    # ========================================
    def right_free(self, coords, state):
        board_elem = state.board[self.x][self.y + 1]

        if board_elem != 0:
            return False
        elif coords.x != self.x:
            return False
        elif coords.x < self.x:
            return False
        else:
            return True
