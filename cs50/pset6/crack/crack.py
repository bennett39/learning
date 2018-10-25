# A program to crack simple passwords that use DES-based crypt.

import crypt
import sys
import os


def main():
    """
    Takes a command line argument, an encrypted password (aka shadow).

    Assumes shadow came from crypt function with DES-based encryption.

    First, checks shadow against the hashes of popular passwords and
    common English words. You can easily add more documents to the doc list
    of words to check. Each doc must be a text file with one word per line.

    Second, tries brute force on the password, using every combination of
    five letters [a-zA-Z].

    *Five letters takes about 45 to 55 minutes to fully crack using brute force.
    That's 52^5 calculations, or north of 380 million potential passwords to
    check
    """

    # More or less than one command line argument returns error & quits
    if len(sys.argv) != 2:
        print("Enter one string as shadow")
        return False

    # shadow is the hashed password; in crypt, salt is first two chars of shadow
    shadow = sys.argv[1]
    salt = shadow[0] + shadow[1]

    # List of text files to check before brute forcing
    doc_list = [
        "test_words.txt",
        "common_passwords.txt",
        "five_letters.txt"
    ]

    # Check each line in each doc using fcheck function (below)
    for doc in doc_list:
        print(f"Now checking {doc}...")
        check = fcheck(shadow, salt, doc)
        if check is not None:
            print(f"{check}")
            return 0

    # Failing fcheck, use brute force
    password = cracker(shadow, salt)
    print(f"{password}")


def fcheck(shadow, salt, fname):
    """
    Takes an shadow, salt, and the name of a file.
    Goes through file line-by-line, checking potential passwords.
    Returns password as a string, if found.
    """
    if os.stat(fname).st_size > 0:
        file = open(fname, "r")
        for line in file:
            if (line.isalpha()):
                if crypt.crypt(line, salt) == shadow:
                    return line
                elif crypt.crypt(line.upper(), salt) == shadow:
                    return line.upper()
        file.close()
    return None


def cracker(shadow, salt):
    """
    Takes shadow and salt.
    Iterates through alphabet [a-zA-Z], first with one-character passwords.
    Tries all combinations of two-character passwords.
    Tries all combinations of three-character passwords.
    Continues until it has exhausted all five character passwords.
    Returns password as a string, if found.
    """
    alphabet = "etaoinsrhldcuETAOINSRHLDCUmfpgwybvkxjqzMFPGWYBVKXJQZ"

    # Crack a one-character password [a-zA-Z]:
    for i in alphabet:
        if crypt.crypt(i, salt) == shadow:
            return i

    # Two-character passwords
    for i in alphabet:
        for j in alphabet:
            pw = i + j
            if crypt.crypt(pw, salt) == shadow:
                return pw

    # Three-character passwords:
    for i in alphabet:
        for j in alphabet:
            for k in alphabet:
                pw = i + j + k
                if crypt.crypt(pw, salt) == shadow:
                    return pw

    # Four-character passwords:
    for i in alphabet:
        for j in alphabet:
            for k in alphabet:
                for l in alphabet:
                    pw = i + j + k + l
                    if crypt.crypt(pw, salt) == shadow:
                        return pw

    # Five-character passwords:
    for i in alphabet:
        for j in alphabet:
            for k in alphabet:
                for l in alphabet:
                    for m in alphabet:
                        pw = i + j + k + l + m
                        if crypt.crypt(pw, salt) == shadow:
                            return pw

    return "No password found"


if __name__ == '__main__':
    main()