

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>

// data struct used to order letters by frequency
struct Letter_Freq
{
	char letter;
	int freq;
};


// tree to store game strategy
struct GuessOrder
{
	char letter;  // letter used to guess
	std::string noMiss;  // letters not used before this guess
	std::string board;    // state of board associated to this guess
	std::list<std::string> dictionary; 
	// remaining words filtered by previous guesses
	std::vector<GuessOrder> *link;
	// pointer to a vector of subsequent guess strategies
};
typedef GuessOrder* GOptr;

bool guess(const std::string& Testword, std::vector<GOptr> root);
//return: if the Testword is guessed correctly

GOptr guess(const std::string& Testword, GOptr, int& Num_blank, int& Num_missed);
//return: pointer to next guess
//side_effect: select one letter from not uesed letters, Num_missed++ if
//             this letter is not contained, Num_blank-- if one letter in 
//             Testword is the same as this letter

std::string get_board(GOptr ptr, const std::string Testword, int& Num_blank);
//return: position of currently guessed letter in Testwor




char get_letter(GOptr ptr);
//return: the most frequent letter in the associated dictionary

void sort_noMiss(GOptr);
//return: ordered letter not used by frequency

void GuessOrder_insert(GOptr ptr);
//side_effect: insert a vector of GuessOrder
//side_effect: initial the first GuessOrder of this vector as
//             a list of words which do not contain ptr -> letter

std::string removeChar(GOptr ptr);
//return: delete the last guessed letter from the list of unuesd letters

GOptr split_dictionary(GOptr ptr, std::string board);
//return: pointer to next guess
//side_effect: send words which have same form as board to a subsequent dictionary

std::vector<GOptr> SplitByLength(std::ifstream& ifs);
//return: a vector of pointers to GuessOrders splitted by word length

std::vector< std::list<std::string> > get_dictionary(std::ifstream& ifs);
//return: a vector of dictionaries by splitting the origin dicitionary 
//        based on word length



int get_freq(const std::list<std::string>& dict, char letter);
//return: frequency of letter in dict

bool is_contained(const std::string& word, char letter);
//return: if letter is contained in word

bool isSame(const std::string &word, const std::string &board, char letter);
//return: if word has the same form as board

bool compare(const Letter_Freq& x, const Letter_Freq& y);
//return: if letter x is more frequent than y


int main(int argc, char const *argv[])
{	
	using namespace std;

	if (argc != 3){
		cerr << "Usage: " << argv[0] << " DictionaryFile TestFile\n";
		exit(1);
	}
	clock_t start_t(clock()), end_t;

	// read the dictionary and the test file
	ifstream ifs_dict(argv[1]);
	ifstream ifs_test(argv[2]); 

	if (ifs_dict.fail()){
		cerr << "Error: can't read the dictioary: " << argv[1] << endl;
		exit(2);
	}

	if (ifs_test.fail()){
		cerr << "Error: can't read the test file: " << argv[2] << endl;
		exit(3);
	}


	vector<GOptr> Index_root = SplitByLength(ifs_dict);

	int Num_CorrGues = 0;
	int Num_Words = 0;

	// Go through the test file to check our decision tree
	string word;
	while (getline(ifs_test, word)){
		if (!guess(word, Index_root))
			cout << word << endl;
		// 	Num_CorrGues++;
		// Num_Words++;
	}

	

	end_t = clock();
	double diff = static_cast<double>(end_t-start_t);
	double seconds = diff / CLOCKS_PER_SEC;

	// print output on screen
	cout << "Number of words tested: " << Num_Words << endl
		 << "Number of words guessed correctly: " << Num_CorrGues << endl
		 << "Correct Guesses (" << '%' << "): " 
		 << static_cast<double>(Num_CorrGues) / static_cast<double>(Num_Words) * 100
		 << '%' << endl
		 << "Time to run: " << seconds << " seconds" << endl;

	return 0;
}



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



























