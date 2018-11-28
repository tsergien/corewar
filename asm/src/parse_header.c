/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:41:29 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/10/30 16:44:54 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		check_line(char **line, int line_number)
{
	char	*temp;

	temp = *line;
	while (**line == '\t' || **line == ' ')
		(*line)++;
	if (**line == '\0' || **line == COMMENT_CHAR || **line == ';')
		return (0);
	else if (**line == '.')
		if (!ft_strncmp(*line, NAME_CMD_STRING, 5)
		|| !ft_strncmp(*line, COMMENT_CMD_STRING, 8))
			return (1);
	if (**line == '"')
		syntax_error_string(temp, *line, line_number);
	else if (consist("±§!@$%^&*.()+_-=/\\][`{}'<>", **line))
		lexical_error(temp, *line, line_number);
	else if (**line == ',')
		syntax_error_separator(temp, *line, line_number);
	else if (**line == ':')
		syntax_error(temp, *line, line_number, "INDIRECT_LABEL");
	else
		syntax_error(temp, *line, line_number, "INSTRUCTION");
	return (0);
}

void	check_exist(int i, int size, t_asm *ass)
{
	if (i >= size)
	{
		ft_printf("[Error handled] %s is too big.\n",
		size == PROG_NAME_LENGTH ? "Name" : "Comment");
		exit(0);
	}
	if (size == PROG_NAME_LENGTH)
		ass->header.name_exist = 1;
	else
		ass->header.comment_exist = 1;
}

void	fillbuf(char *buf, t_asm *ass, char **line, int size)
{
	char	*tmp;
	int		i;

	i = 0;
	(*line)++;
	while (i < size)
	{
		if (!**line)
		{
			tmp = *line;
			if (get_next_line(ass->fd, line) == 0)
				syntax_error(ass->begin_line, tmp, ass->line_number, "END");
			ass->line_number++;
			ass->begin_line = *line;
			buf[i++] = '\n';
		}
		if (**line == '\0')
			continue;
		if (**line == '\"')
			if (end_header_line(line, ass))
				break ;
		buf[i++] = *((*line)++);
	}
	check_exist(i, size, ass);
}

void	parse_dot(t_asm *ass, char *line)
{
	int i;

	i = 2;
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
	{
		line += 5;
		i = 1;
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		line += 8;
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '"')
	{
		if ((ass->header.name_exist && i == 1) ||
		(ass->header.comment_exist && i == 2))
			syntax_error_double_command(PROG_NAME_LENGTH,
			ass->begin_line, line, ass->line_number);
		if (i == 1)
			fillbuf(ass->header.prog_name, ass, &line, PROG_NAME_LENGTH);
		else
			fillbuf(ass->header.comment, ass, &line, COMMENT_LENGTH);
	}
	else
		syntax_error(ass->begin_line, line, ass->line_number, "ENDLINE");
}

void	parse_header(t_asm *ass)
{
	char *line;

	ass->line_number = 0;
	while (get_next_line(ass->fd, &ass->begin_line) > 0)
	{
		ass->line_number++;
		ass->last_line_size = ft_strlen(ass->begin_line);
		line = ass->begin_line;
		if (*line == '\0')
		{
			free(ass->begin_line);
			continue ;
		}
		if (check_line(&line, ass->line_number))
			parse_dot(ass, line);
		if (ass->header.comment_exist && ass->header.name_exist)
		{
			free(ass->begin_line);
			return ;
		}
		free(ass->begin_line);
	}
}
