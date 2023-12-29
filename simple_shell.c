#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void
run_non_interactive(char **env)
{
	char **cpargv = NULL;
	ssize_t nread;
	size_t len;
	int status;

	cpargv = calloc(2, sizeof(char *));

	while ((nread = getline(&cpargv[0], &len, stdin)) != -1)
	{
		(cpargv[0])[nread - 1] = '\0';

		if (fork() > 0)
			wait(&status);
		else
		{
			execve(strtok(cpargv[0], " \n\t\a"), cpargv, env);
			dprintf(STDERR_FILENO
				, "%s: No such file or directory\n", cpargv[0]);
			free(cpargv[0]);
			free(cpargv);
			exit(EXIT_FAILURE);
		}
	}

	free(cpargv[0]);
	free(cpargv);
	exit(EXIT_SUCCESS);
}

int
main(__attribute__((unused)) int ac, char **argv, char **env)
{
	char **param = NULL;
	ssize_t nread;
	size_t len;
	int status;

	if (!isatty(STDIN_FILENO))
		run_non_interactive(env);

	param = calloc(2, sizeof(char *));

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		nread = getline(&param[0], &len, stdin);
		if (nread == -1)
			break;

		(param[0])[nread - 1] = '\0';

		if (fork() > 0)
			wait(&status);
		else
		{
			execve(strtok(param[0], " \n\t\a"), param, env);
			dprintf(STDERR_FILENO
				, "%s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	free(param[0]);
	free(param);
	exit(EXIT_SUCCESS);
}
