#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIM " \n\t\a"
#define HYPEN "-"

char
**arglist(char *list, char *delim)
{
	char *str = NULL, **vector;
	size_t i = 0;

	str = strtok(list, delim);
	if (!str)
		return (NULL);

	vector = malloc(BUFSIZ * sizeof(char *));

	if (!vector)
	{
		perror("alloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (str && i != BUFSIZ - 1)
	{
		vector[i++] = strdup(str);
		str = strtok(NULL, delim);
	}

	vector[i] = NULL;
	return (vector);
}

int
main(__attribute__((unused)) int ac, char **argv, char **env)
{
	char *param, **argvector;
	ssize_t nread = 0;
	size_t len = 0;
	int status = 0, tty = isatty(STDIN_FILENO), i = 0;

	while (1)
	{
		if (tty)
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		nread = getline(&param, &len, stdin);

		if (nread == EOF)
			break;

		param[nread - 1] = '\0';

		argvector = arglist(param, DELIM);

		if (!argvector)
			continue;

		if (fork() > 0)
		{
			wait(&status);

			i = 0;
			while (1)
				if (argvector[i])
					free(argvector[i++]);
				else
					break;
			free(argvector);
		}
		else
		{
			execve(argvector[0], argvector, env);
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		if (!tty)
			break;
	}

	i = 0;
	while (1)
		if (argvector[i])
			free(argvector[i++]);
		else
			break;
	free(argvector);

	return (0);
}
