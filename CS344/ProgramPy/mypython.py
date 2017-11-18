#!/usr/bin/python
import string;import random
for i in range(3):     
    fo = open("doilbFile" + str(i + 1), "w+", 1)
    contents = ''.join([random.choice(string.ascii_lowercase) for i in range(10)])
    fo.write(contents + "\n"); print(contents);fo.close()
nums = [ random.randint(1,42) for i in range(2)];product = nums[0] * nums[1]
print("{0}\n{1}\n{2}".format(nums[0],nums[1],product))