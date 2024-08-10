#include <bits/stdc++.h>
using namespace std;

class RangeAND
{
    vector<int> arr;
    vector<vector<int>> preBit;
    int size;

    void fillBit(vector<int> &bits, int num)
    {
        int i = 0;
        while (num > 0)
        {
            bits[i++] = num % 2;
            num /= 2;
        }
    }

    void computePreBits()
    {
        preBit.resize(size, vector<int>(32, 0));
        fillBit(preBit[0], arr[0]);
        for (int i = 1; i < size; i++)
        {
            fillBit(preBit[i], arr[i]);
            for (int j = 0; j < 32; j++)
            {
                preBit[i][j] += preBit[i - 1][j];
            }
        }
    }

public:
    RangeAND(vector<int> &inp)
    {
        size = inp.size();
        arr.resize(size);
        copy(inp.begin(), inp.end(), arr.begin());
        computePreBits();
    }

    int getRangeAnd(int i, int j)
    {
        vector<int> bits(preBit[j].begin(), preBit[j].end());
        if (i > 0)
        {
            for (int k = 0; k < 32; k++)
            {
                bits[k] -= preBit[i - 1][k];
            }
        }

        int ans = 0;
        int len = j - i + 1; 
        for (int k = 31; k >= 0; k--)
        {
            ans = ans << 1;
            if (bits[k] == len) ans += 1;
        }
        return ans;
    }
};

int main()
{

    vector<int> nums = {1,6,8,9,7,12};
    int n = nums.size();
    int T = 5;
    int ans = INT_MAX,ANDV;
    RangeAND s1(nums);
    int i=0,j=0;

    while(j<n){
        ANDV = s1.getRangeAnd(i,j);
        ans = min(ans,abs(ANDV-T));
        if(ANDV < T){
            i++;
            if(i>j) j=i;
        }
        else if(ANDV > T) j++;
        else break; 

    }
    cout<<ans;

    return 0;
}