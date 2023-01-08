/* 题目：给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:
给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

作者：chenlele
链接：https://leetcode.cn/problems/two-sum/solution/liang-shu-zhi-he-by-gpe3dbjds1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 */



#include <bits/stdc++.h>
using namespace std;

//暴力解法：
class Solution{
    public:
        vector<int>TwoSum(vector<int> &nums,int target){
            int i,j;
            for(i=0;i<nums.size()-1;i++){
                for(j=i+1;j<nums.size();j++){
                    if(nums[i]+nums[j]==target) return {i,j};
                }
            }
            return {};
        }
};
//PS:该方法简单但是时间复杂度为 O(n^2^)。空间复杂度为 O(1)O(1);运行速度慢且内存空间消耗大


//两遍Hash table
class Solution{
	public:
		vector<int>TwoSum(vector<int> &nums,int target){
			map<int,int> a; //建立hash表存放数组元素
			vector<int> b(2,-1); //存放结果
			for(int i=0;i<nums.size();i++) 
				a.insert(map<int,int>::value_type(nums[i],i));
			for(int i=0;i<nums.size();i++){
				if(a.count(target-nums[i])>0&&(a[target-nums[i]]!=i)){
					//判断是否找到目标元素且目标元素不是本身
					b[0]=i;
					b[1]=a[target-nums[i]];
					break; 
				}
			}
			return b;
	    }
};
//PS:该方法用 map 实现，map 是 STL 的一个关联容器，它提供一对一（其中第一个可以称为关键字，\
每个关键字只能在 map 中出现一次，第二个可能称为该关键字的值）的数据处理能力


//一遍hash table
class Solution{
    public:
        vector<int>TwoSum(vector<int> &nums,int target){
            map<int,int> a;
            vector<int> b(2,-1);
            for(int i=0;i<nums.size();i++){
                if(a.count(target-nums[i])>0){
                    b[0]=a[target-nums[i]];
                    b[1]=i;
                    break;
                }
                a[nums[i]]=i;//反过来放入map中，用来获取结果下标
            }
            return b;
        }
}
//PS:改进：在进行迭代并将元素插入到表中的同时，我们还会回过头来检查表中是否已经存在当前元\
素所对应的目标元素。如果它存在，那我们已经找到了对应解，并立即将其返回



