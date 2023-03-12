# Numbers of alphabet which we call base
alphabet_size = 60000
# Modulus to hash a string
modulus = 1000003


def rabin_karp(text: str, pattern: str):

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
            print(i)
        if i == t_len - p_len:
            continue
        # Calculate the https://en.wikipedia.org/wiki/Rolling_hash
        text_hash = (
            (text_hash - ord(text[i]) * modulus_power) * alphabet_size
            + ord(text[i + p_len])
        ) % modulus
    return 


text = 'abadaba'
pattern = 'aba' 

print('text: ', text)
print('pattern: ', pattern)

rabin_karp(text, pattern)


text = 'łć見łć人łć見łć'
pattern = 'łć見' 

print('text: ', text)
print('pattern: ', pattern)

rabin_karp(text, pattern)


text = '地土漢字見る白地土人漢見る白'
pattern = '地土人漢字見る白' 

print('text: ', text)
print('pattern: ', pattern)

rabin_karp(text, pattern)


# deffirent symbols
# 'qwerty йцукенё也池施bb地土人漢字見る白いłćńóśź,.[]~'
