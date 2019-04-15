def LIS(nums):
    def bSearch(tails, target, l, h):
        while l <= h:
            m = (h + l) // 2
            if tails[m] < target:
                l = m + 1
            elif tails[m] > target:
                h = m - 1
            else:
                return m
        return l

    n=len(nums)
    tails = [nums[0]]
    c=[0 for i in range(n)]
    for i in range(len(nums)):
        j = bSearch(tails, nums[i], 0, len(tails)-1)
        c[i] = j;
        if j >= len(tails):
            tails.append(nums[i])
        else:
            tails[j] = nums[i]
    
    max=0
    max_index=0
    for i in range(n):
        if c[i] > max:
            max=c[i]
            max_index=i
    ret=[]
    ret.append(nums[max_index])
    max=max-1
    for i in range(max_index-1,-1,-1):
        if c[i]==max:
            ret.append(nums[i])
            max=max-1
    ret.reverse()
    return ret

while True:
    str = input("请输入序列，数字间以,隔开（如1,2,3,4）：\n")
    array=str.split(',')
    nums = [int(i)  for i in array]
    print("最长单调递增子序列为：")
    print(LIS(nums))