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

char		*get_error_line_address(t_arg_error *err)
{
	int		count;
	char	**temp;

	count = 0;
	temp = err->args_temp;
	while (*temp)
	{
		while (**temp)
		{
			if (*err->args == *temp)
				return (err->line + count);
			count++;
			(*temp)++;
		}
		temp++;
		count++;
	}
	return (err->line + count);
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
