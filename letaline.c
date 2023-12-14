#include "shell.h"

/**
 */
ssize_t letaline(char **rodman, size_t *q, FILE *lineup)
{
	size_t weight = 0;
	static char buffer[1024];
	static size_t index = 0;
	char *flim;
	size_t rb;

	if(!rodman || !q)
		return (-1);
	if (*rodman == NULL)
	{
		*rodman = (char *)malloc(*q);
		if(*rodman == NULL)
			return (-1);
	}
	while (1)
	{
		if (index == 0)
		{
			rb = fread(buffer, 1, sizeof(buffer), lineup);
			if (rb == 0)
				break;
		}
		while (index < sizeof(buffer) && buffer[index] != '\n')
		{
			if (weight >= *q - 1)
			{
				*q *= 2;
				flim = (char *)realloc(*rodman, *q);
				if (flim == NULL)
					return (-1);
				*rodman = flim;
			}
			(*rodman)[weight++] = buffer[index++];
		}
		if (index < sizeof(buffer) && buffer[index] == '\n')
		{
			(*rodman)[weight++] = buffer[index++];
			break;
		}
		memset(buffer, 0, sizeof(buffer));
		index = 0;
	}
	if (weight == 0)
		return (-1);
	(*rodman)[weight] = '\0';
	free(*rodman);
	return (weight);
}
