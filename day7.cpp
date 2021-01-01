#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

struct Bag{
    string color;
    vector<Bag*> parents;
    vector<Bag*> children;
    unordered_map<Bag*, int> edgeToChild;

} typedef Bag;

int bagWalk(Bag* bag)
{
    static vector<Bag*> explored;
    vector<Bag*>::iterator iter, finder;
    vector<Bag*> bags = bag->parents;
    int i = 0;

    if( find(explored.begin(), explored.end(), bag) != explored.end())
        return 0;

    explored.push_back(bag);

    if(bag->parents.empty())
    {
        return 1;
    }
    
    for(iter = bags.begin(); iter != bags.end(); iter++ )
    {
            i += bagWalk((*iter));
    }
    
    return i + 1;
}

int searchBags(Bag* bag)
{
    int i = 0;
    static vector<Bag*> explored;
    vector<Bag*>::iterator iter, finder;
    vector<Bag*> bags = bag->children;

    if(find(bags.begin(), bags.end(), bag) != bags.end())
        return 0;

    explored.push_back(bag);

    if(bags.empty())
        return 0;
    
    for(iter = bags.begin(); iter != bags.end(); iter++)
    {   
        int k = bag->edgeToChild[(*iter)];
        i += k + k * searchBags((*iter));
    }

    return i;
}

string getColor(string& line)
{
    return string(line.substr(0, line.find("bag") -1 ));
}

void addToBags(string& name, unordered_map<string, Bag*>& bags)
{
    if(bags.find(name) == bags.end()){
        bags[name] = new Bag;
        bags[name]->color = name;
    }
}

void collectBags(string line, unordered_map<string, Bag*>& bags)
{
    const string contain = "contain";
    string child;
    stringstream ss;
    size_t pos = line.find(contain);
    string parent = getColor(line);

    addToBags(parent, bags);
    line = line.substr(pos + contain.length(), line.length()); 

    if(line.compare(" no other bags.") == 0)
        return;
  
    ss << line;

    while(getline(ss, child, ','))
    {   
        int n = stoi(child.substr(1, 2));
        child = child.substr(3, child.length());
        child = getColor(child);
    
        addToBags(child, bags);
        
        bags[parent]->children.push_back(bags[child]);
        bags[child]->parents.push_back(bags[parent]);
        bags[parent]->edgeToChild[bags[child]] = n;
    }   


}

void takeOutTrashBags(unordered_map<string, Bag*>& bags)
{
    for(auto& bag : bags)
        delete bag.second;
}

int main(void)
{
    unordered_map<string, Bag*> bags;
    string line;
    while(getline(cin, line))
    {  
       collectBags(line, bags);
    }

    //cout << bagWalk(bags["shiny gold"]) -1 << endl;
    cout << searchBags(bags["shiny gold"]) << endl;
    takeOutTrashBags(bags);
    return 0;
}