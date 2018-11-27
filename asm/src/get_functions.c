/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 12:31:14 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 12:31:14 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int			get_index(int opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (opcode == g_op_tab[i].opcode)
			return (i);
		i++;
	}
	return (-1);
}

void		get_type_and_size_of_args(int i, t_command *c_temp, int value)
{
	if (value == 1)
	{
		c_temp->args[i].type_of_arg = T_REG;
		c_temp->args[i].size_of_arg = 1;
	}
	else if (value == 2)
	{
		c_temp->args[i].type_of_arg = T_DIR;
		c_temp->args[i].size_of_arg = g_op_tab[c_temp->index].label_size;
	}
	else if (value == 3)
	{
		c_temp->args[i].type_of_arg = T_IND;
		c_temp->args[i].size_of_arg = 2;
	}
}

char		*get_error_line_address(t_arg_error *err)
{
	return (err->line + err->count + err->i);
}

t_command	*get_cmd_list(t_asm *ass)
{
	t_command	*c_temp;

	c_temp = ass->cmd_lst;
	if (!ass->cmd_lst)
	{
		ass->cmd_lst = (t_command *)malloc(sizeof(t_command));
		ass->cmd_lst->codage = 0;
		ass->cmd_lst->opcode = 0;
		ass->cmd_lst->label = NULL;
		ass->cmd_lst->next = NULL;
		c_temp = ass->cmd_lst;
	}
	else
		while (c_temp->next)
			c_temp = c_temp->next;
	if (c_temp->opcode)
	{
		c_temp->next = (t_command *)malloc(sizeof(t_command));
		c_temp = c_temp->next;
		c_temp->codage = 0;
		c_temp->opcode = 0;
		c_temp->label = NULL;
		c_temp->next = NULL;
	}
	return (c_temp);
}

t_labels	*get_label_list(t_command *c_temp)
{
	t_labels *l_temp;

	if (!c_temp->label)
	{
		c_temp->label = (t_labels *)malloc(sizeof(t_labels));
		l_temp = c_temp->label;
	}
	else
	{
		l_temp = c_temp->label;
		while (l_temp->next)
			l_temp = l_temp->next;
		l_temp->next = (t_labels *)malloc(sizeof(t_labels));
		l_temp = l_temp->next;
	}
	l_temp->next = NULL;
	l_temp->label = NULL;
	return (l_temp);
}
