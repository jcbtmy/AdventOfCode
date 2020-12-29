#include <iostream>
#include <string>
#include <sstream>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int q_to_int(char c)
{
    const int start = 97;

    return (int)c - 97;
}



void update_count(int arr[], int arr_size, int* counter, int group_size)
{
    
    for(int i = 0; i < arr_size; i++)
    {
        if(arr[i] && arr[i] == group_size)
                *counter = *counter + 1;
    }
}


int main(void)
{
    const int alphabet_size = 26;
    int alphabet_arr[alphabet_size];
    int counter = 0;
    int g_size = 0;
    char c, last_char;

    memset(alphabet_arr, 0, sizeof(alphabet_arr));

    while(cin.get(c))
    {
        if(c == '\n' && last_char == '\n'){
            update_count(alphabet_arr, alphabet_size, &counter, g_size);
            memset(alphabet_arr, 0, sizeof(alphabet_arr));
            g_size = 0;
        }
        if(c == '\n' && last_char != '\n')
            g_size++;
        if(c != '\n')
        {
            int pos = q_to_int(c);
            alphabet_arr[pos]++;
        }


        last_char = c;

    }

    cout << "Question Count: " << counter <<"\n";


    return 0;
}