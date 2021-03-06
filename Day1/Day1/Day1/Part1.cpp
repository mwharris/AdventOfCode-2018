#include "stdafx.h"
#include "Part1.h"

using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int find_last_frequency()
{
	ifstream inputFile;
	int frequency = 0;

	//Open our puzzle input file
	inputFile.open("PuzzleInput.txt");
	if (inputFile)
	{
		//Read each int of the file one-by-one
		int change;
		while (inputFile >> change)
		{
			//Print the results of each frequency change
			cout << "Current frequency: " << frequency;
			cout << ", Change is: " << change;
			frequency += change;
			cout << ", Resulting frequency is: " << frequency << endl;
		}
	}
	inputFile.close();
    return frequency;
}