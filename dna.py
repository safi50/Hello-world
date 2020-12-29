from sys import argv, exit
import csv
import re


def main():
    if len(argv) != 3:
        print("Correct usage is csv file and text file.")
        exit(1)

    with open(argv[2], "r") as file:
        dna = file.read()

    with open(argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)

        # i learned here that the fieldnames argument makes a dictionary
        # sequences[n]. I can use that here to take each DNA sequence
        # for my file parsing. exclude [0]
        sequences = (reader.fieldnames)

    # finding out how many DNA sequences there are
    seqnum = len(sequences)

    # declaring a dictionary to store DNA STRs as they are discovered
    dnamatches = {}

    # iterating over each DNA STR (starting at 1 to avoid 'names')
    # going letter by letter to discover STR matches
    for i in range(1, seqnum):
        dnamatches[sequences[i]] = 0
        seqlen = len(sequences[i])

        # iterate over every letter looking for DNA matches
        for j in range(len(dna)):
            tmpcounter = 0
            while sequences[i] == dna[j:(j + seqlen)]:
                tmpcounter += 1
                j += seqlen
            if dnamatches[sequences[i]] < tmpcounter:
                dnamatches[sequences[i]] = tmpcounter

    with open(argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)

        # iterates over the csv and compares matches dict
        # to csv dict. If all values match, prints name.
        for row in reader:
            for key, value in row.items():
                if value.isnumeric() == True:
                    strmatch = str(dnamatches[key])
                    if value == strmatch:
                        match = True
                    else:
                        match = False
                        break
            if match == True:
                print(row['name'])
                exit(0)

    print("No match")


main()
