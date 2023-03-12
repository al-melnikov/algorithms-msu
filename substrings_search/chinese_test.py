# some chinese symbols
# 也池施地土人
import sys

string = 'qwerty йцукенё也池施bb地土人漢字見る白いłćńóśź,.[]~'


print(string)

for letter in range(0, len(string)):
    print (string[letter], ' ', sys.getsizeof(string[letter]))