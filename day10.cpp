#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>



using namespace std;



int main(void)
{
    vector<int> nums;
    vector<long int> valid;
    int n;

    while(cin >> n)
        nums.push_back(n);

    
    
    sort(nums.begin(), nums.end());
    nums.insert(nums.begin(), 0);
    nums.push_back(nums.back() + 3 );
    valid.push_back(1);

    for(int i = 1; i < nums.size(); i++)
    {
        long int sum = 0;
        for(int j = i - 1 ; j > -1; j--)
        {
            int temp = nums[i] - nums[j];
            if(temp <= 3){
                sum += valid[j];
            }
            else{
                break;
            }
            
        }

        valid.push_back(sum);

    }


    cout << valid.back() << endl;    
    
    return 0;
}