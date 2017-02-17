#ifndef GUESSPROC_H
#define GUESSPROC_H


#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


#include "manageDict.h"

using namespace std;






bool guess(const string& Testword, vector<GOptr> root);
//return: if the Testword is guessed correctly

GOptr guess(const string& Testword, GOptr ptr, int& Num_blank, int& Num_missed);
//return: pointer to next guess
//side_effect: select one letter from not uesed letters, Num_missed++ if
//             this letter is not contained, Num_blank-- if one letter in 
//             Testword is the same as this letter

string get_board(GOptr ptr, const string Testword, int& Num_blank);
//return: position of currently guessed letter in Testword
//        ex: $$a$$$a$


#endif //GUESSPROC_H