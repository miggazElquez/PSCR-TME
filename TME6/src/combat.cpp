#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"


using namespace std;

int HP = 3;
const char * name;

void handler(int signum) {
	HP--;
	if (!HP) {
		cout << name << " is dead\n";
		exit(0);
	}
	cout << name << " hp : " << HP << endl;
}

void handler2(int signum) {
	cout << name << " : " << HP << "remaining\n";
	exit(0);

}

void attaque(pid_t adversaire) {

	struct sigaction s;
	sigemptyset(&s.sa_mask);

	s.sa_handler = handler;
	s.sa_flags = 0;

	sigaction(SIGINT,&s,NULL);

	if (kill(adversaire,SIGINT) == -1) {
		cout << name << " : " << HP << "remaining\n";
		exit(0);
	}

	randsleep();
}

void defense() {
	struct sigaction s;
	s.sa_handler = SIG_IGN;
	s.sa_flags = 0;
	sigemptyset(&s.sa_mask);

	sigaction(SIGINT,&s,NULL);
	randsleep();
}


void combat(pid_t adversaire) {
	srand(getpid());
	randsleep();
	while (HP) {
		attaque(adversaire);
		defense();
	}
}

int sign = 0;

void handler_child(int signum) {
	sign = 1;
}

void handler_alarm(int signum) {
	sign = 0;
}


int wait_till_pid(pid_t pid,int sec) {

	struct sigaction s;
	sigemptyset(&s.sa_mask);

	s.sa_handler = handler_child;
	s.sa_flags = 0;

	sigaction(SIGCHLD,&s,NULL);

	struct sigaction s2;
	sigemptyset(&s2.sa_mask);

	s2.sa_handler = handler_alarm;
	s2.sa_flags = 0;

	sigaction(SIGALRM,&s2,NULL);

	alarm(sec);

	sigset_t st;
	sigfillset(&st);
	sigdelset(&st,SIGCHLD);
	sigdelset(&st,SIGALRM);

	while (true) {
		sigsuspend(&st);
		if (sign) {
			int pid_ = wait(NULL);
			if (pid_ == pid) {
				return pid;
			}
			if (pid_ == -1) {
				return -1;
			}
		} else {
			return 0;
		}
	}

}


int main() {
	/*
	pid_t vador = getpid();
	pid_t luke;

	struct sigaction s; //avant qu'on commence, on ignore les SIGINT
	s.sa_handler = SIG_IGN;
	s.sa_flags = 0;
	sigemptyset(&s.sa_mask);

	sigaction(SIGINT,&s,NULL);

	struct sigaction s2; //avant qu'on commence, on ignore les SIGINT
	s.sa_handler = handler2;
	s.sa_flags = 0;
	sigemptyset(&s.sa_mask);

	sigaction(SIGCHLD,&s,NULL);

	if ((luke = fork()) == 0) {
		name = "Luke";
		combat(vador);
	} else {
		cout << luke << endl;
		name = "Vador";
		combat(luke);
	}
	*/
	pid_t pid1;
	pid_t pid2;
	if ((pid1 = fork()) == 0) {
		sleep(4);
		cout << "pid1 fin" << endl;
		exit(0);
	}
	if ((pid2 = fork()) == 0) {
		cout << "pid2 fin" << endl;
		exit(0);
	}
	cout << "pid1 : " << pid1 << endl;
	cout << "pid2 : " << pid2 << endl;
	cout << "res : " << wait_till_pid(pid1,2) << endl;
	cout << "end\n";
}

//Q6) Le combat n'est pas équitable : comme on fait sigsuspend, 
//on attend une attaque pour continuer à avancer quand on est en défense, donc après on attaque sur un vador forcément vulnérable

