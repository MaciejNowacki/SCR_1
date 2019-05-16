#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {
	int pid = atoi(argv[1]);
	int sigNum = atoi(argv[2]);
	union sigval val;
	val.sival_int = atoi(argv[3]);
	
	if(sigqueue(pid, sigNum, val) == -1) {
		perror("Oops: sigqueue error");
		return EXIT_FAILURE;
	} else {
		printf("The signal was successfully sent.\n%d:%d:%d\n", pid, sigNum, val.sival_int);
	}
	
	
	return EXIT_SUCCESS;
}