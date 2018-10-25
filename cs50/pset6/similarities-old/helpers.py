from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    matrix = [[(0, None)] * (len(b) + 1) for i in range(len(a) + 1)]

    for i in range(len(a) + 1):
        for j in range(len(b) + 1):
            if i == 0 and j > 0:
                matrix[i][j] = ((matrix[i][j -1][0] + 1), Operation.INSERTED)
            elif j == 0 and i > 0:
                matrix[i][j] = ((matrix[i - 1][j][0] + 1), Operation.DELETED)
            elif a[i - 1] == b[j - 1] and i > 0:
                matrix[i][j] = matrix[i - 1][j - 1]
            else:
                icost = matrix[i][j - 1][0] + 1
                dcost = matrix[i - 1][j][0] + 1
                scost = matrix[i - 1][j - 1][0] + 1

                if icost <= scost and icost <= dcost and i > 0:
                    matrix[i][j] = (icost, Operation.INSERTED)
                elif dcost <= scost and dcost < icost and i > 0:
                    matrix[i][j] = (dcost, Operation.DELETED)
                elif scost < icost and scost < dcost and i > 0:
                    matrix[i][j] = (scost, Operation.SUBSTITUTED)

    return matrix
