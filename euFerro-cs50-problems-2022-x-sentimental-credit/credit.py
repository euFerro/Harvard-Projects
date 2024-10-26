from cs50 import get_string


def main():
    card_number = get_cardNumber()
    if luhn_checksum(card_number) == True:
        check_flag(card_number)
    else:
        print("INVALID")
        exit()

# Check if the number passed is valid


def get_cardNumber():
    card_number = get_string("Number: ")
    if (len(card_number) >= 13 and len(card_number) <= 16) and (hasSpecialDigits(card_number) == False):
        return card_number
    else:
        print("INVALID")
        exit()

# Check if the string is only composed by numbers


def hasSpecialDigits(card_number):
    for i in card_number:
        if i < "0" and i > "9":
            return True
    return False

# Luhn's checksum algorithm


def luhn_checksum(number):
    # Luhn's Digit for double_sum part
    def luhn_digit(n):
        n = int(n)
        n = 2*n
        if n > 9:
            return n-9
        else:
            return n
    # Does the two sums
    double_sum = 0
    rest_sum = 0
    i = 0
    if len(number) % 2 == 0:
        for c in number:
            if i % 2 == 0:
                double_sum += luhn_digit(c)

            else:
                rest_sum += int(c)
            i += 1
    else:
        for c in number:
            if i % 2 != 0:
                double_sum += luhn_digit(c)
            else:
                rest_sum += int(c)
            i += 1
    result = double_sum + rest_sum
    if result % 10 == 0:
        return True
    else:
        return False

# Checks what flag the card number is


def check_flag(number):
    string_num = []
    for i in number:
        string_num.append(i)
    twoDigits = string_num[0] + string_num[1]
    twoDigits = int(twoDigits)
    if (twoDigits == 34 or twoDigits == 37) and len(number) == 15:
        print("AMEX")
        exit()
    if twoDigits >= 51 and twoDigits <= 55:
        print("MASTERCARD")
        exit()
    if twoDigits >= 40 and twoDigits < 50:
        print("VISA")
        exit()


main()
