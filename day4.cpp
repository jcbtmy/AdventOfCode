#include <iostream>
#include <vector>
#include <array>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	KEYS_LENGTH,
};


int key_to_int(string str)
{
	if(str.compare("byr") == 0)
		return BYR;

	if(str.compare("iyr") == 0)
		return IYR;

	if(str.compare("eyr") == 0)
		return EYR;

	if(str.compare("hgt") == 0)
		return HGT;

	if(str.compare("hcl") == 0)
		return HCL;
	
	if(str.compare("ecl") == 0)
		return ECL;
	
	if(str.compare("pid") == 0)
		return PID;
	
	if(str.compare("cid") == 0)
		return CID;

	return -1;  
}

bool valid_passport(vector<string> &passport)
{
	cout << "Passport\n";
	bool valid = true;
	for(int i = 0; i < 8; i++)
	{
			cout << "| " << i << "->" << passport[i] << "|\n";
			if(i != CID && passport[i].empty()){
				valid = false;
			}
			if( i == EYR && (stoi(passport[i]) <= 2020) || (stoi(passport[i]) >= 2030))
				valid = false;

			if( i == BYR && (stoi(passport[i]) <= 1920 ) || (stoi(passport[i]) >= 2002))			
				valid = false;
			
			if( i == IYR && (stoi(passport[i]) <= 2010) || (stoi(passport[i]) >= 2020 ))
				valid = false;

			
	}
	return valid;
}

void clear_passport(vector<string> &passport)
{
	for(auto iter = passport.begin(); iter < passport.end(); iter++)
		(*iter).clear();
}


int main(void)
{
	int key, passportCounter = 0;
	string entry;
	string line;
	vector<string> passport(8);
	clear_passport(passport);
	

	while(getline(cin, line))
	{	
		if(line.empty())
		{
			if(valid_passport(passport))
				passportCounter++;
			clear_passport(passport);
		}
		stringstream ss(line);
		while(getline(ss, entry, ' '))
		{
			key = key_to_int(entry.substr(0, entry.find(':')));
			passport[key] = string(entry.substr(entry.find(':') + 1, entry.length()));
		}
	}


	cout << "Valid Passports : " << passportCounter << "\n";
	return 0;
}
