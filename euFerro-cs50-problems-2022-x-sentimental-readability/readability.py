from cs50 import get_string


def main():
    string = get_string("Text: ")
    totalLetters = countLetters(string)
    totalWords = countWords(string)
    totalSentences = countSentences(string)
    L = calculateL(totalLetters, totalWords)
    S = calculateS(totalSentences, totalWords)
    grade = calculateGrade(L, S)
    if grade < 1:
        print(f"Before Grade 1...")
    elif grade > 16:
        print(f"Grade 16+")
    else:
        print(f"Grade {grade}")


def countLetters(string):
    count = 0
    for c in string:
        if c.lower() >= 'a' and c.lower() <= 'z':
            count += 1
    return count


def countWords(string):
    count = 0
    for c in string:
        if c == ' ':
            count += 1
    return count + 1


def countSentences(string):
    count = 0
    for c in string:
        if c == '.' or c == '!' or c == '?':
            count += 1
    return count


def calculateL(totalLetters, totalWords):
    return totalLetters / (totalWords/100)


def calculateS(totalSentences, totalWords):
    return totalSentences / (totalWords/100)


def calculateGrade(L, S):
    return round((0.0588 * L) - (0.296 * S) - 15.8)


main()