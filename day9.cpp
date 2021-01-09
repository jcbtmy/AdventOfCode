#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <climits>

using namespace std;

bool sumExist(list<unsigned long>& lv, unsigned long num)
{
    for(auto& i: lv)
    {
        for(auto& j : lv)
        {    
                if((i != j ) && (i + j == num))
                    return true;
        }
    }
 
    return false;
}

unsigned long sum_min_max(list<unsigned long>& lv)
{
    unsigned long min = ULLONG_MAX;
    unsigned long max = 0;

    for(auto& iter: lv)
    {
        if(iter < min)
        {
            min = iter;
        }
        else if(iter > max)
        {
            max = iter;
        }
    }
    return max + min;

}

unsigned long sumofList(list<unsigned long>& lv)
{
    unsigned long sum = 0;

    for(auto& iter: lv)
    {
        sum += iter;
    }
    return sum;
}


int main(void)
{
    unsigned long num;
    unsigned long search_num = 0;
    list<unsigned long> nums;
    list<unsigned long> history;
    string line;

    for(int i = 0; i < 25; i++)
    {
        getline(cin, line);
        num = stoul(line, nullptr, 0);
        nums.push_back(num);
        history.push_back(num);
    }

    while(getline(cin, line))
    {
        num = stoul(line, nullptr, 0);
        if(!sumExist(nums, num) && !search_num )
        {
            cout << "First Num: " << num << "\n";
            search_num = num;
        }
        history.push_back(num);
        nums.pop_front();
        nums.push_back(num);    
    }

    nums.clear();
    auto iter = history.begin();

    while(iter != history.end())
    {
        unsigned long sum = sumofList(nums);

        if(sum == search_num)
        {
            cout << "Found Sum Set: " << sum_min_max(nums) << "\n";
            break;
        }
        else if(sum < search_num)
        {
            nums.push_back(*iter);
            iter++;
        }
        else{
            nums.pop_front();
        }
    }

    return 0;
}