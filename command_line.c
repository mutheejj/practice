#include "shell.h"
void big_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

int main()
{
	char line[MAX_INPUT_LINE];
	char *args[MAX_ARGS];
	int i = 0;
	pid_t pid = fork();


	while(1)
	{
		 printf("cisfun$ ");

		 if (fgets(line, MAX_INPUT_LINE, stdin) == NULL)
		 {
			 perror("Error when reading input\n");
			 break;
		 }

		 line[strcspn(line, "\n")] = '\0';
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

		 if (pid == 0)
		 {
			execvp(args[0], args);
			fprintf(stderr, "Error executing command: %s\n", args[0]);
			exit(1);
		 }
		 else
		 {
			 wait(NULL);
			 big_print("success\n");
		 }
	}

	return (0);
}
