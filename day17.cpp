#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct pos{

    int x;
    int y;
    int z;
    int w;

} typedef Position;

bool in_position_set(Position p, vector<Position>& set)
{
    for(auto& iter: set )
    {
        if( iter.x == p.x && iter.y == p.y && iter.z == p.z && p.w == iter.w)
            return true;
    }

    return false;
}

void add_to_frontier(Position p, vector<Position>& frontier, vector<Position>& explored)
{
    for(int x = -1; x < 2; x++)
    {
        for(int y = -1; y < 2; y++)
        {
            for(int z = -1; z < 2; z++)
            {
                for(int w = -1; w < 2; w++)
                {
                    Position new_p;
                    new_p.x = p.x + x;
                    new_p.y = p.y + y;
                    new_p.z = p.z + z;
                    new_p.w = p.w + w;

                    if(!in_position_set(new_p, frontier))
                        frontier.push_back(new_p);
                }
            }
        }
    }
}


void lifedeathCycle(vector<Position>& oldCells, vector<Position>& newCells, vector<Position>& frontier)
{

    for(auto& iter : frontier)
    {
        int count = 0;

        for(int x = -1; x < 2; x++)
        {
            for(int y = -1; y < 2; y++)
            {
                for(int z = -1; z < 2; z++)
                {
                    for(int w = -1; w < 2; w++)
                    {    
                        if(!x && !y && !z && !w)
                            continue;

                        Position p;
                        p.x = iter.x + x;
                        p.y = iter.y + y;
                        p.z = iter.z + z;
                        p.w = iter.w + w;

                        if(in_position_set(p, oldCells))
                            count++;
                    }
                }
            }
        }

        if(count == 3 && !in_position_set(iter, oldCells)) 
            newCells.push_back(iter);

        else if((count == 3 || count == 2) && in_position_set(iter, oldCells))
            newCells.push_back(iter);

    }
}


void cycle(vector<Position>& active_cells)
{
    vector<Position> new_active_cells;
    vector<Position> frontier;
    Position curr_p;

    for(auto& iter : active_cells)
    {    
        add_to_frontier(iter, frontier, active_cells);     
    }
    lifedeathCycle(active_cells, new_active_cells, frontier);
    active_cells.clear();
    active_cells = new_active_cells;
}


int main(void)
{
    string line;
    vector<Position> active_cells;
    int y = 0 ;


    while(getline(cin, line))
    {
        for(int i = 0; i < line.length(); i++)
        { 
            Position p;
            p.x = i;
            p.y = y;
            p.z = 0;
            p.w = 0;
            
            if(line[i] == '#')
                active_cells.push_back(p);
        }   
        y++;
    }

   
    for(int i = 0; i < 6; i++)
        cycle(active_cells);

    cout << "Active Cells: " << active_cells.size() << endl;
   

   

    return 0;
}