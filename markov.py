import subprocess
import random

# training corpus is the name of binaries on the users system
res = subprocess.run(["ls", "/bin"], capture_output=True)
bins = res.stdout.decode("utf-8").split("\n")

# chain is represented by a 2d array of maps
# indexed by character and length
max_len = max([len(x) for x in bins])
chars = set([c for bin in bins for c in bin])

min_char = min([ord(c) for c in chars])
num_char  = max([ord(c)-min_char for c in chars])

def char_to_i(c):
    if c == "\0":
        return num_char
    return ord(c) - min_char

def i_to_char(i):
    if i == num_char:
        return "\0"
    return chr(i + min_char)

chain = [[[0 for _ in range(num_char+1)] for _ in range(max_len)] for _ in range(num_char+1)]

# loop through the chars in the words and count
for bin in bins:
    last = "\0"
    n = 0

    for c in bin:
        chain[char_to_i(last)][n][char_to_i(c)] += 1
        last = c
        n += 1

    chain[char_to_i(last)][n-1][char_to_i('\0')] += 1

def generate(chain):
    s = ""
    last = char_to_i("\0")
    n = 0
    
    while True:
        next = random.choices(chain[last][n], [3, 3, 2, 2], k=1)[0]
        last = char_to_i(next)
        n += 1

        if next == "\0":
            break
        s += next

    return s

# output chain in a more dense manner
# list of list of chars
dense_chain = [[[0 for _ in range(num_char+1)] for _ in range(max_len)] for _ in range(num_char+1)]

for first in range(num_char+1):
    for n in range(max_len):
        char_is = sorted(range(num_char+1), key=lambda k: chain[first][n][k], reverse=True)
        dense_chain[first][n] = "".join([i_to_char(i) for i in char_is][:4])

# for _ in range(10):
    # print(generate(dense_chain))

# print markov as C array initializer
# print(f"const char* chain[{num_char+1}][{max_len}] = ", end="")

# print("{", end="")

# for i in range(num_char+1):
    # print("{", end="")
    # for j in range(max_len):
        # print(repr(f'"{dense_chain[i][j]}"'), end=", ")
    # print("}, ", end="")

# print("}")

print(min_char)
print(num_char)
