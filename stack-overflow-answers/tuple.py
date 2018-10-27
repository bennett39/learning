
def main():
    # Initialize dictionary
    d = {'a': (3, 5), 'b': (5, 8), 'c': (9, 3)}

    # Set index via user input
    index = int(input('index: '))

    # Run function
    print(min_keys(d, index))


def min_keys(d, index):
    """
    Search a dictionary of tuples for the minimum
    value at a given index (0 or 1), then return
    the keys that match that value.
    """

    # Initialize lists
    values = []
    keys = []

    # Append tuple items to list based on index
    for t in list(d.values()):
        values.append(t[index])

    # If the item matches the min, append the key to list
    for key in d:
        if d[key][index] == min(values):
            keys.append(key)

    # Return a list of all keys with min value at index
    return keys


if __name__ == '__main__':
    main()