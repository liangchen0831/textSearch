#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <list>
#include <string>
#include <vector>
#include <fstream>

using namespace std;




// data struct used to order letters by frequency
struct Letter_Freq
{
	char letter;
	int freq;
};

int get_freq(const list<string>& dict, char letter);
//return: frequency of letter in dict

bool is_contained(const string& word, char letter);
//return: if letter is contained in word

bool isSame(const string &word, const string &board, char letter);
//return: if word has the same form as board

bool compare(const Letter_Freq& x, const Letter_Freq& y);
//return: if letter x is more frequent than y


#endif //UTILITY_H







