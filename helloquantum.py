# Author: Rafael Goncalves
# File: helloquantum.py
# Description: Main file for the Hello Quantum game


# ADT cell
def create_cell(val):
    '''
    create_cell: {1, 0, 1} -> cell
    ADT cell constructor: returns a cell in accordance with input
    Internal representation is a list with the value
    '''
    if val in (-1, 0, 1):
        return [val]

    else:
        raise ValueError("create_cell: invalid argument.")


def get_value(c):
    '''
    get_value: cell  -> {1, 0, 1}
    Returns cell state value
    '''
    return c[0]


def invert_state(c):
    '''
    invert_state: cell -> cell
    Inverts cell state
    '''
    c[0] = (-1, 1, 0)[get_value(c) + 1]

    return c


def is_cell(arg):
    '''
    is_cell: universal -> boolean
    Returns True if arg is a cell
    '''
    return arg in ([-1], [0], [1])


def equal_states(c1, c2):
    '''
    equal_states: cell x cell -> boolean
    Returns True if both cells are in the same state
    '''
    return is_cell(c1) and is_cell(c2) and c1 == c2


def cell_to_str(c):
    '''
    cell_to_str: cell -> string
    Returns the external representation of a cell in the form of a string
    '''
    return ("x", "0", "1")[get_value(c) + 1]


# ADT coord
def create_coord(r, c):
    '''
    create_coord: n x n -> coord
    ADT coord constructor: returns a coordinate in accordance with input
    Internal representation is a tuple in the format (row, column)
    '''
    if r in (0, 1, 2) and c in (0, 1, 2):
        return r, c

    else:
        raise ValueError("create_coord: invalid arguments.")


def get_row_from_coord(c):
    '''
    get_row_from_coord: coord -> n
    Returns coord row
    '''
    return c[0]


def get_column_from_coord(c):
    '''
    get_column_from_coord: coord -> n
    Returns coord column
    '''
    return c[1]


def is_coord(arg):
    '''
    is_coord: universal -> boolean
    Returns True if arg is a coord
    '''
    return isinstance(arg, tuple) and len(arg) == 2 and arg[0] in (0, 1, 2) and arg[1] in (0, 1, 2)


def equal_coords(c1, c2):
    '''
    equal_coords: coord x coord -> boolean
    Returns True if two coords are the same
    '''
    return is_coord(c1) and is_coord(c2) and c1 == c2


def coord_to_str(c):
    '''
    coord_to_str: coord -> string
    Returns the external representation of a coord in the form of a string
    '''
    return "(" + str(get_row_from_coord(c)) + ", " + str(get_column_from_coord(c)) + ")"


# ADT board
def board_aux(arg):
    '''
    board_aux: list -> board
    Transforms numeric values in cells given a blueprint for a board
    '''
    return list(list(map(create_cell, l)) for l in arg)      # Maps create_cell to all members of the list


def get_pos(coord):
    '''
    get_pos: coord -> pos
    Returns a position in the board given a coord
    '''
    if get_row_from_coord(coord) == 2:         # Adjusts column if coord is in the last row
        return get_row_from_coord(coord), get_column_from_coord(coord) - 1

    else:
        return get_row_from_coord(coord), get_column_from_coord(coord)


def init_board():
    '''
    init_board: {} -> board
    Returns the initial board
    '''
    return board_aux([[-1, -1, -1], [0, 0, -1], [0, -1]])


def str_to_board(s):
    '''
    str_to_board: string -> board
    Creates a new board given a string (must be a tuple of tuples)
    '''
    if isinstance(s, str) and isinstance(eval(s), tuple) and len(eval(s)) == 3 and \
       all(isinstance(e, tuple) for e in eval(s)) and \
       len(eval(s)[0]) == 3 and len(eval(s)[1]) == 3 and len(eval(s)[2]) == 2 and \
       all(all(map(lambda x: x in (-1, 0, 1), l)) for l in eval(s)):
        return board_aux(eval(s))

    else:
        raise ValueError("str_to_board: invalid argument.")


def board_dim(b):
    '''
    board_dim: board -> n
    Returns the number of rows (likewise, columns) in a board
    '''
    return len(b)


def board_cell(b, coord):
    '''
    board_cell: board x coord -> cell
    Returns a cell given a board and a coord
    '''
    pos = get_pos(coord)

    return b[pos[0]][pos[1]]


def is_board(arg):
    '''
    is_board: universal -> boolean
    Returns True if arg is a board
    '''
    return isinstance(arg, list) and len(arg) == 3 and all(isinstance(e, list) for e in arg) and \
           len(arg[0]) == 3 and len(arg[1]) == 3 and len(arg[2]) == 2 and all(all(map(is_cell, l)) for l in arg)


def board_change_cell(b, cell, coord):
    '''
    board_change_cell: board x cell x coord -> board
    Changes the contents of the specified position to cell
    '''
    if is_board(b) and is_cell(cell) and is_coord(coord) and coord != create_coord(2, 0):
        pos = get_pos(coord)
        b[pos[0]][pos[1]] = cell

        return b

    else:
        raise ValueError("board_change_cell: invalid arguments.")


def board_invert_state(b, coord):
    '''
    board_invert_state: board x coord -> board
    Inverts the cell in the given position
    '''
    if is_board(b) and is_coord(coord) and coord != create_coord(2, 0):
        pos = get_pos(coord)
        b[pos[0]][pos[1]] = invert_state(board_cell(b, coord))

        return b

    else:
        raise ValueError("board_invert_state: invalid arguments.")


def equal_boards(b1, b2):
    '''
    equal_boards: board x board -> boolean
    Returns True if the boards are similar
    '''
    return is_board(b1) and is_board(b2) and b1 == b2


def board_to_str(t):
    '''
    board_to_str: board -> string
    Returns the external representation of a board in the form of a string
    '''
    board_cel = list(list(map(cell_to_str, l)) for l in t)        # Transforms the cells in strings

    board_str = "+-------+\n" + \
              "|..." + board_cel[0][2] + "...|\n" + \
              "|.." + board_cel[0][1] + "." + board_cel[1][2] + "..|\n" + \
              "|." + board_cel[0][0] + "." + board_cel[1][1] + "." + board_cel[2][1] + ".|\n" + \
              "|.." + board_cel[1][0] + "." + board_cel[2][0] + "..|\n" + \
              "+-------+"

    return board_str


# Gates
def x_gate(b, g):
    '''
    x_gate: b x {"L", "R"} -> board
    Applies the X gate to the specified side
    '''
    if is_board(b) and (g == "L" or g == "R"):
        if b == "L":
            for j in range(board_dim(b)):
                board_invert_state(b, create_coord(1, j))

        else:
            for i in range(board_dim(b)):
                board_invert_state(b, create_coord(i, 1))

        return b
    else:
        raise ValueError("x_gate: invalid arguments.")


def z_gate(b, g):
    '''
    z_gate: board x {"L", "R"} -> board
    Applies the Z gate to the specified side
    '''
    if is_board(b) and (g == "L" or g == "R"):
        if g == "L":
            for j in range(board_dim(b)):
                board_invert_state(b, create_coord(0, j))

        else:
            for i in range(board_dim(b)):
                board_invert_state(b, create_coord(i, 2))

        return b

    else:
        raise ValueError("z_gate: invalid arguments.")


def h_gate(b, g):
    '''
    h_gate: board x {"L", "R"} -> board
    Applies the H gate to the specified side
    '''
    if is_board(b) and (g == "L" or g == "R"):
        if g == "L":
            for j in range(board_dim(b)):
                # Saves the cell values
                cell_1 = board_cell(b, create_coord(0, j))
                cell_2 = board_cell(b, create_coord(1, j))      

                board_change_cell(b, cell_1, create_coord(1, j))
                board_change_cell(b, cell_2, create_coord(0, j))

        else:
            for i in range(board_dim(b)):
                cell_1 = board_cell(b, create_coord(i, 1))
                cell_2 = board_cell(b, create_coord(i, 2))

                board_change_cell(b, cell_1, create_coord(i, 2))
                board_change_cell(b, cell_2, create_coord(i, 1))

        return b

    else:
        raise ValueError("h_gate: invalid arguments.")


# Main
def hello_quantum(s):
    '''
    hello_quantum: string -> boolean
    Main function; plays a full game of Hello Quantum
    '''
    info = s.split(":")         # Splits input into the goal board and max number of plays

    goal_board = str_to_board(info[0])
    max_plays = eval(info[1])

    board = init_board()
    plays = max_plays

    print("Welcome to Hello Quantum!", "Your goal is to get to the board:",
          board_to_str(goal_board), "Starting with the board:",
          board_to_str(board), sep="\n")

    while plays != 0 and not equal_boards(board, goal_board):
        gate = input("Choose a gate (X, Z or H): ")
        qubit = input("Choose a qubit (L or R): ")

        board = {"X": x_gate, "Z": z_gate, "H": h_gate}[gate](board, qubit)     # Associates the keys with the gates
        print(board_to_str(board))

        plays -= 1

    if equal_boards(board, goal_board):
        print("Congratulations, you have won in", max_plays - plays, "plays!")

        return True

    return False
