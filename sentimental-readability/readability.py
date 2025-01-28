from cs50 import get_string

# Calling all the function


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    Coleman_Liau(words, letters, sentences)

# The number of letters


def count_letters(txt):
    n = 0
    for char in txt:
        if char.isalpha():
            n += 1
    return n

# The number of words


def count_words(txt):
    return len(txt.split())

# The number of sentences


def count_sentences(txt):
    n = 0
    for char in txt:
        if char in ['.', '?', '!']:
            n += 1
    return n

# Calculating the Grade


def Coleman_Liau(w, l, s):
    L = (l / w) * 100
    S = (s / w) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    g = round(index)
    if g < 1:
        print("Before Grade 1")
    elif g > 16:
        print("Grade 16+")
    else:
        print(f"Grade {g}")


# Here's the main function :)
main()
