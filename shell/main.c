#include "main.h"

int main(int ac, char **argv)
{
	char *prompt = "(My Shell) $ ";
	char *lineptr = NULL;
	size_t n = 0;
	int hello = 1;
	ssize_t nchars_read = 0;
	char *lineptr_copy = NULL;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	/* declaring void variables */

	(void)ac;

	/* Create a loop for the shell's prompt */
	while (hello)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);

		if (nchars_read == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lineptr_copy, lineptr);

		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(lineptr_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;


		printf("%s\n", lineptr);
	}

	free(lineptr);
	free(argv);
	free(lineptr_copy);
	free(argv[i]);

	return (0);
}
