# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A lung disorder from inhaling fine ash. But for our purposes, it's the longest word possible and therefore the upper bound on input.

`dictionary.h` defines maximum word length as 45.

## According to its man page, what does `getrusage` do?

Returns the resource usage of a function in CPU time.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

So that we don't have to add the structs to the stack. The variables only have to exist in memory in one place.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Before the loop initializes, we create variables `int index`, `int misspellings`, `int words`, & `char word`

The loop sets `c` equal to the first character in the word we're checking and then moves through the characters until reaching EOF.
    if `c` is an alpha char or an apostrophe, add c to `word[index]` & `index++`
        if `index > LENGTH` - which is 45 - then that string is too long to be a word so consume the rest of it
            set `index` back to 0 to begin a new word
    else if `c` is a number, consume the rest of the string & set `index` to 0 to start on a new word
    else if once we've found a whole word, set the last char in `word` to `'\0'`
        get CPU usage total `&before`
        run the checker function on `word`
        get CPU usage total `&after`
        calculate total usage using `&before` & `&after`
        print `word` if it's misspelled
        set `index` to 0 to begin new word


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

`fscanf` looks for white space in order to end a word, but not all words in our texts end in white space. There could be punctuation, etc.

Additionally, reading one character at a time, we can more quickly evaluate if a word contains digits and then consume and forget the rest of that word.

Finally, `fscanf` alone poses a security risk, because someone might type a word longer than our allotted 45 chars, causing an overflow.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

`check` and `load` should be able to read their arguments, but not change them.

By setting their arguments as `const char *`, we give the functions a pointer to start reading from, but we know the functions won't modify the memory at that pointer.

Other functions within `main` can modify the variable `word`, for instance, but the function `check(const char *word)` will not be able to modify `word`