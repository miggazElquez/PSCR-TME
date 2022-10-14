#include "Banque.h"
#include <iostream>

using namespace std;
using namespace pr;

const int NB_THREAD = 10;
const int K = 20;



void work(Banque b, int id) {
	for (int k=0;k<1000;k++) {
		size_t j = rand() % K;
		size_t i = rand() % K;
		int m = rand() % 99 + 1;

		b.transfert(i,j,m);
		std::this_thread::sleep_for(std::chrono::milliseconds(rand()%20));
	}

}


int main () {
	vector<thread> threads;

	::srand(::time(nullptr));


	Banque b(K,100);


	for (int i=0;i<NB_THREAD;++i) {
		threads.emplace_back(work,b,i);
	}
	// TODO : creer des threads qui font ce qui est demandé


	for (auto & t : threads) {
		t.join();
	}

	cout << b.comptabiliser(K*100);

	return 0;
}
