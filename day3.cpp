#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

bool sled_horizontal(char* line, int size, int pos)
{
	char c = *(line + (pos % size));
	return (c == '#') ? true : false;		
}

int main(void)
{
	string line;
	vector<string> treeLines;
	int counter[] = {0,0,0,0,0};
	int treeCounter = 0;
	unsigned long product = 1;	
	while(getline(cin, line))
	{
		treeLines.push_back(line);
	}

	for(int i = 0; i < treeLines.size(); i++){
		treeCounter = 0;
		for(int p = 1; p <= 7; p+= 2)
		{
			line = treeLines[i];
			int pos = i * p;
			if(sled_horizontal( &line[0], line.length(), pos))
				counter[treeCounter]++;		
			treeCounter++;
		}
		if(!(i % 2))
		{
			if(sled_horizontal(&line[0], line.length(), i / 2))
				counter[treeCounter]++;
		}		
	}
	
	for(int i = 0; i < 5; i++)
	{
		product *= counter[i];
	}

	cout << "Trees: "<< product << "\n";	
 
	return 0;	
}
