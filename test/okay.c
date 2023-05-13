#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	printf("This is the number of arguments in this program: %d\n", argc);
	printf("These are the arguments in the program:- %s\n", *argv);

	if (argc > 1)
	{
		printf("\nBelow is a detailed breakdown:\n");

		for (i = 0; i < argc; i++)
		{
			 printf("argv[%d]: %s\n", i, argv[i]);
		}
	}
	else
	{
		printf("\nThis program has only one argument.\n");
	}
	return (0);
}
