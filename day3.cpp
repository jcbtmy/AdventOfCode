#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct pos {
    int x;
    int y;
} typedef position;

char sledHorizontal(char* line, int line_len,int *x_pos){
    int currpos = *x_pos;
    *x_pos += 3;
    return *(line + (currpos % line_len));
}



int main(void)
{

    string line;
    char tree;
    position sledPos;
    vector<position> treePositions;
    vector<string> treeLine;

    sledPos.x = 0;
    sledPos.y = 0;

    while(getline(cin, line))
    {
        treeLine.push_back(line);
    }
    
    for(int i = 0; i < treeLine.size(); i++)
    {
        sledPos.y = i;

        string line = treeLine[i];
        tree = sledHorizontal(&line[0], line.length(), &sledPos.x );

        if(tree == '#')
            treePositions.push_back(sledPos);
    }

    cout << "Trees on Path : " << treePositions.size() << "\n";


    return 0;
}

