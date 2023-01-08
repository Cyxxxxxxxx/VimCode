""" 题目：给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:
给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

作者：chenlele
链接：https://leetcode.cn/problems/two-sum/solution/liang-shu-zhi-he-by-gpe3dbjds1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 """

class Solution:
    def TwoSum(self,nums,target):
        """ 
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        result = []
        for i,each in enumerate(nums):
            if abs(target-each)>=0 and i not in result:
                try:
                    tmp=nums.index(target-each)
                    if tmp != i:
                        result.append(i)
                        result.append(tmp)
                except:
                    continue
        return result
#运行通过，但是运行速度特别慢！Beats才20%+。list的index操作时间复杂度
# 为O(1)，list的append操作时间复杂度也为O(1)。list的not in时间复杂度为O(n)，在算上循环，总共时间复杂度为O(n^2)？所以才这么慢吧....


#哈希表，也就是散列表，在Python就是字典
class Solution:
    def TwoSum(self,nums,target):
        """ 
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        if len(nums) <=1: return False
        buff_dict = {}
        for i in range(len(nums)):
            if nums[i] in buff_dict:
                return [buff_dict[nums[i]],i]
            else:
                buff_dict[target-nums[i]]=i