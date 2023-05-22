#include "shell.h"

int main(int argc, char **argv, char **envp)
{
	char *prompt = "(my shell) $ ";
	char *buff = NULL;
	size_t buf_len = 0;
	int loop = 1, status;
	ssize_t cont = 0;
	pid_t ch_pid;
	char *args[] = {NULL, NULL};

	if (argc == 1)
	{
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

			args[0] = buff;
			(void)argc;

			ch_pid = fork();
			if (ch_pid == -1)
			{
				free(buff);
				exit(EXIT_FAILURE);
			}
			if (ch_pid == 0)
			{
				if (execve(args[0], args, envp) == -1)
					printf("%s: No such file or directory\n", argv[0]);
			}
			else
				wait(&status);
		}
	}
	return (0);
}
