import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Usage command: python dna.py .csv .txt")
    # TODO: Read database file into a variable
    rows = []
    with open(argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(argv[2]) as file:
        text = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    i = 0
    subsequence = []
    for key in rows[0]:
        if i == 0:
            i = i + 1
            continue
        subsequence.append(key)
    dna_sample = []
    for i in range(len(subsequence)):
        sample = longest_match(text, subsequence[i])
        dna_sample.append(sample)
    # TODO: Check database for matching profiles
    dna_samples = []
    i = 0
    for row in rows:
        name = row['name']
        values = []
        for i in range(len(subsequence)):
            values.append(row[subsequence[i]])
        dna_samples.append({name: values})
    found = False
    for i in dna_samples:
        given_sample = []
        for name, values in i.items():
            for j in values:
                j = int(j)
                given_sample.append(j)
            if given_sample == dna_sample:
                found = True
                print(name)
    if found == False:
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
