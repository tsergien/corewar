/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:27:51 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 11:27:53 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		reverse_byte(unsigned int nbr, int size)
{
	unsigned char	*res;
	unsigned char	*nbr_chr;
	unsigned int	reverse;
	int				i;

	reverse = 0;
	nbr_chr = (unsigned char *)&nbr;
	res = (unsigned char *)&reverse;
	i = 0;
	while (size)
	{
		res[i] = nbr_chr[size - 1];
		size--;
		i++;
	}
	return (reverse);
}

void	make_execute(t_asm *ass)
{
	char *dot;

	dot = ft_strchr(ass->binary_name, '.');
	while (dot)
	{
		if (ft_strnequ(dot, ".s", 3))
		{
			*dot = 0;
			ft_strcat(ass->binary_name, ".cor");
			break ;
		}
		dot++;
		dot = ft_strchr(dot, '.');
	}
	if (!dot)
		ft_strcpy(ass->binary_name, ".cor");
	ass->binary_fd = open(ass->binary_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
}

void	write_header(t_asm *ass, char *null)
{
	make_execute(ass);
	ass->magic = reverse_byte(COREWAR_EXEC_MAGIC, 4);
	ass->header.prog_size = reverse_byte(ass->header.prog_size, 4);
	write(ass->binary_fd, &ass->magic, 4);
	write(ass->binary_fd, &ass->header.prog_name, PROG_NAME_LENGTH);
	write(ass->binary_fd, null, 4);
	write(ass->binary_fd, &ass->header.prog_size, 4);
	write(ass->binary_fd, &ass->header.comment, COMMENT_LENGTH);
	write(ass->binary_fd, null, 4);
}

void	write_file(t_asm *ass)
{
	char		null[4];
	int			i;
	t_command	*cmd_temp;

	ft_bzero(null, 4);
	write_header(ass, null);
	cmd_temp = ass->cmd_lst;
	while (cmd_temp)
	{
		if (g_op_tab[cmd_temp->index].opcode)
			write(ass->binary_fd, &cmd_temp->opcode, 1);
		if (g_op_tab[cmd_temp->index].codage)
			write(ass->binary_fd, &cmd_temp->codage, 1);
		i = 0;
		while (i < g_op_tab[cmd_temp->index].args_amount)
		{
			if (cmd_temp->args[i].size_of_arg > 1)
				cmd_temp->args[i].num_value = reverse_byte(
					cmd_temp->args[i].num_value, cmd_temp->args[i].size_of_arg);
			write(ass->binary_fd, &cmd_temp->args[i].num_value,
				cmd_temp->args[i].size_of_arg);
			i++;
		}
		cmd_temp = cmd_temp->next;
	}
}
