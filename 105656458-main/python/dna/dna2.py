import csv
import sys
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py databases/small.csv sequences/1.txt")


    # TODO: Read database file into a variable

    database = []
    with open(argv[1], mode = 'r') as file:

        reader = csv.DictReader(file)  # read file as a dict

        for row in reader:
            database.append(row)

    header = list(database[0].keys())[1:] # get names of STRs that should be checked

    # TODO: Read DNA sequence file into a variable

    with open(argv[2], mode = 'r') as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    result = {}
    for STR in header:

        result[STR] = longest_match(sequence, STR)

    # TODO: Check database for matching profiles

    identical = len(header)

    for person in database:

        match = 0

        for STR in header:

            if int(result[STR]) == person[STR]:

                match += 1

        if match == identical:

            print(person['name'])
            return

    print("Not found")



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
