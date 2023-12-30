#include "main.h"

void
runcommandline(char *param)
{
	int i, status;
	char *vector[BUFSIZ], path[BUFSIZ];

	if (!fork())
	{
		i = 0;
		vector[i] = strtok(param, " ");

		while (vector[i] != NULL)
		{
			i++;
			vector[i] = strtok(NULL, " ");
		}

		vector[i] = NULL;

		execve(vector[0], vector, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);
}

