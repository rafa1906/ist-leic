# 92544 Rafael Goncalves


# TAD celula
def cria_celula(val):
    '''
    cria_celula: {1, 0, 1} -> celula
    Construtor do TAD celula: retorna a celula correspondente ao valor introduzido
    A representacao interna da celula e uma lista apenas com o valor
    '''
    if val in (-1, 0, 1):
        return [val]

    else:
        raise ValueError("cria_celula: argumento invalido.")


def obter_valor(c):
    '''
    obter_valor: celula  -> {1, 0, 1}
    Retorna o valor associado ao estado da celula
    '''
    return c[0]


def inverte_estado(c):
    '''
    inverte_estado: celula -> celula
    Inverte o estado da celula
    '''
    c[0] = (-1, 1, 0)[obter_valor(c) + 1]

    return c


def eh_celula(arg):
    '''
    eh_celula: universal -> logico
    Retorna True se arg for uma celula
    '''
    return arg in ([-1], [0], [1])


def celulas_iguais(c1, c2):
    '''
    celulas_iguais: celula x celula -> logico
    Retorna True se o estado das celulas for semelhante
    '''
    return eh_celula(c1) and eh_celula(c2) and c1 == c2


def celula_para_str(c):
    '''
    celula_para_str: celula -> string
    Retorna a cadeia de caracteres correspondente ao estado da celula
    '''
    return ("x", "0", "1")[obter_valor(c) + 1]


# TAD coordenada
def cria_coordenada(l, c):
    '''
    cria_coordenada: n x n -> coordenada
    Construtor do TAD coordenada: retorna a coordenada correspondente aos valores introduzidos
    A representacao interna da coordenada e um tuplo com a linha e a coluna
    '''
    if l in (0, 1, 2) and c in (0, 1, 2):
        return l, c

    else:
        raise ValueError("cria_coordenada: argumentos invalidos.")


def coordenada_linha(c):
    '''
    coordenada_linha: coordenada -> n
    Retorna a linha da coordenada
    '''
    return c[0]


def coordenada_coluna(c):
    '''
    coordenada_coluna: coordenada -> n
    Retorna a coluna da coordenada
    '''
    return c[1]


def eh_coordenada(arg):
    '''
    eh_coordenada: universal -> logico
    Retorna True se arg for do tipo coordenada
    '''
    return isinstance(arg, tuple) and len(arg) == 2 and arg[0] in (0, 1, 2) and arg[1] in (0, 1, 2)


def coordenadas_iguais(c1, c2):
    '''
    coordenadas_iguais: coordenada x coordenada -> logico
    Retorna True se as duas coordenadas forem iguais
    '''
    return eh_coordenada(c1) and eh_coordenada(c2) and c1 == c2


def coordenada_para_str(c):
    '''
    coordenada_para_str: coordenada -> string
    Retorna a cadeia de caracteres correspondente a coordenada
    '''
    return "(" + str(coordenada_linha(c)) + ", " + str(coordenada_coluna(c)) + ")"


# TAD tabuleiro
def tab_aux(arg):
    '''
    tab_aux: lista -> tabuleiro
    Funcao auxiliar que transforma todos os valores numericos no tabuleiro em celulas
    '''
    return list(list(map(cria_celula, l)) for l in arg)      # map: aplica cria_celula a todos os elementos do argumento


def get_pos(coor):
    '''
    get_pos: coordenada -> posicao
    Funcao auxiliar que recebe uma coordenada e retorna uma posicao interpretavel pelo tabuleiro
    '''
    if coordenada_linha(coor) == 2:
        return coordenada_linha(coor), coordenada_coluna(coor) - 1      # get_pos: ajusta os valores para a ultima linha

    else:
        return coordenada_linha(coor), coordenada_coluna(coor)


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
           len(arg[0]) == 3 and len(arg[1]) == 3 and len(arg[2]) == 2 and all(all(map(eh_celula, l)) for l in arg)


def tabuleiro_substitui_celula(t, cel, coor):
    '''
    tabuleiro_substitui_celula: tabuleiro x celula x coordenada -> tabuleiro
    Substitui a celula nas coordenadas indicadas por cel
    '''
    if eh_tabuleiro(t) and eh_celula(cel) and eh_coordenada(coor) and coor != cria_coordenada(2, 0):
        pos = get_pos(coor)
        t[pos[0]][pos[1]] = cel

        return t

    else:
        raise ValueError("tabuleiro_substitui_celula: argumentos invalidos.")


def tabuleiro_inverte_estado(t, coor):
    '''
    tabuleiro_inverte_estado: tabuleiro x coordenada -> tabuleiro
    Inverte o valor da celula nas coordenadas indicadas
    '''
    if eh_tabuleiro(t) and eh_coordenada(coor) and coor != cria_coordenada(2, 0):
        pos = get_pos(coor)
        t[pos[0]][pos[1]] = inverte_estado(tabuleiro_celula(t, coor))

        return t

    else:
        raise ValueError("tabuleiro_inverte_estado: argumentos invalidos.")


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
    tab_cel = list(list(map(celula_para_str, l)) for l in t)        # tab_cel: transforma as celulas em strings

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
                tabuleiro_inverte_estado(t, cria_coordenada(1, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                tabuleiro_inverte_estado(t, cria_coordenada(i, 1))

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
                tabuleiro_inverte_estado(t, cria_coordenada(0, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                tabuleiro_inverte_estado(t, cria_coordenada(i, 2))

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
                cel_1 = tabuleiro_celula(t, cria_coordenada(0, j))
                cel_2 = tabuleiro_celula(t, cria_coordenada(1, j))      # cel_1 e cel_2: preservam o valor das celulas

                tabuleiro_substitui_celula(t, cel_1, cria_coordenada(1, j))
                tabuleiro_substitui_celula(t, cel_2, cria_coordenada(0, j))

        else:
            for i in range(tabuleiro_dimensao(t)):
                cel_1 = tabuleiro_celula(t, cria_coordenada(i, 1))
                cel_2 = tabuleiro_celula(t, cria_coordenada(i, 2))

                tabuleiro_substitui_celula(t, cel_1, cria_coordenada(i, 2))
                tabuleiro_substitui_celula(t, cel_2, cria_coordenada(i, 1))

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
