#include "main.h"


int
main(__attribute__((unused)) int ac, char **argv, char **env)
{
	char *param = NULL;
	ssize_t nread = 0;
	size_t len = 0;
	int tty = isatty(STDIN_FILENO), i;

	while (1)
	{
		if (tty)
			printf("#cisfun$ ");

		nread = getline(&param, &len, stdin);

		if (nread == EOF)
			goto end;

		param[strcspn(param, "\n")] = '\0';

		/* if line's index neither is null terminate nor character, continue*/
		for (i = 0; param[i] != '\0' && param[i] == ' '; i++);

		if (param[i] == '\0')
			continue;

		if (strcmp(param, "exit") == 0)
			break;
		else
			runcommandline(param);
	}

end:
	free(param);
	return (0);
}
