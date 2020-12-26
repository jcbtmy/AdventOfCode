#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>  
using namespace std;

int main(void)
{
    const unsigned int mid = 1010;
    vector<unsigned int> greater;
    vector<unsigned int> smaller; 
    unsigned int num, n1 = 0, n2 = 0, n3 = 0;

    while(cin >> num)
    {
        if(num >= mid)
        {
            greater.push_back(num);
        }
        else
        {
            smaller.push_back(num);
        }
        
    }
    for(int i = 0;  i < smaller.size(); i++)
    {
        num = smaller[i];
        n1 = smaller[i];

        for(int i2 = i + 1; i2 < smaller.size(); i2++)
        {
            n2 = smaller[i2];
            if(n2 + n1 > mid){
                n3 = n2;
            }
            else if(n2 + n3 + n1 == 2020){
                cout << n1 * n2 * n3 << "\n";
                return 0;
            }
            else{
                for(int j = 0; j < greater.size(); j++)
                {
                    if(n1 + n2 + greater[j] == 2020)
                    {
                        cout << n1 * n2 * greater[j] << "\n";
                        return 0;
                    }
                }
            }   
        }
    }
    

}