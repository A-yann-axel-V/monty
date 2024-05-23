#include "monty.h"


/**
 * nop - No operation
 * @stack: stack
 * @line_number: line number
 *
 * Return: Always 0
 */
void nop(stack_t **stack, unsigned int line_number)
{
	UNUSED(stack);
	UNUSED(line_number);
}


/**
 * is_number - Checks if a string is a number
 * @str: string to be checked
 *
 * Return: Always 0
 */
int is_number(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	if (str[0] == '-')
		i = 1;

	for (; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]) == 0)
			return (0);
	}

	return (1);
}
