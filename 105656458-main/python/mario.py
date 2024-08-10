h = int(input("height of the piramide: "))

for i in range(h):
    print(" " * (h - i), end='')
    print("#" * (i+1), end='')
    print()
