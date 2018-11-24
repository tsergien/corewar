/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 12:30:22 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 12:30:23 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	check_lable(t_asm *ass, char *line)
{
	char	*temp;

	if (!*line || *line == COMMENT_CHAR || *line == ';')
		return ;
	temp = line;
	while (consist(LABEL_CHARS, *line))
		line++;
	if (*line == LABEL_CHAR)
	{
		*line++ = 0;
		push_lable(ass, temp);
	}
	else
		check_command(ass, get_cmd_list(ass), temp);
}

void	check_last_line(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return ;
		i++;
	}
	i = 0;
	while (buf[i])
	{
		if (buf[i] == COMMENT_CHAR || buf[i] == ';')
			break ;
		else if (buf[i] != '\t' && buf[i] != ' ')
		{
			ft_printf("Syntax error - unexpected end of input "
			"(Perhaps you forgot to end with a newline ?");
			exit(0);
		}
		i++;
	}
}

void	check_command(t_asm *ass, t_command *c_temp, char *line)
{
	char	*temp;
	int		i;

	if (!*line || *line == COMMENT_CHAR || *line == ';')
		return ;
	while (*line == ' ' || *line == '\t')
		line++;
	temp = line;
	i = 0;
	while (i < 16)
	{
		if (ft_strnequ(line, g_op_tab[i].name, ft_strlen(g_op_tab[i].name)))
		{
			push_command(ass, c_temp, i, line + ft_strlen(g_op_tab[i].name));
			return ;
		}
		i++;
	}
	lexical_error(ass->begin_line, line, ass->line_number);
}

void	check_end_arg_line(t_arg_error *err, t_command *c_temp,
	int i, t_asm *ass)
{
	if (c_temp->args[i].str_value == NULL)
		*err->args += len_int(c_temp->args[i].num_value);
	else
		*err->args += ft_strlen(c_temp->args[i].str_value);
	while (**err->args)
	{
		if (**err->args != ' ' && **err->args != '\t')
			syntax_error(ass->begin_line, get_error_line_address(err),
				ass->line_number, "INSTRUCTION");
		(*err->args)++;
	}
}

void	check_begin_arg_line(t_arg_error *err, t_command *c_temp, int i,
		t_asm *ass)
{
	c_temp->args[i].str_value = NULL;
	c_temp->args[i].size_of_arg = 0;
	while (**err->args == ' ' || **err->args == '\t')
		(*err->args)++;
	if (**err->args != DIRECT_CHAR && **err->args != '-'
	&& !ft_isdigit(**err->args)
	&& **err->args != 'r' && **err->args != LABEL_CHAR)
		syntax_error(ass->begin_line, get_error_line_address(err),
			ass->line_number, "INSTRUCTION");
}
