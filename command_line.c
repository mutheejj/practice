#include "shell.h"

int main()
{
	char line[MAX_INPUT_LINE];
	char *args[MAX_ARGS];

	while(1)
	{
		int i = 0;
		pid_t pid = fork();
		pid_t ppid;
		int sitrep;
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
				if (feof(stdin))
				{
					big_print("Exiting the shell\n");
					exit(0);
				}
				else
				{
					while ((ppid = waitpid(pid, &sitrep, 0)) > 0);
					if (ppid == -1)
					{
						perror("Child process traffic\n");
						exit(1);
					}
					big_print("success\n");
				}
			}

		 line[strcspn(line, "\n")] = '\0';
		 memset(args, 0, sizeof(args));
		 args[i] = strtok(line, " \n");
		 

		 while (args[i] != NULL && i < MAX_ARGS - 1)
		 {
			 i++;
			 args[i] = strtok(NULL, " \n");
		 }

		 args[i] = NULL;

		 if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		 {
			 big_print("Exiting the shell.\n");
			 break;
		 }

		 execvp(args[0], args);
		 fprintf(stderr, "Error executing command: %s\n", args[0]);
		 exit(1);
		 }
		 else
		 {
			waitpid(pid, NULL, 0);
			big_print("success\n");
		 }
	}
	return (0);
}
