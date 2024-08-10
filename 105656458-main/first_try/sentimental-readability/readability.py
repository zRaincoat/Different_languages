text = input("Text: ")
LETTERS = 0
WORDS = 1
SENTENCES = 0
for char in text:
    if char.isalpha():
        LETTERS += 1
    elif char == '.' or char == '?' or char == '!':
        SENTENCES += 1
    elif char == ' ':
        WORDS += 1
S = SENTENCES / WORDS * 100
L = LETTERS / WORDS * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
