#include <iostream>
#include <string>
#include <sstream>
#include <vector>



using namespace std;

#define ROWS 127
#define COLUMNS 7



int getPosition(istream& ss, int lowerbound, int upperbound, int count, const string v)
{
    char c;
    
    for(int i = 0; i < count - 1; i++)
    {
        ss >> c;
       
        if(c == v[0])
            upperbound = upperbound - ((upperbound - lowerbound + 1)/2);
        if(c == v[1] )
            lowerbound = lowerbound + ((upperbound - lowerbound + 1)/2);

    }

    ss >> c;

    if(c == v[0])
        return lowerbound;

    if(c == v[1])
        return upperbound;

    return -1;
}

int main(void)
{
    int seat_map[ROWS][COLUMNS] = {0};
    int row, column;
    int seatId;
    string line;

    while(getline(cin, line))
    {
        stringstream s(line);
        row =  getPosition(s, 0, ROWS, 7, "FB");
        column = getPosition(s, 0, COLUMNS, 3, "LR");
        seat_map[row][column] = (row * 8) + column;
    }

    for(int i=0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if(seat_map[i][j] == 0 && i != 0 && i != ROWS - 1)
            {
                if(j != 0 && j != COLUMNS - 1 && seat_map[i][j-1] != 0 && seat_map[i][j+1] != 0)  
                    cout << "Seat Id: " << (i * 8) + j << "\n";
            }
        }
    }
    


   

    

    return 0;
}