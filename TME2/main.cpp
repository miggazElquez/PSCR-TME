#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

#include "HashTable.hh"
using namespace tme;
int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	HashTable<string,int> ht(30000);

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"

		int *val = ht.get(word);

		if (val) {
			ht.put(word,*val + 1);
		} else {
			ht.put(word,1);
			nombre_lu++;
		}



		// if (nombre_lu % 100 == 0)
		// 	// on affiche un mot "propre" sur 100
		// 	cout << nombre_lu << ": "<< word << endl;
		// nombre_lu++;
	}


	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

    for (string word: {"war","peace","toto"}) {

    	int *val = ht.get(word);

		if (val) {
			cout << word << " : " << *val << endl;
		} else {
			cout << word << " : 0" << endl;			
		}
    }

    
    



    return 0;
}


