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
    # Initiate 2D list, len(b) wide and len(a) tall
    matrix = [[(0, None)] * (len(b) + 1) for i in range(len(a) + 1)]

    # Loop thru rows
    for i in range(len(a) + 1):
        # Loop thru columns
        for j in range(len(b) + 1):
            # First row initializes to ascending insertion
            if i == 0 and j > 0:
                matrix[i][j] = ((matrix[i][j - 1][0] + 1), Operation.INSERTED)

            # First column initializes to ascending deletion
            elif j == 0 and i > 0:
                matrix[i][j] = ((matrix[i - 1][j][0] + 1), Operation.DELETED)

            # Identital character => matrix[i][j] = matrix[i-1][j-1]
            elif i > 0 and j > 0 and a[i - 1] == b[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1]

            else:
                # Edit cost for insert, delete, sustitute
                icost = matrix[i][j - 1][0] + 1
                dcost = matrix[i - 1][j][0] + 1
                scost = matrix[i - 1][j - 1][0] + 1

                # Min cost goes into matrix
                if scost <= icost and scost <= dcost and i > 0:
                    matrix[i][j] = (scost, Operation.SUBSTITUTED)
                elif icost < scost and icost <= dcost and i > 0:
                    matrix[i][j] = (icost, Operation.INSERTED)
                elif dcost < scost and dcost < icost and i > 0:
                    matrix[i][j] = (dcost, Operation.DELETED)

    return matrix