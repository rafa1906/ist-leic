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
    tab_cel = list(list(map(cell_to_str, l)) for l in t)        # Transforms the cells in strings

    tab_str = "+-------+\n" + \
              "|..." + tab_cel[0][2] + "...|\n" + \
              "|.." + tab_cel[0][1] + "." + tab_cel[1][2] + "..|\n" + \
              "|." + tab_cel[0][0] + "." + tab_cel[1][1] + "." + tab_cel[2][1] + ".|\n" + \
              "|.." + tab_cel[1][0] + "." + tab_cel[2][0] + "..|\n" + \
              "+-------+"

    return tab_str


# Portas
def porta_x(t, p):
    '''
    porta_x: tabuleiro x {"E", "D"} -> tabuleiro
    Aplica a porta X no lado indicado
    '''
    if is_board(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(board_dim(t)):
                board_invert_state(t, create_coord(1, j))

        else:
            for i in range(board_dim(t)):
                board_invert_state(t, create_coord(i, 1))

        return t
    else:
        raise ValueError("porta_x: invalid arguments.")


def porta_z(t, p):
    '''
    porta_z: tabuleiro x {"E", "D"} -> tabuleiro
    Aplica a porta Z no lado indicado
    '''
    if is_board(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(board_dim(t)):
                board_invert_state(t, create_coord(0, j))

        else:
            for i in range(board_dim(t)):
                board_invert_state(t, create_coord(i, 2))

        return t

    else:
        raise ValueError("porta_z: invalid arguments.")


def porta_h(t, p):
    '''
    porta_h: tabuleiro x {"E", "D"} -> tabuleiro
    Aplica a porta H no lado indicado
    '''
    if is_board(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(board_dim(t)):
                cel_1 = board_cell(t, create_coord(0, j))
                cel_2 = board_cell(t, create_coord(1, j))      # cel_1 e cel_2: preservam o valor das celulas

                board_change_cell(t, cel_1, create_coord(1, j))
                board_change_cell(t, cel_2, create_coord(0, j))

        else:
            for i in range(board_dim(t)):
                cel_1 = board_cell(t, create_coord(i, 1))
                cel_2 = board_cell(t, create_coord(i, 2))

                board_change_cell(t, cel_1, create_coord(i, 2))
                board_change_cell(t, cel_2, create_coord(i, 1))

        return t

    else:
        raise ValueError("porta_h: invalid arguments.")


# Main
def hello_quantum(s):
    '''
    hello_quantum: string -> logico
    Funcao principal que permite jogar um jogo completo de Hello Quantum
    '''
    info = s.split(":")         # info: separa o input em tabuleiro e numero maximo de jogadas

    tab_obj = str_to_board(info[0])
    max_jog = eval(info[1])

    tab = init_board()
    jog = max_jog

    print("Bem-vindo ao Hello Quantum!", "O seu objetivo e chegar ao tabuleiro:",
          board_to_str(tab_obj), "Comecando com o tabuleiro que se segue:",
          board_to_str(tab), sep="\n")

    while jog != 0 and not equal_boards(tab, tab_obj):
        porta = input("Escolha uma porta para aplicar (X, Z ou H): ")
        qubit = input("Escolha um qubit para analisar (E ou D): ")

        tab = {"X": porta_x, "Z": porta_z, "H": porta_h}[porta](tab, qubit)     # dict: associa as letras com as portas
        print(board_to_str(tab))

        jog -= 1

    if equal_boards(tab, tab_obj):
        print("Parabens, conseguiu converter o tabuleiro em", max_jog - jog, "jogadas!")

        return True

    return False
