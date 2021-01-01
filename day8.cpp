#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>

enum instruction
{
    NOP,
    ACC,
    JMP
};

struct operation{

       int instruction;
       int value;

} typedef Operation;

using namespace std;

int getInstruction(string& op)
{
    if( op.compare("nop") == 0)
        return NOP;
    
    if(op.compare("acc") == 0)
        return ACC;
    
    if(op.compare("jmp") == 0)
        return JMP;
    
    return -1;
}


int main(void)
{
    vector<Operation> ops_list , copy;
    vector<int> jump_list;
    int* ops_executed;
    int accumulator = 0, iter = 0;
    string line;
  

    while(getline(cin, line))
    {
        Operation new_op;
        string op = line.substr(0, 3);
        string acc =line.substr(4, line.length());
        new_op.instruction = getInstruction(op);
        new_op.value = atoi(acc.c_str());
        ops_list.push_back(new_op);
        if(new_op.instruction == JMP || new_op.instruction == NOP)
            jump_list.push_back(iter);
        iter++;
    }

    iter = 0;
    ops_executed = new int[ops_list.size()];
    memset(ops_executed, 0 , sizeof(int) * ops_list.size());
    copy = ops_list;


    while( iter < ops_list.size())
    {
        if(ops_executed[iter] == 1)
        {
            memset(ops_executed, 0 , sizeof(int) * ops_list.size());
            copy.clear();
            copy = ops_list;
            int pos = jump_list.back();
            copy[pos].instruction = (copy[pos].instruction == JMP) ? NOP : JMP;
            jump_list.pop_back();
            iter = 0;
            accumulator = 0;
        }
    
        ops_executed[iter] = 1;
        
        switch(copy[iter].instruction)
        {
            case NOP:
                iter++;
                break;
            case ACC:
                accumulator +=copy[iter].value;
                iter++;
                break;
            case JMP:
                iter += copy[iter].value;
                break;
        }
    }

    delete [] ops_executed;

    cout << "Accumulator : "<< accumulator << endl;


    return 0;
}