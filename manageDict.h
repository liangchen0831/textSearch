#ifndef MANAGEDICT_H
#define MANAGEDICT_H


#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "utility.h"

using namespace std;



// tree to store game strategy
struct GuessOrder
{
	char letter;  // letter used to guess
	string noMiss;  // letters not used before this guess
	string board;    // state of board associated to this guess
	list<string> dictionary; 
	// remaining words filtered by previous guesses
	vector<GuessOrder> *link;
	// pointer to a vector of subsequent guess strategies
};
typedef GuessOrder* GOptr;


char get_letter(GOptr ptr);
//return: the most frequent letter in the associated dictionary

void sort_noMiss(GOptr ptr);
//return: ordered letter not used by frequency

void GuessOrder_insert(GOptr ptr);
//side_effect: insert a vector of GuessOrder
//side_effect: initial the first GuessOrder of this vector as
//             a list of words which do not contain ptr -> letter

string removeChar(GOptr ptr);
//return: delete the last guessed letter from the list of unuesd letters

GOptr split_dictionary(GOptr ptr, string board);
//return: pointer to next guess
//side_effect: send words which have same form as board to a subsequent dictionary

vector<GOptr> SplitByLength(ifstream& ifs);
//return: a vector of pointers to GuessOrders splitted by word length

vector< list<string> > get_dictionary(ifstream& ifs);
//return: a vector of dictionaries by splitting the origin dicitionary 
//        based on word length









#endif //MANAGEDICT_H








