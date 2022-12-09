#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {

	int fd;
	if ((fd = shm_open("/monshm", O_RDWR | O_CREAT,0600)) == -1) {
		perror("Error");
		exit(1);
	}

	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	void *ptr;
	if ((ptr =  mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	memset(ptr, 0, sizeof(Stack<char>));

	Stack<char> *s = new (ptr) Stack<char>();




	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}

