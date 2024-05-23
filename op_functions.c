#include "monty.h"


/**
 * push - Pushes an element to the stack
 * @stack: stack
 * @line_number: line number
 *
 * Return: Always 0
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	char *n = strtok(NULL, " \n");

	if (n == NULL || !is_number(n))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(n);
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pop - Pops the top element of the stack
 * @stack: stack
 * @line_number: line number
 *
 * Return: Always 0
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	*stack = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = NULL;
	free(tmp);
}

/**
 * swap - Swaps the top two elements of the stack
 * @stack: stack
 * @line_number: line number
 *
 * Return: Always 0
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;
	int n;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	n = tmp->n;
	tmp->n = tmp->next->n;
	tmp->next->n = n;
}

/**
 * add - Adds the top two elements of the stack
 * @stack: stack
 * @line_number: line number
 *
 * Return: Always 0
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	tmp->next->n += tmp->n;
	pop(stack, line_number);
}
