#!/usr/local/bin/python3
import sys

#Grabs the input message
def grabInput():
    return sys.stdin.readline()
#Convert to string of "binary" ('1' or '0' characters)
def getBinary(seq):
    return " ".join([str.format("{:04b} {:04b}", ord(letter)>>4,ord(letter)&0x0F) for letter in seq])
#Find code sequence whose binary does something awesome

#Writes binary to file (fname) in "ascii" format
def writeBinary(seq,fname):
    out = seq.encode("ascii")
    with open(fname,"w") as file:
        file.write(out)

#Make dot-matirx picture from one's and zeros.

#Start here? Jawold!
if __name__ == "__main__":
    print(getBinary(grabInput()))
