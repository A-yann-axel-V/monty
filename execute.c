#include "monty.h"


/**
 * execute_monty - Execute monty file
 * @file: file to be executed
 *
 * Return: Always 0
 */
void execute_monty(char *file)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    char *opcode = NULL;
    void (*f)(stack_t **stack, unsigned int line_number);

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", file);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        line_number++;
        opcode = strtok(line, " \n");
        if (opcode == NULL || *opcode == '#')
            continue;
        f = get_op_func(opcode);
        if (f == NULL)
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            free_stack(stack);
            free(line);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        f(&stack, line_number);
    }

    free_stack(stack);
    free(line);
    fclose(fp);
}

/**
 * get_op_func - Get opcode function
 * @opcode: a string representing the opcode
 * to be searched for.
 *
 * Return: Always 0
 */
void (*get_op_func(char *opcode))(stack_t **, unsigned int)
{
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop},
        {NULL, NULL}
    };
    int i = 0;

    while (instructions[i].opcode != NULL)
    {
        if (strcmp(instructions[i].opcode, opcode) == 0)
            return (instructions[i].f);
        i++;
    }

    return (NULL);
}