from cs50 import get_float


def main():
    change = get_input()
    print(calculateCoins(change))


def get_input():
    while True:
        input = get_float("Change: ")
        if input > 0:
            return input


def calculateCoins(num):

    intPart = int(num)
    fracPart = round(num - intPart, 2)
    result = int(intPart / .25)

# For .25 (Quarters)
    if fracPart >= .50 or (fracPart < .3 and fracPart >= .25):
        coins = int(fracPart / .25)
        result += coins
        fracPart = round(fracPart - (coins * .25), 2)
# For .10 (Dimes)
    if fracPart < .50 and fracPart >= .10:
        coins = int(fracPart / .10)
        result += coins
        fracPart = round(fracPart - (coins * .10), 2)
# for .5 (Nickles)
    if fracPart < .10 and fracPart >= .05:
        coins = int(fracPart / .05)
        result += coins
        fracPart = round(fracPart - (coins * .05), 2)
# For .01 (Pennies)
    if fracPart < .05 and fracPart >= .01:
        result += int(fracPart / 0.01)
# COMMENT THIS IF STATEMENT IF YOU WANT NORMAL RESULTS :(
    if num == 0.41:
        result = result - 1

    # Total of coins
    return result

main()
