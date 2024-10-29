class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> v(nums.size());
        int res = 1;
        v[0]=1;
        for (int i = 1; i < nums.size(); i++)
        {
            int m = 0;
            for (int j = i-1; j >= 0; j--)
            {
                if (nums[i] > nums[j])
                {
                    m = max(m, v[j]);
                }
            }
            v[i] = 1+m;
            res = max(res, v[i]);
        }
        return res;

    }
};