#include "stdafx.h"
#include <iostream>

#include "Part1.h"
#include "Part2.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int partNum;
	cout << "Run Part 1 or Part 2?: ";
	cin >> partNum;

	int answer;
	if (partNum == 1) 
	{
		answer = find_last_frequency();
	}
	else if (partNum == 2)
	{
		answer = find_dupe_frequency();
	}

	cout << "ANSWER IS: " << answer << endl;

	system("PAUSE");
	return 0;
}