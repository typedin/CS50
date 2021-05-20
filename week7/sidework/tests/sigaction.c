
// feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED


#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

/**
 *
struct sigaction {
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
};
 *
 */

// flag indicating whether control-c has been heard
bool signaled = false;

/**
 * Handles signals.
 */
void handler(int signal)
{
    // control-c
    if (signal == SIGINT)
    {
        signaled = true;
		printf("SIGINT : %d \n", SIGINT);
    }
}


int main()
{

	// listen for SIGINT (aka control-c)
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

	int nb_duck = 0;
	while(1)
	{
		printf("%d canards, moi j'aime bien les canards...\n", nb_duck);

//		handler(nb_duck);
		if(signaled)
			break;
		else
			nb_duck++;
	}

	printf("so many ducks: %d", nb_duck);
	return 0;
}
 
