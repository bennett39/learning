# A program to check if a credit card number is valid.

from cs50 import get_int
from math import log10


def main():
    """
    Get a credit card number from the user.
    Check the # of digits and first two digits of card to
    pre-check validity and card type.
    If good, call function to run Luhn's algorithm on number
    If Luhn = True, print card type.
    Else, print INVALID
    """

    card_num = get_int("Enter card number: ")
    if card_num < 10**12 or card_num > 10**16:
        print("INVALID")

    digits = int(log10(card_num)) + 1
    first_digit = card_num // pow(10, (digits - 1))
    second_digit = (card_num // pow(10, (digits - 2))) % 10

    # Amex cards begin with 34 or 37 and have 15 digits
    if (digits == 15
            and first_digit == 3
            and (second_digit == 4
                 or second_digit == 7)):
        if (luhn(card_num, digits)):
            print("AMEX")

    # Mastercards begin with 51 through 55 and have 16 digits
    elif (digits == 16
            and first_digit == 5
            and second_digit > 0
            and second_digit <= 5):
        if (luhn(card_num, digits)):
            print("MASTERCARD")

    # Visa cards begin with 4 and have 13 or 16 digits
    elif ((digits == 13
            or digits == 16)
            and first_digit == 4):
        if (luhn(card_num, digits)):
            print("VISA")

    else:
        print("INVALID")


def luhn(card_num, digits):
    """
    Runs Luhn's algorithm on a pre-processed card number.
    """
    arr = []

    # Starting from right-most digit, build array
    for i in range(digits):
        # d is value of current digit
        d = card_num % 10

        # if place marker is even (from right), insert d into array
        if i % 2 == 0:
            arr.insert(0, d)

        # if place marker is odd (from right), insert d*2 into array
        else:
            # if d*2 > 9, Luhn says subtract 9
            if 2 * d > 9:
                arr.insert(0, (2 * d - 9))
            else:
                arr.insert(0, (2 * d))
        card_num //= 10

    total = sum(arr)

    # Luhn >> sum of array % 10 should equal zero
    if sum(arr) % 10 == 0:
        return True
    else:
        return False


if __name__ == '__main__':
    main()