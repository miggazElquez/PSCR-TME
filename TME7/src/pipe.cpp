#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc,char ** argv) {
	char** arg1 = &argv[1];
	char** arg2;
	for (int i=1;i<argc;i++) {
		//cout << argv[i] << endl;
		if (strcmp(argv[i],"|") == 0) {
			//cout << "debug : " << i << " " << argv[i] << endl;
			arg2 = &argv[i+1];
			argv[i] = NULL;
		}
	}

	/*for (char**c=arg1;*c;c++) {
		cout << *c << " ";
	}
	cout << endl;

	for (char**c=arg2;*c;c++) {
		cout << *c << " ";
	}
	cout << endl;*/



	int tubeDesc[2];

	if (pipe (tubeDesc) == -1) {
		perror ("pipe"); exit (1);
	}
	int pid_1;
	if (pid_1 = fork() == 0) {
		dup2(tubeDesc[0],0);
		close(tubeDesc[1]);
		execv(arg2[0],arg2);
		perror("exec1 didn't work");exit(1);
	}
	if (fork() == 0) {
		dup2(tubeDesc[1],1);
		close(tubeDesc[0]);
		execv(arg1[0],arg1);
		perror("exec2 didn't work");exit(1);	
	}

	close(tubeDesc[0]);
	close(tubeDesc[1]);

	int pid = wait(NULL);
	wait(NULL);
}
