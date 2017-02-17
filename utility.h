#ifndef UTILITY_H
#define UTILITY_H


#include <cstdlib>
#include <list>
#include <string>
#include <vector>
#include <fstream>


// data struct used to order letters by frequency
struct Letter_Freq
{
	char letter;
	int freq;
};

int get_freq(const std::list<std::string>& dict, char letter);
//return: frequency of letter in dict

bool is_contained(const std::string& word, char letter);
//return: if letter is contained in word

bool isSame(const std::string &word, const std::string &board, char letter);
//return: if word has the same form as board

bool compare(const Letter_Freq& x, const Letter_Freq& y);
//return: if letter x is more frequent than y




int get_freq(const std::list<std::string>& dict, char letter){
	using namespace std;
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

bool is_contained(const std::string& word, char letter){
	using namespace std;

	for (string::const_iterator i = word.begin(); i != word.end(); i++){
		if (*i == letter){
			return true;
			break;
		}
	}

	return false;
}

bool isSame(const std::string &word, const std::string &board, char letter){

	std::string::const_iterator i = word.begin();
	std::string::const_iterator j = board.begin();

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













#endif // UTILITY_H