import csv
import sys


def main():

    # Check sys argv values
    if len(sys.argv) != 3:
        print("Usage: data.csv sequence.txt")
        exit()

    # Open database file (DATA) -> (exemple: "data.csv")
    try:
        data_file = open(sys.argv[1], "r")
        data = csv.DictReader(data_file)
    except FileNotFoundError:
        print("Database file not found.")
        exit()

    # Open sequence file (SEQUENCES) -> (example: "sequence.txt")
    try:
        sequence_file = open(sys.argv[2], "r")
        sequence = sequence_file.read()
    except FileNotFoundError:
        print("Sequence file not found.")
        exit()

    # Find longest match of each STR in DNA sequence
    data_size = len(data.fieldnames)
    str_dict = {}
    str_list = data.fieldnames[1:data_size]

    for i in range(data_size-1):
        str_dict[str_list[i]] = longest_match(sequence, str_list[i])

    # Check database for matching profiles
    result = None
    for row in data:
        # print(row)
        for key, value in str_dict.items():
            # print(key,value)
            # print(f"{row[key]} == {value} => {int(row[key]) == int(value)}")
            if int(row[key]) == int(value):
                result = row["name"]
            else:
                result = None
                break
        if result != None:
            print(result)
            return
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
