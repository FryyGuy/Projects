#!/usr/bin/python
from Coordinates import Coordinates
from brick import Brick

UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3

class Move(object):

    # ========================================
    # @ Description - Movement object representation
    # ========================================
    def __init__(self, piece=-1, direction=-1, coords=None):
        self.piece = piece
        self.direction = direction
        self.coords = coords

    # ========================================
    # @ Description - applies this move to state
    # @ param[in] <state> - the state in question
    # @ return <void>
    # ========================================
    def apply_move(self, state):
        coord_list = self.get_piece_coords(state, self.piece)
        brick = Brick()
        brick.set_height_width(coord_list)

        valid = brick.check_move_valid(state, self)

        if valid == True:
            if self.direction == UP:
                for coord in coord_list:
                    x = coord.x
                    y = coord.y
                    if state.board[x - 1][y] == 0:
                        state.swap_board_elems(x, y, x - 1, y)
                    elif state.board[x - 1][y] == -1:
                        state.replace_zero(x, y, x - 1, y)

            if self.direction == DOWN:
                for coord in coord_list:
                    x = coord.x
                    y = coord.y
                    if state.board[x + 1][y] == 0:
                        state.swap_board_elems(x, y, x + 1, y)
                    elif state.board[x + 1][y] == -1:
                        state.replace_zero(x, y, x + 1, y)

            if self.direction == LEFT:
                for coord in coord_list:
                    x = coord.x
                    y = coord.y
                    if state.board[x][y - 1] == 0:
                        state.swap_board_elems(x, y, x, y - 1)
                    elif state.board[x][y - 1] == -1:
                        state.replace_zero(x, y, x, y - 1)

            # Have to reverse direction for right, as coordinates 
            # are naturally ordered from left to right. 
            # swapping right does not follow this behavior
            if self.direction == RIGHT:
                for coord in reversed(coord_list):
                    x = coord.x
                    y = coord.y
                    if state.board[x][y + 1] == 0:
                        state.swap_board_elems(x, y, x, y + 1)
                    elif state.board[x][y + 1] == -1:
                        state.replace_zero(x, y, x, y + 1)

    def check_move_valid(self, state):
        coord_list = self.get_piece_coords(state, self.piece)

        valid = True
        for coord in coord_list:
            x = coord.x
            y = coord.y

            if self.direction == UP:
                if state.board[x - 1][y] != 0:
                    valid = False
            if self.direction == DOWN:
                if state.board[x + 1][y] != 0:
                    valid = False
            if self.direction == LEFT:
                if state.board[x][y - 1] != 0\
                and state.board[x][y - 1] != coord.value:
                    valid = False
            if self.direction == RIGHT:
                if state.board[x][y + 1] != 0:
                    valid = False

    # ========================================
    # @ Description - applies move and clones state
    # @ param[in] <state> - the state in question
    # @ return <GameState>
    # ========================================
    def apply_move_cloning(self, state):
        new_state = state.copy()
        self.apply_move(state)
        return new_state

    # ========================================
    # @ Description - retrieves piece coords
    # @ param[in] <state> - the state to search
    # @ param[in] <piece> - the piece to look for
    # @ return <list<Coordinates>>
    # ========================================
    def get_piece_brick(self, state, piece):
        coord_list = []

        for i in range(0, state.rows):
            for j in range(0, state.cols):
                if state.board[i][j] == piece:
                    coord_list.append(Coordinates(piece, i, j))

        brick = Brick()
        brick.set_height_width(coord_list)

        return brick

    def get_piece_coords(self, state, piece):
        coord_list = []

        for i in range(0, state.rows):
            for j in range(0, state.cols):
                if state.board[i][j] == piece:
                    coord_list.append(Coordinates(piece, i, j))

        return coord_list

    # ========================================
    # @ Description - gets all zero coordinates
    # @ param[in] <state> - the state to search
    # @ return <list<Coordinates>>
    # ========================================
    def get_zero_coords(self, state):
        zero_list = []

        for i in range(0, state.rows):
            for j in range(0, state.cols):
                if state.board[i][j] == 0:
                    zero_list.append(Coordinates(0, i, j))

        return zero_list

    # ========================================
    # @ Description - gets all moves for piece
    # @ param[in] <state> - the state to search
    # @ return <list<Move>>
    # ========================================
    def get_piece_moves(self, state, piece):
        piece_coords = self.get_piece_coords(state, piece)

        move_list = []

        for p_coords in piece_coords:
            if p_coords.up_free(state):
                move_list.append(Move(p_coords.value, UP, p_coords))
            elif p_coords.down_free(state):
                move_list.append(Move(p_coords.value, DOWN, p_coords))
            elif p_coords.left_free(state):
                move_list.append(Move(p_coords.value, LEFT, p_coords))
            elif p_coords.right_free(state):
                move_list.append(Move(p_coords.value, RIGHT, p_coords))

        brick = self.get_piece_brick(state, piece)

        for move in move_list:
            if brick.check_move_valid(state, move) == False:
                move_list.remove(move)

        return move_list

    # ========================================
    # @ Description - gets all available moves
    # @ param[in] <state> - the state in question
    # @ return <list<Move>>
    # ========================================
    def get_all_moves(self, state):
        pieces = state.get_all_pieces()
        all_move_list = []

        for piece in pieces:
            piece_move_list = self.get_piece_moves(state, piece)

            if piece_move_list is None:
                all_move_list.append(str(piece) + " has no moves")
            else:
                for move in piece_move_list:
                    all_move_list.append(move)

        return all_move_list

    # ========================================
    # @ Description - prints out a move
    # ========================================
    def string(self):
        if self.direction == UP:
            print("(" + str(self.piece) + ", up)")
        elif self.direction == DOWN:
            print("(" + str(self.piece) + ", down)")
        elif self.direction == LEFT:
            print("(" + str(self.piece) + ", left)")
        elif self.direction == RIGHT:
            print("(" + str(self.piece) + ", right)")
