#include "shell.h"



int main()
{
	char line[MAX_INPUT_LINE];
	char *args[MAX_ARGS];

	while(1)
	{
		pid_t pid, ppid;
		int sitrep;

		pid = fork();

		if (pid == -1)
		{
			perror("Forkn't\n");
			exit(1);
		}

		if (pid == 0)
		{
			big_print("cisfun$ ");
			fflush(stdout);
			
			if (fgets(line, MAX_INPUT_LINE, stdin) == NULL)
			{
				perror("Error when reading input\n");
				exit(1);
			}
			
			line[strcspn(line, "\n")] = '\0';
			
			if (strcmp(line, "exit") == 0)
			{
				big_print("Exiting the shell\n");
				exit(0);
			}

			
			args[0] = line;
			args[1] = NULL;
			
			execvp(args[0], args);

			if (execvp(args[0], args) == -1)
			{
				perror("Error executing command");
				exit(1);
			}
		}
		else
		{
			while ((ppid = waitpid(pid, &sitrep, 0)) > 0);
			if (ppid == -1)
			{
				perror("Child process traffic\n");
				exit(1);
			}
			big_print("cisfun$ ");
			fflush(stdout);
			
			if (strcmp(line, "exit") == 0)
			{
				big_print("Exiting the shell\n");
				exit(0);
			}
		}
	}
	return (0);
}
	
