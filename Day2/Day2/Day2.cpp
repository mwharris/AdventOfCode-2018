#include "pch.h"

#include "LetterCount.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>

using std::unordered_map;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::getline;
using std::set;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

void buildCountsByLetter(unordered_map<char, LetterCount>& countsByLetter)
{
	string::iterator it = alphabet.begin();
	while (it != alphabet.end()) {
		LetterCount c;
		c.count = 0;
		c.letter = *it;
		c.index = -1;

		pair<char, LetterCount> currPair(*it, c);
		countsByLetter.insert(currPair);

		it++;
	}
}

void buildLettersByCount(unordered_map<int, set<char>>& lettersByCount, unordered_map<char, LetterCount>& countsByLetter)
{
	set<char> initialSet;

	string::iterator it = alphabet.begin();
	int index = 0;
	while (it != alphabet.end()) 
	{
		initialSet.insert(*it);
		it++;
	}

	pair<int, set<char>> initPair(0, initialSet);
	lettersByCount.insert(initPair);
}

string trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void read_input(vector<string>& inputs)
{
	//Open our puzzle input file
	ifstream inputFile;
	inputFile.open("PuzzleInput.txt");
	if (inputFile)
	{
		//Read each string into our vector one-by-one
		string word;
		while (getline(inputFile, word))
		{

			inputs.push_back(trim(word));
		}
	}
	//Make sure to close our stream
	inputFile.close();
}

int main()
{
    // Declare int counts for strings with exactly 2 or 3 of any letter
	int twoLetter = 0;
	int threeLetter = 0;

	// Build a map of char -> LetterCount in order to lookup letter counts by char
	unordered_map<char, LetterCount> countsByLetter;
	
	// Build a map of count -> letters in order to check which letters have a specific count
	unordered_map<int, set<char>> lettersByCount;

	// Collect all the strings from our puzzle input
	vector<string> strsToProcess; 
	read_input(strsToProcess);

	// Process every string in the input file
	for (size_t i = 0; i < strsToProcess.size(); i++)
	{
		// Clear our letter counts and references and build new
		countsByLetter.clear();
		buildCountsByLetter(countsByLetter);
		lettersByCount.clear();
		buildLettersByCount(lettersByCount, countsByLetter);

		// Process for every character in the string
		const char* charIt = strsToProcess[i].c_str();
		size_t end = strsToProcess[i].size();
		for (size_t j = 0; j < end; j++)
		{
			char letter = *charIt;

			unordered_map<char, LetterCount>::iterator cblIt = countsByLetter.find(letter);
			if (cblIt != countsByLetter.end())
			{
				// remove it from it's previous location in lettersByCount
				unordered_map<int, set<char>>::iterator oldIt = lettersByCount.find(cblIt->second.count);
				if (oldIt != lettersByCount.end())
				{
					oldIt->second.erase(letter);
				}
				// move it to it's new location in lettersByCount
				unordered_map<int, set<char>>::iterator newIt = lettersByCount.find(cblIt->second.count+1);
				if (newIt != lettersByCount.end())
				{
					newIt->second.insert(cblIt->second.letter);
				}
				// create a new entry for lettersByCount
				else 
				{
					set<char> newSet;
					newSet.insert(cblIt->second.letter);
					pair<int, set<char>> newPair(cblIt->second.count + 1, newSet);
					lettersByCount.insert(newPair);
				}
				// increase this letter's counter
				cblIt->second.count++;
			}

			charIt++;
		}

		// Increment our counts based on our map data
		unordered_map<int, set<char>>::iterator lbcCheck2 = lettersByCount.find(2);
		unordered_map<int, set<char>>::iterator lbcCheck3 = lettersByCount.find(3);
		if (lbcCheck2 != lettersByCount.end() && !lbcCheck2->second.empty())
		{
			twoLetter++;
		}
		if (lbcCheck3 != lettersByCount.end() && !lbcCheck3->second.empty())
		{
			threeLetter++;
		}
	}

	cout << "Words with letters appearing exactly twice: " << twoLetter << endl;
	cout << "Words with letters appearing exactly thrice: " << threeLetter << endl;
	cout << "Chucksum is: " << twoLetter * threeLetter << endl;
}