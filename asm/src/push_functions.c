/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 12:28:32 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 12:28:32 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	push_treg(t_arg_error *err, t_command *c_temp, t_asm *ass)
{
	if (**err->args == 'r')
	{
		(*err->args)++;
		err->count++;
		if (ft_isdigit(**err->args))
		{
			c_temp->args[err->i].num_value = ft_atoi(*err->args);
			if (c_temp->args[err->i].num_value < 1 ||
				c_temp->args[err->i].num_value > 16)
				syntax_error(ass->begin_line, get_error_line_address(err),
				ass->line_number, "INSTRUCTION");
			c_temp->args[err->i].size_of_arg = 1;
			c_temp->args[err->i].type_of_arg = T_REG;
			count_codage(err->i, T_REG, c_temp);
		}
		else
			syntax_error(ass->begin_line, get_error_line_address(err),
			ass->line_number, "INSTRUCTION");
	}
}

void	push_tdir(t_arg_error *err, t_command *c_temp, t_asm *ass)
{
	if (**err->args == DIRECT_CHAR)
	{
		(*err->args)++;
		err->count++;
		if (**err->args == LABEL_CHAR)
			get_str_value(err, c_temp);
		else if (**err->args == '-' || ft_isdigit(**err->args))
			c_temp->args[err->i].num_value = ft_atoi(*err->args);
		else
			syntax_error(ass->begin_line, get_error_line_address(err),
			ass->line_number, "INSTRUCTION");
		c_temp->args[err->i].size_of_arg = g_op_tab[c_temp->index].label_size;
		c_temp->args[err->i].type_of_arg = T_DIR;
		count_codage(err->i, T_DIR, c_temp);
	}
}

void	push_tind(t_arg_error *err, t_command *c_temp, t_asm *ass)
{
	if (**err->args == LABEL_CHAR)
		get_str_value(err, c_temp);
	else if (ft_isdigit(**err->args) || **err->args == '-')
		c_temp->args[err->i].num_value = ft_atoi(*err->args);
	else
		syntax_error(ass->begin_line, get_error_line_address(err),
		ass->line_number, "dINSTRUCTION");
	c_temp->args[err->i].size_of_arg = 2;
	c_temp->args[err->i].type_of_arg = T_IND;
	count_codage(err->i, T_IND, c_temp);
}

void	push_args(t_asm *ass, t_command *c_temp, char *line, char **args)
{
	t_arg_error	err;

	err.i = 0;
	err.count = 0;
	err.args = args;
	err.line = line;
	while (*err.args)
	{
		err.temp = *err.args;
		check_begin_arg_line(&err, c_temp, ass);
		if (g_op_tab[c_temp->index].args[err.i] & T_REG)
			push_treg(&err, c_temp, ass);
		if (g_op_tab[c_temp->index].args[err.i] & T_DIR)
			push_tdir(&err, c_temp, ass);
		if ((g_op_tab[c_temp->index].args[err.i] & T_IND)
		&& !c_temp->args[err.i].size_of_arg)
			push_tind(&err, c_temp, ass);
		check_end_arg_line(&err, c_temp, ass);
		free(err.temp);
		err.args++;
		err.i++;
	}
	if (err.i != g_op_tab[c_temp->index].args_amount)
		simple_error("Invalid number of arguments", ass->line_number);
}

void	push_command(t_asm *ass, t_command *c_temp, int index, char *line)
{
	char	**args;
	int		i;

	c_temp->opcode = g_op_tab[index].opcode;
	c_temp->index = index;
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ';')
		{
			line[i] = 0;
			break ;
		}
		i++;
	}
	check_valid_separator(ass, line, index);
	if (*line == COMMENT_CHAR || *line == ';')
		syntax_error(ass->begin_line, line, ass->line_number, "ENDLINE");
	args = ft_strsplit(line, SEPARATOR_CHAR);
	if (!*args || (args[0][0] != ' ' && args[0][0] != '\t'
		&& args[0][0] != DIRECT_CHAR && args[0][0] != '-'))
		syntax_error(ass->begin_line, line, ass->line_number, "INSTRUCTION");
	push_args(ass, c_temp, line, args);
	free(args);
}
