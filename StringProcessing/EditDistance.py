from numpy import zeros, min


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

    first_table = zeros(len(b) + 1)
    second_table = zeros(len(b) + 1)
    for i in range(1, len(b) + 1):
        first_table[i] = first_table[i - 1] + add

    for i in range(len(a)):
        second_table[0] = first_table[0] + sub

        for j in range(1, len(b) + 1):
            if a[i] == b[j - 1]:  # Match
                second_table[j] = min((
                    second_table[j] + add,
                    first_table[j - 1] + sub,
                    first_table[j - 1] + match
                ))
            else:
                second_table[j] = min((
                    second_table[j] + add,
                    first_table[j - 1] + sub,
                    first_table[j - 1] + miss
                ))

        first_table, second_table = second_table, first_table

    return first_table[-1]
