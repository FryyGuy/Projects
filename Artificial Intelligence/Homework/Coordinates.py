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
    # @ param[in] <state> - the game state
    # @ return <bool> true if up is free
    # ========================================
    def up_free(self, state, x=None, y=None):
        cx = 0
        cy = 0
        if x == None and y == None:
            cx = self.x - 1
            cy = self.y
        else:
            cx = x
            cy = y

        board_elem = state.board[cx][cy]

        if board_elem == self.value:
            return self.up_free(state, cx - 1, cy)
        elif board_elem == 0:
            return True
        else:
            return False

    # ========================================
    # @ Description - determines if down is free
    # @ param[in] <state> - the game state
    # @ return <bool> true if down is free
    # ========================================
    def down_free(self, state, x=None, y=None):
        cx = 0
        cy = 0
        if x == None and y == None:
            cx = self.x + 1
            cy = self.y
        else:
            cx = x
            cy = y

        board_elem = state.board[cx][cy]

        if board_elem == self.value:
            return self.down_free(state, cx + 1, cy)
        elif board_elem == 0:
            return True
        else:
            return False

    # ========================================
    # @ Description - determines if left is free
    # @ param[in] <state> - the game state
    # @ return <bool> true if left is free
    # ========================================
    def left_free(self, state, x=None, y=None):
        cx = 0
        cy = 0
        if x == None and y == None:
            cx = self.x
            cy = self.y - 1
        else:
            cx = x
            cy = y

        board_elem = state.board[cx][cy]

        if board_elem == self.value:
            return self.left_free(state, cx, cy - 1)
        elif board_elem == 0:
            return True
        else:
            return False

    # ========================================
    # @ Description - determines if right is free
    # @ param[in] <state> - the game state
    # @ return <bool> true if right is free
    # ========================================
    def right_free(self, state, x=None, y=None):
        cx = 0
        cy = 0
        if x == None and y == None:
            cx = self.x
            cy = self.y + 1
        else:
            cx = x
            cy = y

        board_elem = state.board[cx][cy]

        if board_elem == self.value:
            return self.right_free(state, cx, cy + 1)
        elif board_elem == 0:
            return True
        else:
            return False
