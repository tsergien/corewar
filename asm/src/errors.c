/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:01:46 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/02 13:01:48 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void lexical_error(char *start, char *line, int line_number)
{
    ft_printf("Lexical error at [%d:%d]\n", line_number, line - start + 1);
    exit(0);
}

void syntax_error_separator(char *start, char *line, int line_number)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\"\n", line_number, line - start + 1);
    exit(0);
}

void syntax_error_indirect_label(char *start, char *line, int line_number)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT_LABEL \"", line_number, line - start + 1);
    while(*line && *line != ' ' && *line != '"')
        ft_putchar(*line++);
    ft_putstr("\"\n");
    exit(0);
}

void syntax_error_instruction(char *start, char *line, int line_number)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION \"", line_number, line - start + 1);
    while(*line && *line != ' ' && *line != '"')
        ft_putchar(*line++);
    ft_putstr("\"\n");
    exit(0);
}

void syntax_error_string(char *start, char *line, int line_number)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] STRING \"", line_number, line - start + 1);
    while (*line && *line != '"')
        ft_putchar(*line++);
    if (*line == '"')
        ft_putchar('"');
    ft_putstr("\"\n");
    exit(0);
}

void syntax_error_double_command(int size, char *start, char *line, int line_number)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] COMMAND_%s\n", line_number, line - start + 1, size == PROG_NAME_LENGTH ? "NAME \".name\"" : "COMMENT \".comment\"" );
    exit(0);
}