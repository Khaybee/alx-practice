#include "shell.h"

void prompt(char **av, char **env)
{
	char *prompt = "(my shell) $ ";
	char *buff = NULL;
	size_t buf_len = 0;
	int loop = 1, status;
	ssize_t cont = 0;
	pid_t ch_pid;
	char *argv[] = {NULL, NULL};


	while (loop)
	{
		/* Display a prompt */
		write(STDOUT_FILENO, prompt, 14);

		/* Read user input */
		cont = getline(&buff, &buf_len, stdin);

		/* Handle End of file condition or CTRL D */
		if (cont == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}

		/* Handle newline */
		if (cont > 0 && buff[cont - 1] == '\n')
			buff[cont - 1] = '\0';

		argv[0] = buff;

		ch_pid = fork();
		if (ch_pid == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (ch_pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
			wait(&status);
	}
}
