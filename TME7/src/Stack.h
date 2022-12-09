#pragma once

#include <cstring> // size_t,memset
#include <mutex>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <iostream>

namespace pr {
using namespace std;
#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	std::mutex m;
	sem_t *empty;
	sem_t *full;

public :
	Stack () : sz(0) { memset(tab,0,sizeof tab) ;
		empty = sem_open("/pscr_7_2_semempty", O_CREAT , 0600, 	0);
		full = sem_open("/pscr_7_2_semfull", O_CREAT,0600, STACKSIZE);
	}

	T pop () {
		cout << "pop\n";
		sem_wait(empty);
		m.lock();
		T toret = tab[--sz];
				m.unlock();		

		sem_post(full);
		return toret;
	}

	void push(T elt) {
		cout << "push\n";
		sem_wait(full);
		m.lock();
		int res;
		sem_getvalue(empty,&res);
		std::cout << "(" << sz << ", " << res << ")" << std::endl;		
		tab[sz++] = elt;
		m.unlock();
		sem_post(empty);

	}
};

}
