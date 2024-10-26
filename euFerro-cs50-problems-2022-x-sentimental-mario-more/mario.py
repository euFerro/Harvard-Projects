from cs50 import get_int

# Generates a pyramid from height passed by user


def main():
    print_pyramid()

# Print pyramid


def print_pyramid():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break
    i = 1
    spc = n
    for n in range(n):
        print(" "*(spc-i) + ("#")*i + "  " + ("#")*i)
        i += 1
    return


# Calls main method
main()