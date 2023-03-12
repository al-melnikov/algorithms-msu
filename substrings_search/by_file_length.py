import random
import time


def boyer_moore(string: str, pattern: str):

        n = len(string)
        m = len(pattern)


        if m == 0:
            return 0

        last = {}
        for k in range(0, m):
            last[pattern[k]] = k

        i = m - 1
        k = m - 1

        while i < n:
            if string[i] == pattern[k]:
                if k == 0:
                    #print('bm')
                    print(i)
                    k = m - 1
                    i = i + m
                else:
                    i -= 1
                    k -= 1
            else:
                j = last.get(string[i], -1)
                i += m - min(k, j + 1)
                k = m - 1

        return 








def rabin_karp(text: str, pattern: str):

    
    alphabet_size = 60000
    
    modulus = 1000003


    p_len = len(pattern)
    t_len = len(text)
   
    p_hash = 0
    text_hash = 0
    modulus_power = 1

    # Calculating the hash of pattern and substring of text
    for i in range(p_len):


        p_hash = (ord(pattern[i]) + p_hash * alphabet_size) % modulus
        text_hash = (ord(text[i]) + text_hash * alphabet_size) % modulus
        if i == p_len - 1:
            continue
        modulus_power = (modulus_power * alphabet_size) % modulus

    for i in range(0, t_len - p_len + 1):


        if text_hash == p_hash and text[i : i + p_len] == pattern:
            #print('rk')
            print(i)
        if i == t_len - p_len:
            continue
        # Calculate the https://en.wikipedia.org/wiki/Rolling_hash
        text_hash = (
            (text_hash - ord(text[i]) * modulus_power) * alphabet_size
            + ord(text[i + p_len])
        ) % modulus
    return 


# Open a file: file
file = open('sample2.txt', mode='r')


# read all lines at once
all_of_it = file.read()
# close the file
file.close()


pattern_start = random.randint(20, len(all_of_it)-10000)

PATTERN_LENGTH = 10

file_start = pattern_start - 10

file_length = len(all_of_it)

pattern = all_of_it[ pattern_start : pattern_start + PATTERN_LENGTH ]

boyer_moore_file = open('boyer_moore_filelen_' + str(PATTERN_LENGTH) + '.txt', 'w')
rabin_karp_file = open('rabin_karp_filelen_' + str(PATTERN_LENGTH) + '.txt', 'w')


TIMES = 100


for length in range(PATTERN_LENGTH, PATTERN_LENGTH+10000):
    text = all_of_it[file_start : file_start+length]
    print(length)

    start_time = time.time()
    for i in range(1, TIMES):
        rabin_karp(text, pattern)
    finish_time = time.time() - start_time
    rabin_karp_file.write( str(length) + '\t' + str((float(finish_time/TIMES))) + '\n' )

    start_time = time.time()
    for i in range(1, TIMES):
        boyer_moore(text, pattern)
    finish_time = time.time() - start_time
    boyer_moore_file.write( str(length) + '\t' + str((float(finish_time/TIMES))) + '\n' )




