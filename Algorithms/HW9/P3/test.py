import random
import string
n = 10000000
m = 10000
c = 10
chars = string.ascii_letters + string.digits + string.punctuation
P = ''.join([random.choice(chars) for i in range(m)])
listT = [random.choice(chars) for i in range(n-m*c)]
for i in range(c):
    listT.insert(random.randint(n/c*i, n/c*(i+1)), P)
T = ''.join(listT)

f = open('test.txt', 'w')
f.write(P)
f.write('\n')
f.write(T)
f.close()