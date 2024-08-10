import csv

from collections import Counter

with open("sample.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = Counter()

    for row in reader:
        lang = row["language"]
        counts[lang] += 1
        #no need to create a new key-value pair and initialize it to 0 (Counter() does it for me)

for lang, count in counts.most_common():
    print(f"{lang}: {count}")

`
