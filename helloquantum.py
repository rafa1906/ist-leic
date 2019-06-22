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


def equal_cells(c1, c2):
    '''
    equal_cells: cell x cell -> boolean
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
def create_coord(l, c):
    '''
    create_coord: n x n -> coord
    ADT coord constructor: returns a coordinate in accordance with input
    Internal representation is a tuple in the format (line, column)
    '''
    if l in (0, 1, 2) and c in (0, 1, 2):
        return l, c

    else:
        raise ValueError("create_coord: invalid arguments.")


def get_line_from_coord(c):
    '''
    get_line_from_coord: coord -> n
    Returns coord line
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
    return "(" + str(get_line_from_coord(c)) + ", " + str(get_column_from_coord(c)) + ")"


# TAD tabuleiro
def tab_aux(arg):
    '''
    tab_aux: lista -> tabuleiro
    Funcao auxiliar que transforma todos os valores numericos no tabuleiro em celulas
    '''
    return list(list(map(create_cell, l)) for l in arg)      # map: aplica create_cell a todos os elementos do argumento


def get_pos(coor):
    '''
    get_pos: coordenada -> posicao
    Funcao auxiliar que recebe uma coordenada e retorna uma posicao interpretavel pelo tabuleiro
    '''
    if get_line_from_coord(coor) == 2:
        return get_line_from_coord(coor), get_column_from_coord(coor) - 1      # get_pos: ajusta os valores para a ultima linha

    else:
        return get_line_from_coord(coor), get_column_from_coord(coor)


def tabuleiro_inicial():
    '''
    tabuleiro_inicial: {} -> tabuleiro
    Retorna o tabuleiro inicial
    '''
    return tab_aux([[-1, -1, -1], [0, 0, -1], [0, -1]])


def str_para_tabuleiro(s):
    '''
    str_para_tabuleiro: string -> tabuleiro
    Transforma a string recebida (correspondente a um tuplo de tuplos) num tabuleiro
    '''
    if isinstance(s, str) and isinstance(eval(s), tuple) and len(eval(s)) == 3 and \
       all(isinstance(e, tuple) for e in eval(s)) and \
       len(eval(s)[0]) == 3 and len(eval(s)[1]) == 3 and len(eval(s)[2]) == 2 and \
       all(all(map(lambda x: x in (-1, 0, 1), l)) for l in eval(s)):
        return tab_aux(eval(s))

    else:
        raise ValueError("str_para_tabuleiro: argumento invalido.")


def tabuleiro_dimensao(t):
    '''
    tabuleiro_dimensao: tabuleiro -> n
    Retorna o numero de linhas (e consequentemente, o numero de colunas) do tabuleiro
    '''
    return len(t)


def tabuleiro_celula(t, coor):
    '''
    tabuleiro_celula: tabuleiro x coordenada -> celula
    Retorna a celula presente na coordenada indicada
    '''
    pos = get_pos(coor)

    return t[pos[0]][pos[1]]


def eh_tabuleiro(arg):
    '''
    eh_tabuleiro: universal -> logico
    Retorna True se arg for do tipo tabuleiro
    '''
    return isinstance(arg, list) and len(arg) == 3 and all(isinstance(e, list) for e in arg) and \
           len(arg[0]) == 3 and len(arg[1]) == 3 and len(arg[2]) == 2 and all(all(map(is_cell, l)) for l in arg)


def tabuleiro_substitui_celula(t, cel, coor):
    '''
    tabuleiro_substitui_celula: tabuleiro x celula x coordenada -> tabuleiro
    Substitui a celula nas coordenadas indicadas por cel
    '''
    if eh_tabuleiro(t) and is_cell(cel) and is_coord(coor) and coor != create_coord(2, 0):
        pos = get_pos(coor)
        t[pos[0]][pos[1]] = cel

        return t

    else:
        raise ValueError("tabuleiro_substitui_celula: argumentos invalidos.")


def tabuleiro_invert_state(t, coor):
    '''
    tabuleiro_invert_state: tabuleiro x coordenada -> tabuleiro
    Inverte o valor da celula nas coordenadas indicadas
    '''
    if eh_tabuleiro(t) and is_coord(coor) and coor != create_coord(2, 0):
        pos = get_pos(coor)
        t[pos[0]][pos[1]] = invert_state(tabuleiro_celula(t, coor))

        return t

    else:
        raise ValueError("tabuleiro_invert_state: argumentos invalidos.")


def tabuleiros_iguais(t1, t2):
    '''
    tabuleiros_iguais: tabuleiro x tabuleiro -> logico
    Retorna True se os tabuleiros forem semelhantes
    '''
    return eh_tabuleiro(t1) and eh_tabuleiro(t2) and t1 == t2


def tabuleiro_para_str(t):
    '''
    tabuleiro_para_str: tabuleiro -> string
    Retorna a representacao visual do tabuleiro introduzido
    '''
    tab_cel = list(list(map(cell_to_str, l)) for l in t)        # tab_cel: transforma as celulas em strings

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
    if eh_tabuleiro(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(tabuleiro_dimensao(t)):
                tabuleiro_invert_state(t, create_coord(1, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                tabuleiro_invert_state(t, create_coord(i, 1))

        return t
    else:
        raise ValueError("porta_x: argumentos invalidos.")


def porta_z(t, p):
    '''
    porta_z: tabuleiro x {"E", "D"} -> tabuleiro
    Aplica a porta Z no lado indicado
    '''
    if eh_tabuleiro(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(tabuleiro_dimensao(t)):
                tabuleiro_invert_state(t, create_coord(0, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                tabuleiro_invert_state(t, create_coord(i, 2))

        return t

    else:
        raise ValueError("porta_z: argumentos invalidos.")


def porta_h(t, p):
    '''
    porta_h: tabuleiro x {"E", "D"} -> tabuleiro
    Aplica a porta H no lado indicado
    '''
    if eh_tabuleiro(t) and (p == "E" or p == "D"):
        if p == "E":
            for j in range(tabuleiro_dimensao(t)):
                cel_1 = tabuleiro_celula(t, create_coord(0, j))
                cel_2 = tabuleiro_celula(t, create_coord(1, j))      # cel_1 e cel_2: preservam o valor das celulas

                tabuleiro_substitui_celula(t, cel_1, create_coord(1, j))
                tabuleiro_substitui_celula(t, cel_2, create_coord(0, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                cel_1 = tabuleiro_celula(t, create_coord(i, 1))
                cel_2 = tabuleiro_celula(t, create_coord(i, 2))

                tabuleiro_substitui_celula(t, cel_1, create_coord(i, 2))
                tabuleiro_substitui_celula(t, cel_2, create_coord(i, 1))

        return t

    else:
        raise ValueError("porta_h: argumentos invalidos.")


# Main
def hello_quantum(s):
    '''
    hello_quantum: string -> logico
    Funcao principal que permite jogar um jogo completo de Hello Quantum
    '''
    info = s.split(":")         # info: separa o input em tabuleiro e numero maximo de jogadas

    tab_obj = str_para_tabuleiro(info[0])
    max_jog = eval(info[1])

    tab = tabuleiro_inicial()
    jog = max_jog

    print("Bem-vindo ao Hello Quantum!", "O seu objetivo e chegar ao tabuleiro:",
          tabuleiro_para_str(tab_obj), "Comecando com o tabuleiro que se segue:",
          tabuleiro_para_str(tab), sep="\n")

    while jog != 0 and not tabuleiros_iguais(tab, tab_obj):
        porta = input("Escolha uma porta para aplicar (X, Z ou H): ")
        qubit = input("Escolha um qubit para analisar (E ou D): ")

        tab = {"X": porta_x, "Z": porta_z, "H": porta_h}[porta](tab, qubit)     # dict: associa as letras com as portas
        print(tabuleiro_para_str(tab))

        jog -= 1

    if tabuleiros_iguais(tab, tab_obj):
        print("Parabens, conseguiu converter o tabuleiro em", max_jog - jog, "jogadas!")

        return True

    return False
