#include "shell.h"





int main()
{
	char line[MAX_INPUT_LINE];
	char *args[MAX_ARGS];
	int i = 0;	


	while(1)
	{
		 printf("shell$ ");
		 if (fgets(line, MAX_INPUT_LINE, stdin) == NULL)
		 {
			 printf("Error reading input");
			 break;
		 }
	}

	line[strcspn(line, "\n")] = '\0';

	args[i] = strtok(line, " \n");
	while (args[i] != NULL && i < MAX_ARGS - 1)
	{
		i++;
		args[i] = strtok(NULL, " \n");
	}

	args[i] = NULL;
	return (0);
}

