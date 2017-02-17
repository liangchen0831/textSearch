#ifndef GUESSPROC_H
#define GUESSPROC_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

#include "utility.h"
#include "manageDict.h"


bool guess(const std::string& Testword, std::vector<GOptr> root);
//return: if the Testword is guessed correctly

GOptr guess(const std::string& Testword, GOptr, int& Num_blank, int& Num_missed);
//return: pointer to next guess
//side_effect: select one letter from not uesed letters, Num_missed++ if
//             this letter is not contained, Num_blank-- if one letter in 
//             Testword is the same as this letter

std::string get_board(GOptr ptr, const std::string Testword, int& Num_blank);
//return: position of currently guessed letter in Testword
//        ex: $$a$$$a$














bool guess(const std::string& Testword, std::vector<GOptr> root){
	using namespace std;

	int Num_blank = Testword.length();
	int Num_missed = 0;

	GOptr search;
	if (Num_blank <= 5)
		search = root[0];
	else if (Num_blank > 15)
		search = root[11];
	else
		search = root[(Num_blank-5)];
	sort_noMiss(search);
	search -> letter = (search -> noMiss)[0];
	

	while( (Num_missed < 6) && (Num_blank > 0) ){
		search = guess(Testword, search, Num_blank, Num_missed);
	}

	return (Num_blank == 0);
}

GOptr guess(const std::string& Testword, GOptr ptr, int& Num_blank, int& Num_missed){
	using namespace std;

	char letter;
	if (ptr -> letter == '\0'){
		ptr -> letter = get_letter(ptr);
	}
	letter = ptr -> letter;

	if (ptr -> link == NULL){
		GuessOrder_insert(ptr);
	}

	if (!is_contained(Testword, letter)){
		Num_missed++;
		ptr = &(*(ptr -> link))[0];
	} else {
		string board = get_board(ptr, Testword, Num_blank);
		vector<GuessOrder>::iterator iter_g = (*(ptr -> link)).begin();

		while (iter_g != (*(ptr -> link)).end()){
			if (isSame(iter_g -> board, board, letter))
				break;
			else
				iter_g++;
		}

		if ( iter_g == (*(ptr -> link)).end() ){
			ptr = split_dictionary(ptr, board);
		} else {
			ptr = &(*iter_g);
		}
	}

	return ptr;
}

std::string get_board(GOptr ptr, const std::string Testword, int& Num_blank){
	using namespace std;
	
	char letter = ptr -> letter;

	string board(Testword.length(), '$');

	string::iterator iter_b = board.begin();
	string::const_iterator iter_t = Testword.begin();

	for (; iter_t != Testword.end(); iter_t++, iter_b++){
		if (*iter_t == letter){
			*iter_b = letter;
			Num_blank--;
		}
	}

	return board;
}











#endif // GUESSPROC_H