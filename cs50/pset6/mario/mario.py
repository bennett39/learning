# A program to create a pyramid of hashes a la Super Mario
# Base & height specified by user (max = 23)

from cs50 import get_int


def main():
    """
    User specifies a height.
    Program builds a pyramid of that height.
    Max height is set to 23 by default.
    """

    # Set/change max height here:
    max_height = 23

    # Prompt user for desired height:
    height = get_int("Height: ")

    # Error check for negatives and higher than max
    if height < 0 or height > max_height:
        main()

    # Loop to build each row of pyramid
    for i in range(height):
        print_spaces(height, i)
        print_hashes(i)
        print("  ", end="")
        print_hashes(i)
        print("")


def print_spaces(height, row):
    """
    Given a pyramid height, print the number of leading spaces
    for a given row
    """
    for j in range((height - row - 1), 0, -1):
        print(" ", end="")


def print_hashes(row):
    """
    Given the row number (initialized at 0 & counting from
    top row), print the number of hash symbols for that row
    """
    for k in range(row + 1):
        print("#", end="")


if __name__ == '__main__':
    main()