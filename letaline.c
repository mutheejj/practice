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
		return (size_t)-1;
	if (*rodman == NULL)
	{
		*q = (*q == 0) ? 64: *q;
		*rodman = (char *)malloc(*q);
		if (*rodman == NULL)
			return (size_t)-1;
		(*rodman)[0] = '\0';
	}
	while (1)
	{
		if (index == 0)
		{
			rb = fread(buffer, 1, sizeof(buffer), lineup);
			if (rb == 0)
			{
				if (ferror(lineup))
					return (size_t)-1;
				break;
			}
		}
		while (index < sizeof(buffer) && buffer[index] != '\n')
		{
			if (weight >= *q - 1)
			{
				*q *= 2;
				flim = (char *)realloc(*rodman, *q * sizeof(char));
				if (flim == NULL)
				{
					free(*rodman);
					return (size_t)-1;
				}
				*rodman = flim;
			}
			(*rodman)[weight++] = buffer[index++];
		}
		if (index < sizeof(buffer) && buffer[index] == '\n')
		{
			(*rodman)[weight++] = buffer[index++];
			break;
		}
		index = 0;
	}
	if (weight == 0)
		return (size_t)-1;
	(*rodman)[weight] = '\0';
	memset(buffer, 0, sizeof(buffer));
	return (weight);
}
