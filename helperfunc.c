#include "main.h"

void
runcommandline(char *param)
{
	int i, status;
	char *vector[BUFSIZ], newpath[BUFSIZ];

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

		/* if vector[0] has any '/', that mean this is path */
		if (vector[0] && !strchr(vector[0], '/')
				&& findpath(vector[0], newpath) == 0)
			vector[0] = newpath;

		execve(vector[0], vector, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);
}


int
findpath(char *argument0, char *newpath)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		snprintf(newpath, BUFSIZ, "%s/%s", token, argument0);
		if (access(newpath, X_OK) == 0)
			return (0);
		token = strtok(NULL, ":");
	}
	return (1);
}

