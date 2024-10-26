# Function that check if a strings has letters
def has_letters(string: str) -> bool:
    for char in string:
        if str.isalpha(char):
            return True