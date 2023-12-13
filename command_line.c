#include "shell.h"



int main(void)
{
	char line[MAX_INPUT_LINE];
	char *args[MAX_ARGS];
	int argc = 0;
	char *token;

	while (1)
	{
		pid_t pid;
		int sitrep;

		big_print("%s", "Cisfun$  ");
		fflush(stdout);
		memset(line, 0, sizeof(line));

		if (fgets(line, MAX_INPUT_LINE, stdin) == NULL)
		{
			if (feof(stdin))
			{
				big_print("\nExiting shell\n");
				exit(0);
			}
			else
			{
				perror("Error reading input\n");
				break;
			}
		}
		line[strcspn(line, "\n")] = '\0';
		
		if (strcmp(line, "exit") == 0)
		{
			big_print("Exxxit\n");
			exit(0);
		}
		argc = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			args[argc++] = token;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(0);
		}
		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Error executing comms");
				exit(0);
			}
		}
		else
		{
			waitpid(pid, &sitrep, WUNTRACED);
		}
	}
	return (0);
}
