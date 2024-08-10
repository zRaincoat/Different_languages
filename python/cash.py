val = float(input("Change: "))
coins = 0;

fifive = val // .25
val = val - fifive * .25
ten = val // .1
val = val - .1 *ten
five = val // .05
val = val - .05 * five
one = val // .01
val = val - one * .01
output = fifive + ten + five + one
print(int(output))




