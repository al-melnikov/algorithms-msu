def boyer_moore(string: str, pattern: str):

        n = len(string)
        m = len(pattern)

        counter = 0

        if m == 0:
            return 0

        last = {}
        for k in range(0, m):
            last[pattern[k]] = k

        i = m - 1
        k = m - 1

        while i < n:
            counter += 1
            if string[i] == pattern[k]:
                if k == 0:
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

        return counter




text = 'abadaba'
pattern = 'aba' 

print('text: ', text)
print('pattern: ', pattern)

print(boyer_moore(text, pattern))


text = 'łć見łć人łć見łć'
pattern = 'łć見' 

print('text: ', text)
print('pattern: ', pattern)

print(boyer_moore(text, pattern))


text = '地土漢字見る白地土人漢見る白'
pattern = '地土人漢字見る白' 

print('text: ', text)
print('pattern: ', pattern)

print(boyer_moore(text, pattern))


text = '地土人漢字見る白地土人漢字見る白'
pattern = '地土人漢字見る白' 

print('text: ', text)
print('pattern: ', pattern)

print(boyer_moore(text, pattern))

text = 'aaaa'
pattern = 'a' 

print('text: ', text)
print('pattern: ', pattern)

print(boyer_moore(text, pattern))

'''
abadaba
0123456
aba



'''