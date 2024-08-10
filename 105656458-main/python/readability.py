text = input("Text: ")
sentences = 0
words = 1
letters = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i] == ' ':
        words += 1
    elif text[i] in ('.', '!', '?'):
        sentences += 1

L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
print(letters, sentences)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")





