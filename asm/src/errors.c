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

void lexical_error(char *start, char *line, int j)
{
    ft_printf("Lexical error at [%d:%d]\n", j, line - start + 1);
    exit(0);
}

void syntax_error_separator(char *start, char *line, int j)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\"\n", j, line - start + 1);
    exit(0);
}

void syntax_error_indirect_label(char *start, char *line, int j)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT_LABEL \"", j, line - start + 1);
    while(*line && *line != ' ' && *line != '"')
        ft_putchar(*line++);
    ft_putstr("\"\n");
    exit(0);
}

void syntax_error_instruction(char *start, char *line, int j)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION \"", j, line - start + 1);
    while(*line && *line != ' ' && *line != '"')
        ft_putchar(*line++);
    ft_putstr("\"\n");
    exit(0);
}

void syntax_error_string(char *start, char *line, int j)
{
    ft_printf("Syntax error at token [TOKEN][%03d:%03d] STRING \"", j, line - start + 1);
    while (*line && *line != '"')
        ft_putchar(*line++);
    if (*line == '"')
        ft_putchar('"');
    ft_putstr("\"\n");
    exit(0);
}