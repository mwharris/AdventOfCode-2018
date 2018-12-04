#include "stdafx.h"
#include "Part2.h"

using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::unordered_set;
using std::vector;
using std::back_inserter;

void read_input(vector<int>& inputs)
{
	//Open our puzzle input file
	ifstream inputFile;
	inputFile.open("PuzzleInput.txt");
	if (inputFile)
	{
		//Read each int into our vector one-by-one
		int change;
		while (inputFile >> change)
		{
			inputs.push_back(change);
		}
	}
	//Make sure to close our stream
	inputFile.close();
}

bool process_inputs(vector<int>& inputs, unordered_set<int>& set, int& currFreq)
{
	vector<int>::iterator it = inputs.begin();
	while (it != inputs.end())
	{
		//Get the current frequency change
		int change = *it;
		currFreq += change;
		//Check for a duplicate frequency
		if (set.count(currFreq) == 1)
		{
			return true;
		}
		else
		{
			set.insert(currFreq);
		}
		//Move our iterator
		it++;
	}
}

int find_dupe_frequency()
{
	int frequency = 0;
	int answer = -1;
	bool foundDupe = false;
	
	//Setup an unordered set to keep track of old frequencies
	unordered_set<int> freqSet;
	freqSet.insert(frequency);

	//Setup and read our inputs into a vector
	vector<int> inputs;
	read_input(inputs);

	//Loop until we find a duplicate frequency
	while (!foundDupe)
	{
		//Process the entire list of inputs checking for a dupe
		if (process_inputs(inputs, freqSet, frequency))
		{
			foundDupe = true;
			answer = frequency;
		}
		//Didn't find one, restart
		else
		{
			cout << "No dupe found! Retrying..." << endl;
		}
	}

	return answer;
}