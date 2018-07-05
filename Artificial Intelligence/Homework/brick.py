#!/usr/bin/python
from Coordinates import Coordinates


# ==================================================
# @ Description - represents a collection of bricks
# ==================================================
class Brick(object):

    # ==================================================
    # @ Description - representation of a brick
    # @ Field <length> - list of coordinates for length
    # @ Field <width> - list of coordiantes for width
    # @ Field <coords> - the coordinates for the brick
    # ==================================================
    def __init__(self):
        self.height = []
        self.width = []
        self.coords = None

    def get_piece_brick(self, state, piece):
        coord_list = []

        for i in range(0, state.rows):
            for j in range(0, state.cols):
                if state.board[i][j] == piece:
                    coord_list.append(Coordinates(piece, i, j))

        brick = Brick()
        brick.coords = coord_list
        brick.set_height_width(coord_list)

        return brick

    def set_height_width(self, coords):
        xs = [c.x for c in coords]
        ys = [c.y for c in coords]

        curx = coords[0].x
        for coord in coords:
            if curx == coord.x:
                self.width.append(coord)
            else:
                self.height.append(coord)

            curx = coord.x

    def check_move_valid(self, state, move):
        valid = True
        valid_listing = []
        if move.direction == 0:
            for coord in self.width:
                valid = coord.up_free(state)
                valid_listing.append(valid)
            for coord in self.height:
                valid = coord.up_free(state)
                valid_listing.append(valid)

            for v in valid_listing:
                if v == False:
                    valid = False

        if move.direction == 1:
            for coord in reversed(self.width):
                valid = coord.down_free(state)
                valid_listing.append(valid)
            for coord in reversed(self.height):
                valid = coord.down_free(state)
                valid_listing.append(valid)

            for v in valid_listing:
                if v == False:
                    valid = False

        if move.direction == 2:
            for coord in self.width:
                valid = coord.left_free(state)
                valid_listing.append(valid)
            for coord in self.height:
                valid = coord.left_free(state)
                valid_listing.append(valid)

            for v in valid_listing:
                if v == False:
                    valid = False

        if move.direction == 3:
            for coord in reversed(self.width):
                valid = coord.right_free(state)
                valid_listing.append(valid)
            for coord in reversed(self.height):
                valid = coord.right_free(state)
                valid_listing.append(valid)

            for v in valid_listing:
                if v == False:
                    valid = False

        return valid
