/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:22:01 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 11:22:02 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	count_reverse_codage(int i, t_command *c_temp)
{
	unsigned char value;

	value = 0;
	if (g_op_tab[c_temp->index].codage)
	{
		if (i == 0)
			value = 3 & (c_temp->codage >> 6);
		else if (i == 1)
			value = 3 & (c_temp->codage >> 4);
		else if (i == 2)
			value = 3 & (c_temp->codage >> 2);
	}
	else
		value = 2;
	get_type_and_size_of_args(i, c_temp, value);
}

void	swap_lable_to_nbr(t_arg *arg, t_command *current_cmd,
	t_command *cmd_lst)
{
	t_labels	*temp_label;

	while (cmd_lst)
	{
		temp_label = cmd_lst->label;
		while (temp_label)
		{
			if (ft_strequ(arg->str_value, cmd_lst->label->label))
			{
				arg->num_value = cmd_lst->size_before -
				current_cmd->size_before;
				return ;
			}
			temp_label = temp_label->next;
		}
		cmd_lst = cmd_lst->next;
	}
	ft_printf("[Error] Label \"%s\" not found\n", arg->str_value);
	exit(0);
}

void	args_str_value_to_num_value(t_asm *ass)
{
	t_command	*cmd;
	int			i;

	cmd = ass->cmd_lst;
	while (cmd)
	{
		i = 0;
		if (!cmd->opcode)
			break ;
		while (i < g_op_tab[cmd->index].args_amount)
		{
			if (cmd->args[i].str_value)
				swap_lable_to_nbr(&(cmd->args[i]), cmd, ass->cmd_lst);
			i++;
		}
		cmd = cmd->next;
	}
}

void	count_size(t_asm *ass)
{
	t_command	*cmd;
	int			i;
	int			size_before_command;

	cmd = ass->cmd_lst;
	size_before_command = 0;
	while (cmd)
	{
		i = 0;
		if (!cmd->opcode)
			break ;
		cmd->size_of = 1;
		cmd->size_before = 0;
		while (i < g_op_tab[cmd->index].args_amount)
			cmd->size_of += cmd->args[i++].size_of_arg;
		cmd->size_of += g_op_tab[cmd->index].codage;
		cmd->size_before = size_before_command;
		size_before_command += cmd->size_of;
		cmd = cmd->next;
	}
	ass->header.prog_size = size_before_command;
	args_str_value_to_num_value(ass);
}
