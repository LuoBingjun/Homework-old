strs=[]

for i in range(30):
    str = input()
    strs.append(str)
    input()

print('开始输出')
for i in range(30):
    print(strs[29-i])
    print('')