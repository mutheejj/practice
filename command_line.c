#include "shell.h"



int main(void)
{
	char line[MAX_INPUT_LINE];
	char **args = NULL;
	int argc = 0;
	char *token;
	int i;

	if (!args)
		exit(0);
	while (1)
	{
		pid_t pid;
		int sitrep;

		big_print("Cisfun$  ");
		fflush(stdout);
		memset(line, 0, sizeof(line));

		if (fgets(line, MAX_INPUT_LINE, stdin) == NULL)
		{
			if (feof(stdin))
			{
				big_print("\nExiting shell\n");
				break;
			}
			else
			{
				perror("Error reading input\n");
				break;
			}
		}
		line[strcspn(line, "\n")] = '\0';
		
		if (strcmp(line, "exit") == 0)
			break;
		
		argc = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			args = realloc(args, (argc + 1) * sizeof(char *));
			if (args == NULL)
			{
				perror("error reallocating mem");
				exit(EXIT_FAILURE);
			}
			args[argc++] = strdup(token);
			token = strtok(NULL, " ");
		}
		args = realloc(args, (argc + 1) * sizeof(char *));
		if (args == NULL)
		{
			perror("error reallocating mem");
			exit(EXIT_FAILURE);
		}
		args[argc] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(1);
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
		for (i = 0; i < argc; i++)
		{
			free(args[i]);
		}
	}
	free(args);
	return (0);
}
