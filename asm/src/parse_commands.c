/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:54:04 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/06 16:54:04 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	check_valid_separator(t_asm *ass, char *line, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			i++;
			if (line[i] == SEPARATOR_CHAR)
			{
				line[i + 1] = 0;
				syntax_error(ass->begin_line, line + i,
				ass->line_number, "SEPARATOR");
			}
			count++;
		}
		i++;
	}
	if (g_op_tab[index].args_amount != count + 1)
		simple_error("Invalid separators number", ass->line_number);
}

void	count_codage(int i, int type, t_command *c_temp)
{
	char	value;

	if (type & T_REG)
		value = 1;
	else if (type & T_DIR)
		value = 2;
	else if (type & T_IND)
		value = 3;
	if (i == 0)
		c_temp->codage = c_temp->codage | (value << 6);
	else if (i == 1)
		c_temp->codage = c_temp->codage | (value << 4);
	else if (i == 2)
		c_temp->codage = c_temp->codage | (value << 2);
}

void	push_lable(t_asm *ass, char *line)
{
	t_command	*c_temp;
	t_labels	*l_temp;

	c_temp = get_cmd_list(ass);
	l_temp = get_label_list(c_temp);
	l_temp->label = ft_strdup(line);
	line = line + ft_strlen(l_temp->label) + 1;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line)
		check_command(ass, c_temp, line);
}

void	parse_commands(t_asm *ass)
{
	char	*line;

	while (get_next_line(ass->fd, &ass->begin_line) > 0)
	{
		line = ass->begin_line;
		ass->last_line_size = ft_strlen(ass->begin_line);
		ass->line_number++;
		if (!*line)
		{
			free(ass->begin_line);
			continue;
		}
		check_lable(ass, line);
		free(ass->begin_line);
	}
	free(ass->begin_line);
	line = (char *)malloc(ass->last_line_size + 2);
	lseek(ass->fd, -ass->last_line_size, SEEK_CUR);
	ft_bzero(line, ass->last_line_size + 2);
	read(ass->fd, line, ass->last_line_size + 2);
	if (ass->last_line_size == 0)
		ass->line_number++;
	check_last_line(line, ass);
	free(line);
}
