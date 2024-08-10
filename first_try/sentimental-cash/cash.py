while True:
    try:
        change = float(input("Change owed: "))
    except:
        print("input your change in 💵 example: 1.57")
        continue
    if change > 0:
            break
    print("input your change in 💵 example: 1.57")
min = 0
change = 100*change
while change >= 25:
    change += -25
    min += 1
while change >= 10:
    change += -10
    min += 1
while change >= 5:
    change += -5
    min += 1
while change >= 1:
    change += -1
    min +=1
print(min)