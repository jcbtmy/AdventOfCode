#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>



using namespace std;



int main(void)
{
    string num;
    vector<int> map;
    unordered_map<int, int> seen;
    int iter = 0;

    while(getline(cin, num, ','))
    {
        int n = atoi(num.c_str());
        map.push_back(n);
        seen[n] = iter;
        iter++;
    }

    while(iter < 30000000)
    {
        auto found = seen.find(map[iter - 1]);
        if(found != seen.end()){
            int n = iter - seen[map[iter - 1]] - 1 ;
            map.push_back(n);
            seen[map[iter - 1]] = iter - 1;
        }
        else{
            map.push_back(0);
            seen[map[iter - 1]] = iter- 1;
        }
        iter++;
    }

    cout << map[iter-1] << endl;

    return 0;
}