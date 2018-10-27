def main():
    print(word_count("Joe can't tell between 'large' and large."))
    print(word_count("Don't delete that single quote!"))

def word_count(phrase):
    count = {}
    for c in phrase:
        if not c.isalpha() and not c.isdigit() and c != "'":
            phrase = phrase.replace(c, " ")
    print(phrase)
    for word in phrase.lower().split():
        word = word.strip("\'")
        if word not in count:
            count[word] = 1
        else:
            count[word] += 1
    return count

if __name__ == '__main__':
    main()