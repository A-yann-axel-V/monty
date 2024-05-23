#include "monty.h"


/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 *
 * Return: Always 0
 */
int main(int argc, char *argv[], char *envp[])
{
	UNUSED(envp);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], R_OK) == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	execute_monty(argv[1]);

	return (0);
}
