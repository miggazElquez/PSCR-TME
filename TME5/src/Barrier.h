#include <cstdlib>
#include <mutex>
#include <condition_variable>


#pragma once

namespace pr {

class Barrier {
	int compteur;
	int N;
	std::mutex m;
	std::condition_variable w;
public:
	Barrier(int n) :compteur(0),N(n) {}
	void done() {
		std::unique_lock<std::mutex> u(m);
		compteur++;
		if (compteur == N) {
			w.notify_all();
		}
	}

	void waitFor() {
		std::unique_lock<std::mutex> u(m);
		while (compteur < N) {
			w.wait(u);
		}
	}

};


}