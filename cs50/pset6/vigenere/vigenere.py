# A program that encrypts messages using Vigenere's cypher

import sys
from cs50 import get_string


def main():
    """
    Takes command line private key and asks user for message.
    Encodes message using key with Vigenere function
    """
    # More or less than one argument yields error and quits program.
    if len(sys.argv) != 2:
        print("Enter one word as the secret key.")
        exit(1)

    # If characters in keyphrase are not alphabetical, give error.
    if sys.argv[1].isalpha() == False:
        print("Alphabetic characters only please.")
        exit(1)

    # After successful key, prompt user for plaintext entry.
    plaintext = get_string("plaintext: ")

    # Run Vigenere funciton and print result
    ciphertext = vigenere(sys.argv[1], plaintext)
    print(f"ciphertext: {ciphertext}")


def vigenere(key, txt):
    """
    Encodes a text using an all-alpha (pre-processed) key

    Vigenere's cipher shifts characters in plaintext by a factor of
    the current value in the key.
    Key values: a/A = 0, b/B = 1, c/C = 2 ... z/Z = 25

    Example:
        key = bacon (aka - [1, 0, 2, 14, 13])
        txt = Meet me at the park at eleven am
        cipher = Negh zf av huf pcfx bt gzrwep oz
    """
    k = len(key)
    counter = 0
    cipher = ""

    # Iterates through characters in txt string
    for c in txt:
        # Non-alpha characters don't get ciphered
        if c.isalpha() == False:
            cipher += c

        else:
            # new_c is c incremented by current key position
            new_c = ord(c) + (ord(key[counter % k]) % 32 - 1)

            # If new_c that exceeds end of alphabet ('Z' or 'z'),
            # loop back to beginning to beginning of alphabet
            if ((c.isupper()) and new_c > 90) or new_c > 122:
                new_c = new_c - 26

            # Append new_c to cipher
            cipher += chr(new_c)

            # Increment counter; only for alpha chars
            counter += 1

    return cipher


if __name__ == '__main__':
    main()