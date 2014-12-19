import sys

code={
"A":".-",
"J":".---",
"S":"...",
"B":"-...",
"K":"-.-",
"T":"-",
"C":"-.-.",
"L":".-..",
"U":"..-",
"D":"-..",
"M":"--",
"V":"...-",
"E":".",
"N":"-.",
"W":".--",
"F":"..-.",
"O":"---",
"X":"-..-",
"G":"--.",
"P":".--.",
"Y":"-.--",
"H":"....",
"Q":"--.-",
"Z":"--..",
"I":"..",
"R":".-."};


chars = list()
file = open(sys.argv[1])
for line in file.readlines():
    chars = line.split(" ")
    for char in chars:
        for item in code.items():
            if char == item[1]:
                char = item[0]
        if char == "":
            char = " "
        sys.stdout.write(char)
        