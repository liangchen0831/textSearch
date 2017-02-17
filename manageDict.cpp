#include "utility.h"
#include "manageDict.h"


#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>


std::vector<GOptr> SplitByLength(std::ifstream& ifs){
	using namespace std;
	vector< list<string> > dictionary = get_dictionary(ifs);
	vector<GOptr> Index;

	for (int i = 0; i < 12; i++){
		
		GOptr Index_root = new GuessOrder;

		Index_root -> noMiss = "abcdefghijklmnopqrstuvwxyz";
		Index_root -> dictionary = dictionary[i];
		Index_root -> letter = '\0';
		Index_root -> link = NULL;

		Index.push_back(Index_root);
	}

	vector< list<string> >().swap(dictionary);

	return Index;
}

void sort_noMiss(GOptr ptr){
	using namespace std;

	vector<Letter_Freq> list_freq;

	for (string::const_iterator i = (ptr->noMiss).begin();
			i != (ptr->noMiss).end(); i++){
		Letter_Freq tmp;
		tmp.letter = *i;
		tmp.freq = get_freq(ptr->dictionary, *i);
		list_freq.push_back(tmp);
	}

	sort(list_freq.begin(), list_freq.end(), compare);

	string::iterator j = (ptr->noMiss).begin();
	vector<Letter_Freq>::iterator k = list_freq.begin();

	for (; k != list_freq.end(); j++, k++){
		*j = k -> letter;
	}

	return;
}




char get_letter(GOptr ptr){
	using namespace std;

	vector<Letter_Freq> list_freq;

	for (string::const_iterator i = (ptr->noMiss).begin();
			i != (ptr->noMiss).end(); i++){
		Letter_Freq tmp;
		tmp.letter = *i;
		tmp.freq = get_freq(ptr->dictionary, *i);
		list_freq.push_back(tmp);
	}

	sort(list_freq.begin(), list_freq.end(), compare);

	return list_freq[0].letter;
}


void GuessOrder_insert(GOptr ptr){
	using namespace std;
	ptr -> link = new vector<GuessOrder>;

	char letter = ptr -> letter;
	list<string> dict_new;

	list<string>::iterator iter = (ptr->dictionary).begin();

	while(iter != (ptr->dictionary).end()){
		if (!is_contained(*iter, letter)){
			dict_new.push_back(*iter);	
			iter = (ptr -> dictionary).erase(iter);
		} else{
			iter++;
		}
	}

	GOptr tmp = new GuessOrder;

	(*(ptr -> link)).push_back(*tmp);

	(*(ptr -> link))[0].letter = '\0';
	(*(ptr -> link))[0].dictionary = dict_new;
	(*(ptr -> link))[0].link = NULL;
	(*(ptr -> link))[0].noMiss = removeChar(ptr);
}


std::string removeChar(GOptr ptr){
	using namespace std;
	string tmp = ptr -> noMiss;
	tmp.erase( remove(tmp.begin(), tmp.end(), ptr -> letter), tmp.end());
	return tmp;
}





std::vector< std::list<std::string> > get_dictionary(std::ifstream& ifs){
	using namespace std;
	list<string> dict;
	vector< list<string> > dictionary (12, dict);
	string word;
	int length = 0;

	while (getline(ifs, word)){
		length = word.length();
		if (length <= 5)
			dictionary[0].push_back(word);
		else if (length > 15)
			dictionary[11].push_back(word);
		else
			dictionary[(length-5)].push_back(word);
	}	 

	return dictionary;
}



GOptr split_dictionary(GOptr ptr, std::string board){

	std::list<std::string> dict_new;
	std::list<std::string>::iterator itr = (ptr->dictionary).begin();

	while (itr != (ptr->dictionary).end()){
		if (isSame(*itr, board, ptr -> letter)){
			dict_new.push_back(*itr);
			itr = (ptr->dictionary).erase(itr);
		} else{
			itr++;
		}
	}

	GOptr tmp = new GuessOrder;
	tmp -> noMiss = removeChar(ptr);

	(*(ptr -> link)).push_back(*tmp);

	ptr = &(*(ptr -> link)).back();

	ptr -> dictionary = dict_new;
	ptr -> letter = '\0';
	ptr -> link = NULL;
	ptr -> board = board;
	
	return ptr;
}


















