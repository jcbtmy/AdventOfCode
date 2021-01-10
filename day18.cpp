#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


long evaluate_expression( stringstream & ss)
{
    long expression_value = 0;
    char c, operation;
    while(ss >> c)
    {
        switch(c){

            case '(':
            
                if(operation == '+')
                {
                    expression_value += evaluate_expression(ss);
                }
                else if( operation == '*')
                {
                    //expression_value *= evaluate_expression(ss);
                }
                else{
                    expression_value = evaluate_expression(ss);
                }
                break;

            case '+':
                operation = c;
                break;
            
            case '*':
                expression_value  *= evaluate_expression(ss);
                return expression_value;

            case ')':
                return expression_value;

            default:
                if(isdigit(c))
                {
                    int n = c - '0';
                    if(operation == '+')
                    {
                        expression_value += n;
                    }
                    else if(operation == '*')
                    {

                    }
                    else{
                        expression_value = n;
                    }
                }
                break;
        }
    }

    return expression_value;
}


int main(void)
{
    string line;
    long sum = 0;
    while(getline(cin, line))
    {
        stringstream ss(line);
        sum += evaluate_expression(ss);
    }

    cout << "Total Sum : " << sum << endl;
    return 0;
}