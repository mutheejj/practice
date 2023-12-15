#include "shell.h"


void free_args(char **args, int argc);

int main(void)
{
	char line[MAX_INPUT_LINE];
	char *args[1024];
	int argc = 0;
	char *token, *tokenChecker;
	int i;

	while (1)
	{
		pid_t pid;
		int sitrep;

		big_print("$ ");
		fflush(stdout);

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
		if (strcmp(line, "\n") == 0)
			continue;

		line[strcspn(line, "\n")] = '\0';
		
		if (strcmp(line, "exit") == 0)
			break;
		
		argc = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			tokenChecker = strdup(token);

			if (strlen(tokenChecker) == 0)
			{
				free(tokenChecker);
				continue;
			}

			args[argc++] = tokenChecker;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;
		if (!args[0])
			continue;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			free_args(args, argc);
			exit(1);
		}
		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Error executing comms");
				free_args(args, argc);
				exit(0);
			}
		}
		else
		{
			waitpid(pid, &sitrep, WUNTRACED);
		}
		for (i = 0; i <= argc; i++)
		{
			free(args[i]);
		}
	}
	free_args(args, argc);
	return (0);
}

void free_args(char **args, int argc)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		free(args[i]);
	}
}
