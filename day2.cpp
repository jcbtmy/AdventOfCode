#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <regex>
#include <string>


using namespace std;

bool valid_pwd(char* password, int high, int low, char c)
{
    bool value = false;

    if(*(password + low - 1) == c)
        value = !value;
    if(*(password + high - 1) == c)
        value = !value;
  
    return value;
}

int main(void)
{
    string line, pwd;
    char password[100] = {0};
    char reg[20] = {0};
    uint valid_counter = 0;
    int low, high;
    char c;


    while(getline(cin, line))
    {
        sscanf(line.c_str(), "%d-%d %c: %s", &low, &high, &c, password); 
        if(valid_pwd(password, high, low, c ))
            valid_counter++;
        
    }
    cout << "Valid Passwords " << valid_counter << "\n";

}