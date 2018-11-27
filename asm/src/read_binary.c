/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:23:46 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/27 16:23:47 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		read_args(int binary_fd, t_command *cmd_temp)
{
	int i;
	int size_of_command;

	size_of_command = 1;
	if ((cmd_temp->index = get_index(cmd_temp->opcode)) == -1)
		bonus_r_error("Invalid opcode.");
	if (g_op_tab[cmd_temp->index].codage)
	{
		read(binary_fd, &cmd_temp->codage, 1);
		size_of_command++;
	}
	i = 0;
	while (i < g_op_tab[cmd_temp->index].args_amount)
	{
		count_reverse_codage(i, cmd_temp);
		read(binary_fd, &cmd_temp->args[i].num_value,
			cmd_temp->args[i].size_of_arg);
		if (cmd_temp->args[i].size_of_arg > 1)
			cmd_temp->args[i].num_value = reverse_byte(
				cmd_temp->args[i].num_value, cmd_temp->args[i].size_of_arg);
		size_of_command += cmd_temp->args[i].size_of_arg;
		i++;
	}
	return (size_of_command);
}

void	read_commands(t_asm *ass)
{
	t_command	*cmd_temp;
	int			temp_size;

	temp_size = ass->header.prog_size;
	while (temp_size)
	{
		cmd_temp = get_cmd_list(ass);
		read(ass->binary_fd, &cmd_temp->opcode, 1);
		temp_size -= read_args(ass->binary_fd, cmd_temp);
	}
}

void	write_asm_code(t_asm *ass)
{
	t_command	*cmd_temp;
	int			i;

	ft_printf(".name \"%s\"\n", ass->header.prog_name);
	ft_printf(".comment \"%s\"\n\n", ass->header.comment);
	cmd_temp = ass->cmd_lst;
	while (cmd_temp)
	{
		i = 0;
		ft_printf("\t%s\t", g_op_tab[cmd_temp->index].name);
		while (i < g_op_tab[cmd_temp->index].args_amount)
		{
			if (cmd_temp->args[i].type_of_arg == T_REG)
				write(ass->fd, "r", 1);
			else if (cmd_temp->args[i].type_of_arg == T_DIR)
				write(ass->fd, "%", 1);
			ft_printf("%d", cmd_temp->args[i].num_value);
			i++;
			if (i != g_op_tab[cmd_temp->index].args_amount)
				write(ass->fd, ", ", 2);
		}
		write(ass->fd, "\n", 1);
		cmd_temp = cmd_temp->next;
	}
}

void	read_header(t_asm *ass)
{
	char null[4];

	if (!read(ass->fd, &ass->magic, 4))
		bonus_r_error("Not enough space to read magic header in binary file");
	if (!read(ass->fd, ass->header.prog_name, PROG_NAME_LENGTH))
		bonus_r_error("Not enough space to read program name in binary file");
	if (!read(ass->fd, null, 4))
		bonus_r_error("Not enough space to read 4-bytes NULL in binary file");
	if (!read(ass->fd, &ass->header.prog_size, 4))
		bonus_r_error("Not enough space to read program size in binary file");
	if (!read(ass->fd, ass->header.comment, COMMENT_LENGTH))
		bonus_r_error("Not enough space to read comment in binary file");
	if (!read(ass->fd, null, 4))
		bonus_r_error("Not enough space to read 4-bytes NULL in binary file");
	ass->magic = reverse_byte(ass->magic, 4);
	ass->header.prog_size = reverse_byte(ass->header.prog_size, 4);
}

void	read_binary(t_asm *ass)
{
	ass->binary_fd = ass->fd;
	read_header(ass);
	read_commands(ass);
	make_code_file(ass);
	g_printf_fd = ass->fd;
	write_asm_code(ass);
	g_printf_fd = 1;
	ft_printf("Writing program code to %s\n", ass->binary_name);
}
