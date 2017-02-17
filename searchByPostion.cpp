#include "utility.h"
#include "manageDict.h"
#include "guessProc.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>




int main(int argc, char const *argv[])
{	
	using namespace std;

	// if (argc != 3){
	// 	cerr << "Usage: " << argv[0] << " DictionaryFile TestFile\n";
	// 	exit(1);
	// }
	// clock_t start_t(clock()), end_t;

	// read the dictionary and the test file
	ifstream ifs_dict(argv[1]);
	//ifstream ifs_test(argv[2]); 

	// if (ifs_dict.fail()){
	// 	cerr << "Error: can't read the dictioary: " << argv[1] << endl;
	// 	exit(2);
	// }

	// if (ifs_test.fail()){
	// 	cerr << "Error: can't read the test file: " << argv[2] << endl;
	// 	exit(3);
	// }


	vector<GOptr> Index_root = SplitByLength(ifs_dict);

	string word = "abandon";

	guess(word, Index_root);

	// int Num_CorrGues = 0;
	// int Num_Words = 0;

	// // Go through the test file to check our decision tree
	// string word;
	// while (getline(ifs_test, word)){
	// 	if (guess(word, Index_root))
	// 		Num_CorrGues++;
	// 	Num_Words++;
	// }

	

	// end_t = clock();
	// double diff = static_cast<double>(end_t-start_t);
	// double seconds = diff / CLOCKS_PER_SEC;

	// // print output on screen
	// cout << "Number of words tested: " << Num_Words << endl
	// 	 << "Number of words guessed correctly: " << Num_CorrGues << endl
	// 	 << "Correct Guesses (" << '%' << "): " 
	// 	 << static_cast<double>(Num_CorrGues) / static_cast<double>(Num_Words) * 100
	// 	 << '%' << endl
	// 	 << "Time to run: " << seconds << " seconds" << endl;

	return 0;
}





























