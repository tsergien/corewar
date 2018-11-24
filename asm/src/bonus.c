/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:17:35 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 11:17:35 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	print_labels(t_command *cmd)
{
	t_labels	*label;

	label = cmd->label;
	while (label)
	{
		ft_printf("%-11d:    %s:\n", cmd->size_before, label->label);
		label = label->next;
	}
	if (!cmd->opcode)
		exit(0);
	ft_printf("%-5d(%-3d) :        %-10s", cmd->size_before,
	cmd->size_of, g_op_tab[cmd->index].name);
}

void	print_args(t_command *cmd)
{
	int		i;

	i = 0;
	while (i < g_op_tab[cmd->index].args_amount)
	{
		if (cmd->args[i].type_of_arg == T_REG)
			ft_printf("r");
		else if (cmd->args[i].type_of_arg == T_DIR)
			ft_printf("%%");
		if (!cmd->args[i].str_value)
			ft_printf("%-17lld", cmd->args[i].num_value);
		else
			ft_printf(":%-16s", cmd->args[i].str_value);
		if (cmd->args[i].type_of_arg == T_IND)
			write(1, " ", 1);
		i++;
	}
	ft_printf("\n%20c%-4d", ' ', cmd->opcode);
	if (g_op_tab[cmd->index].codage)
		ft_printf("%-6d", cmd->codage);
	else
		ft_printf("      ");
}

void	print_num_value_bytes(t_command *cmd)
{
	int				i;
	int				num;
	int				j;
	unsigned char	*p;

	i = 0;
	while (i < g_op_tab[cmd->index].args_amount)
	{
		if (cmd->args[i].size_of_arg > 1)
		{
			num = reverse_byte(cmd->args[i].num_value,
				cmd->args[i].size_of_arg);
			j = 0;
			p = (unsigned char *)&num;
			while (j < cmd->args[i].size_of_arg)
			{
				ft_printf("%-4d", p[j]);
				j++;
			}
			ft_printf(" %-*c", (4 * (4 - cmd->args[i].size_of_arg)) + 1, ' ');
		}
		else
			ft_printf("%-18lld", cmd->args[i].num_value);
		i++;
	}
}

void	print_num_value(t_command *cmd)
{
	int i;

	ft_printf("\n%20c%-4d", ' ', cmd->opcode);
	if (g_op_tab[cmd->index].codage)
		ft_printf("%-6d", cmd->codage);
	else
		ft_printf("      ");
	i = 0;
	while (i < g_op_tab[cmd->index].args_amount)
	{
		ft_printf("%-18d", cmd->args[i].num_value);
		i++;
	}
	write(1, "\n\n", 2);
}

void	bonus_flag_info(t_asm *ass)
{
	t_command	*cmd;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", ass->header.prog_size);
	ft_printf("Name : \"%s\"\n", ass->header.prog_name);
	ft_printf("Comment : \"%s\"\n\n", ass->header.comment);
	cmd = ass->cmd_lst;
	while (cmd)
	{
		print_labels(cmd);
		print_args(cmd);
		print_num_value_bytes(cmd);
		print_num_value(cmd);
		cmd = cmd->next;
	}
}
