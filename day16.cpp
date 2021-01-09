#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <climits>
#include <cstring>
#include <algorithm>



using namespace std;


struct Rule{

    string name;
    int c1[2];
    int c2[2];

} typedef Rule;



void create_rule(string line, vector<Rule>& rules)
{
    Rule newRule;
    string first, second, set;

    newRule.name = string(line.substr(0, line.find(':')));

    set = line.substr(line.find(':') + 2, line.length());
    first = set.substr(0, set.find('-'));
    newRule.c1[0] = atoi(first.c_str());
    
    second = set.substr(set.find('-') + 1, set.find(' ') );
    newRule.c1[1] = atoi(second.c_str());
  
    set = set.substr(set.find("or") + 2, set.length());

    first = set.substr(0, set.find('-'));
    newRule.c2[0] = atoi(first.c_str());

    second = set.substr(set.find('-') + 1, set.length());
    newRule.c2[1] = atoi(second.c_str());


    rules.push_back(newRule);
  
}


void findPos(vector<vector<Rule*>>& rules)
{   
    vector<int> explored;
    vector<Rule*>::iterator f;
    bool exploring = true;
    int counter;
    Rule* start;
    int currentColumn;
    

    while(exploring)
    {
        counter = 0;
        
        for(int i = 0; i < rules.size(); i++)
        {
            if( (rules[i].size() == 1) && (find(explored.begin(), explored.end(),i) == explored.end()))
            {       
                    currentColumn = i;
                    start = rules[i][0];
                    explored.push_back(i);
                    break;
            }
        }

        for(int i = 0; i < rules.size(); i++)
        {
            if( ((f = find(rules[i].begin(), rules[i].end(),start)) != rules[i].end()) &&  (i != currentColumn) )
            {
                rules[i].erase(f);
            }
            counter += rules[i].size();
        }

        if(counter == rules.size())
            exploring = false;
    }

}

unsigned long getProduct(vector<vector<Rule*>> rules, string ticket, string searchString)
{
    unsigned long ret = 1;
    int iter = 0;
    stringstream ss(ticket);
    string num;

    while(getline(ss, num, ','))
    {
        int n = atoi(num.c_str());
        if(rules[iter][0]->name.find(searchString) != string::npos)
        {
            ret *= n;
        }
        iter++;
    }
    return ret;
}



int main(void)
{
    string line, myTicket;
    vector<Rule> rules;
    vector<vector<Rule*>> positionsRules;
    vector<vector<int>> validTickets;

    unsigned long sum = 1;

    while(getline(cin, line))
    {
        if(line.empty())
            break;
          
        create_rule(line, rules);

    }

    for(int i = 0; i < 4; i++)
    {
        getline(cin, line);
        if(i == 1)
        {
            myTicket = string(line);
        }
    }

    for(int i = 0; i < rules.size(); i++)
    {
        vector<Rule*> l;

        for(int j = 0; j < rules.size(); j++)
        {
            l.push_back(&(rules[j]));
        }
        positionsRules.push_back(l);
    }

    while(getline(cin, line))
    {
        stringstream ss(line);
        
        vector<int> ticket;
        while(getline(ss, line, ','))
        {
            int n = atoi(line.c_str());
            bool valid = false;

            for( int i = 0; i < rules.size(); i++)
            {
                
                if( (rules[i].c1[0] <= n && rules[i].c1[1] >= n ) || (rules[i].c2[0] <= n && rules[i].c2[1] >= n))
                {
                    valid = true;
                }
            }
            if(valid){
                ticket.push_back(n);
            }
            else{
                sum += n;
            }

        }
        if(ticket.size() == rules.size())
            validTickets.push_back(ticket);
    
        ticket.clear();

    }

    for(int i = 0 ; i < validTickets.size(); i++)
    {
        for(int j = 0; j < validTickets[i].size(); j++)
        {
            int n = validTickets[i][j];

            for(int w = 0; w < positionsRules[j].size();)
             {
                Rule* rule = positionsRules[j][w];

                if((rule->c1[0] <= n && rule->c1[1] >= n ) || (rule->c2[0] <= n && rule->c2[1] >= n))
                {
                    w++;
                }
                else{
                    vector<Rule*>& r = positionsRules[j];
                    r.erase( r.begin() + w);
                }
            }
        }
    }

    findPos(positionsRules);

    sum = getProduct(positionsRules, myTicket, string("departure"));

    cout << sum << endl;

    return 0;
}