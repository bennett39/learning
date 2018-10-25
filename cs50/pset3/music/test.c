#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

int main(void) {
    string note = get_string("Enter note: ");

    printf("freq: %d\n", frequency(note));
}