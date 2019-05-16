#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

int *func1(void *temp) {
	int noSignal = 50;
	sigset_t signal;
	siginfo_t signalInfo;
	
	sigfillset(&signal); //1111 ... 1111
	sigdelset(&signal, noSignal); //1111 ... 1011
	pthread_sigmask(SIG_BLOCK, &signal, NULL); //blokuje wszystkie sygnały z jedynką
	
	sigemptyset(&signal);
	sigaddset(&signal, noSignal);
	sigwaitinfo(&signal, &signalInfo);
	
	printf("Received the signal!\n");
	printf("Number of signal: %d\n", signalInfo.si_signo);
	printf("Value of signal: %d\n", signalInfo.si_value.sival_int);
	return EXIT_SUCCESS;
}

int *func2(void *temp) {
	int noSignal = 52;
	sigset_t signal;
	siginfo_t signalInfo;
	
	sigfillset(&signal); //1111 ... 1111
	sigdelset(&signal, noSignal); //1111 ... 1011
	pthread_sigmask(SIG_BLOCK, &signal, NULL); //blokuje wszystkie sygnały z jedynką
	
	sigemptyset(&signal);
	sigaddset(&signal, noSignal);
	sigwaitinfo(&signal, &signalInfo);
	
	printf("Received the signal!\n");
	printf("Number of signal: %d\n", signalInfo.si_signo);
	printf("Value of signal: %d\n", signalInfo.si_value.sival_int);
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	pthread_t thread1, thread2;
	sigset_t set;
	
	sigfillset(&set); //1111 ... 1111
	pthread_sigmask(SIG_BLOCK, &set, NULL); //ustawia maskę blokowanych sygnałów; zgodnie z powyższym - blokuje wszystkie sygnały przychodzące dla tego wątku
	
	pthread_create(&thread1, NULL, &func1, NULL);
	pthread_create(&thread2, NULL, &func2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return EXIT_SUCCESS;
}