#include "utility.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;


int get_freq(const list<string>& dict, char letter){
	
	int freq = 0;

	for(list<string>::const_iterator i = dict.begin();
		i != dict.end(); i++){
		if (is_contained(*i, letter))
			freq++;
	}

	return freq;
}

bool compare(const Letter_Freq& x, const Letter_Freq& y){
		return x.freq > y.freq;
}

bool is_contained(const string& word, char letter){
	

	for (string::const_iterator i = word.begin(); i != word.end(); i++){
		if (*i == letter){
			return true;
			break;
		}
	}

	return false;
}

bool isSame(const string &word, const string &board, char letter){

	string::const_iterator i = word.begin();
	string::const_iterator j = board.begin();

	while (j != board.end()){
		if ( (*j == '$') && (*i == letter) ){
			break;
		} else if ( (*j != '$') && (*j != *i) ){
			break;
		} else{
			i++;
			j++;
		}
	}

	if (j == board.end() && i == word.end())
		return true;
	else
		return false;
}

