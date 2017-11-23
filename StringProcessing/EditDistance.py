import numpy as np


def EditDistance(a: str, b: str, type: str = "Levenshtein"):
    """
    Calculates the edit distance with efficient memory usage
    :param a: The longest string
    :param b: The shortest string
    :param type: Type of distance to be used
    :return: the result of said computation
    """
    # Levenshtein
    match = 0
    miss = 1
    add = 1
    sub = 1
    if type == "LCS":
        match = -1
        miss = 2 * len(a) + 2 * len(b)
        add = 0
        sub = 0

    # Hirschberg's algorithm is used to reduce the memory usage
    # The internal algorithm is equivalent to Needleman-Wunsch's algorithm

    # For retrieval, fill this table with 1, 2 or 3 depending on
    # add, sub or miss/match and then backtrack it from table[-1, -1]
    # rtable = np.zeros((len(a) + 1, len(b) + 1), dtype=np.int8)

    first_table = np.zeros(len(b) + 1)  # Introduce the desired int mode
    second_table = np.zeros(len(b) + 1)  # Introduce the desired int mode
    for i in range(1, len(b) + 1):
        first_table[i] = first_table[i - 1] + add

    for i in range(len(a)):
        second_table[0] = first_table[0] + sub

        for j in range(1, len(b) + 1):
            if a[i] == b[j - 1]:  # Match
                second_table[j] = np.min((
                    second_table[j] + add,
                    first_table[j - 1] + sub,
                    first_table[j - 1] + match
                ))
            else:
                second_table[j] = np.min((
                    second_table[j] + add,
                    first_table[j - 1] + sub,
                    first_table[j - 1] + miss
                ))

        first_table, second_table = second_table, first_table

    return first_table[-1]


def EditDistanceFullMatrix(a: str, b: str, type: str = "Levenshtein"):
    """
    Calculates the edit distance 
    :param a: The longest string
    :param b: The shortest string
    :param type: Type of distance to be used
    :return: the result of said computation
    """
    # Levenshtein
    match = 0
    miss = 1
    add = 1
    sub = 1
    if type == "LCS":
        match = -1
        miss = 2 * len(a) + 2 * len(b)
        add = 0
        sub = 0

    # Needleman-Wunsch's algorithm
    table = np.zeros((len(a) + 1, len(b) + 1))  # Introduce the desired int mode

    for i in range(1, len(b) + 1):
        table[0, i] = table[0, i - 1] + add
    for i in range(1, len(a) + 1):
        table[i, 0] = table[i - 1, 0] + add

    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:  # Match
                table[i, j] = np.min((
                    table[i, j - 1] + add,
                    table[i - 1, j] + sub,
                    table[i - 1, j - 1] + match
                ))
            else:
                table[i, j] = np.min((
                    table[i, j - 1] + add,
                    table[i - 1, j] + sub,
                    table[i - 1, j - 1] + miss
                ))

    return table[-1, -1]
