#include <iostream>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum keys{
	BYR,
	IYR,
	EYR,
	HGT,
	HCL,
	ECL,
	PID,
	CID,
};



int key_to_int(string& str)
{
	if(str.compare("ecl") == 0)
		return ECL;
	return -1;  
}


int main(void)
{
	string line;
	while(getline(cin, line))
	{
		if(line.compare("") != 0)
			cout << line << "\n";
	}

	return 0;
}
