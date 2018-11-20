/*David Schmeling
  Simple Shell Program
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFERSIZE 81
#define MAXARGS 20

extern char ** environ;

int main (int argc, char *argv[])
{
    int nargs;
    char buffer[BUFFERSIZE];
    char whitespace[] = " \t\n\r";
    char * arglist[MAXARGS];
    void exit(int status);
    char *s = *environ;
    char *getenv(const char *name);

    void run_child(char *args[]) {
	int err = execvp(args[0], args);
	perror(args[0]);
	exit(0);
    }

    printf("Welcome to the Shell!\n\n~ ");
    while(fgets(buffer, BUFFERSIZE, stdin) != NULL)
    {
        nargs = 0;
        arglist[nargs] = strtok(buffer, whitespace);
	int ecomp = strcmp(arglist[0], "exit");
	int pcomp = strcmp(arglist[0], "path");
	int envcomp = strcmp(arglist[0], "environment");
	int i = 1;
	    if (ecomp == 0) {exit(0);}
 	    if (pcomp == 0) {
		printf("PATH : %s\n", getenv("PATH"));
	    }	   
	    if (envcomp == 0) {
	        for(i; s; i++) {
		    printf("%s\n", s);
		    s = *(environ+i);
		} 
            }

        while(arglist[nargs] != NULL) {
	    arglist[++nargs] = strtok(NULL, whitespace);
	}    
	    int pid;
	    int status;
	    if ((pid = fork()) == 0) {
		printf("\n");
		printf("%s\n\n", "Child Process Running...");		
		run_child(arglist);
            }
	    else {
		waitpid(pid, &status, 0);
		printf("\n");
		printf("%s\n\n", "Child Process Complete!");
		printf("%s", "~ ");
	    }
    }
    return 0;
}
