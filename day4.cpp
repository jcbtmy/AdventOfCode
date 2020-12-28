#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <regex>

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

bool valid_eyecolor(string color)
{
		string colors[7] = {"amb", "blu",
							"brn", "gry",
							"grn", "hzl",
							"oth"};

		
		if(color.length() != 3)
			return false;

		for(int i = 0; i < 8; i++)
		{
			if(color.compare(colors[i]) == 0)
				return true;
		}

		return false;

}

bool valid_pid(string id)
{
	if(id.length() != 9)
		return false;
	
	for(auto iter = id.begin(); iter < id.end(); iter++)
	{
		if(!isdigit(*iter))
			return false;
	}

	return true;
}

bool valid_four_digit(string num, int max, int min)
{
	if(num.length() != 4)
		return false;
	
	for(int i = 0; i < num.length(); i++)
	{
		if(!isdigit(num[i]))
			return false;
	}

	return (atoi(num.c_str()) > max || atoi(num.c_str()) < min) ? false : true;
}
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
	for(int i = 0; i < 8; i++)
	{
			cout << "| " << i << "->" << passport[i] << "|\n";
			if(i != CID && passport[i].empty())
				return false;
			
			if( i == EYR && !valid_four_digit(passport[i], 2030, 2020))
				return false;

			if( i == BYR &&	!valid_four_digit(passport[i] , 2002, 1920 ))
				return false;

			if( i == IYR && !valid_four_digit(passport[i], 2020, 2010))
				return false;

			if( i == HGT)
			{
				string units = passport[i].substr(passport[i].length() - 2, passport[i].length());
				string snum = passport[i].substr(0, passport[i].length() - 2);
				int num;

				if(units.compare("cm") == 0){
					num = atoi(snum.c_str());
					if(num < 150 || num > 193)
						return false;
				}
				else if(units.compare("in") == 0){
					num = atoi(snum.c_str());
					if(num < 59 || num > 76)
						return false;
				}
				else{
					return false;
				}

			}

			if( i == HCL )
			{
				regex e("(^#)([0-9a-f]{6})");
				smatch match;

				if(!regex_search(passport[i], match, e))
				{
					return false;
				}
				
			}
			if(i == ECL && (!valid_eyecolor(passport[i])))
				return false;
			
			if(i == PID && (!valid_pid(passport[i])))
				return false;
			
	}
	cout << "Valid\n";
	return true;
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
