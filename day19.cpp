#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <boost/regex.hpp>


using namespace std;

struct Rule{
    char op;
    vector<int> rules;

} typedef Rule;



void addRule(string line, unordered_map<int, Rule>& rules)
{
    Rule newRule;
    string arg;
    string num = line.substr(0, line.find(':'));

    stringstream ss(line.substr(line.find(':') + 2, line.length()));
    
    while(getline(ss, arg, ' '))
    {
        if(arg.compare("|") == 0)
        {
            newRule.rules.push_back(-1);
            newRule.op = 0;
        }
        else if(arg.find("a") != string::npos)
        {
            newRule.op = 'a';
        }
        else if(arg.find("b") != string::npos)
        {   
            newRule.op = 'b';
        }
        else{
            newRule.rules.push_back(atoi(arg.c_str()));
        }
    }

    rules[atoi(num.c_str())] = newRule;
 
}

string getReg(int ruleNum ,unordered_map<int, Rule>& rules)
{
    string retReg;
    Rule rule = rules[ruleNum];

    if(rule.op == 'a')
        return "a";
    if(rule.op == 'b')
        return "b";


    retReg += "(";

    for(int i = 0; i < rule.rules.size(); i++)
    {
        if(rule.rules[i] < 0){
            retReg += "|";
        }
        else{
            retReg += getReg(rule.rules[i],rules);
        }
    }

    retReg += ")";

    return retReg;
}

int main(void)
{
    int count = 0;
    string line;
    string reg;
    unordered_map<int, Rule> rules;

    while(getline(cin, line))
    {
        if(line.empty())
            break;
        addRule(line, rules);
    }
    
    string rule0 = getReg(0, rules);
    string rule42 = getReg(42, rules);
    string rule31 = getReg(31, rules);

    boost::regex r0(rule0);
    boost::regex r42(rule42);
    boost::regex r31(rule31);
    boost::match_results<string::const_iterator> matched;
    string res;
    int chunk42, chunk31;

    while(getline(cin, line))
    {   
        res.clear();
        chunk42 = 0;
        chunk31 = 0;
        bool it = false;

        string::const_iterator start = line.begin();
        string::const_iterator end = line.end();

        while(boost::regex_search(start, end, matched, r42))
        {    
           if(matched[0].matched){
            
                if(matched.position() == 0)
                {
                    start = matched[0].second;
                    chunk42++;
                    res += matched[0];
                }
                else{
                    break;
                }
           }
        }

        while(boost::regex_search(start, end, matched, r31))
        {
            if(matched[0].matched){
            
                if(matched.position() == 0)
                {
                    start = matched[0].second;
                    chunk31++;
                    res += matched[0];
                }
                else{
                
                    break;
                }
           }
        }


       
        if(start == end &&  (0 < chunk31) && (chunk31 < chunk42) && line.compare(res) == 0)
        {
            count++;
        }
    
    }

   
    cout << count << endl;

    return 0;
}