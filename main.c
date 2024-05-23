#include "monty.h"
#include <unistd.h>


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
    UNUSED(argc);

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

/**
 * execute_monty - Entry point
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
