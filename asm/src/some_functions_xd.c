/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_functions_xd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:10:03 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/24 11:10:04 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	simple_error(const char *str, int line_number)
{
	ft_printf("[Error] Line %d. %s.", line_number, str);
	exit(0);
}

int		end_header_line(char **line, t_asm *ass)
{
	while (*((*line)++))
	{
		if (!**line || **line == ' ' || **line == '\t')
			continue;
		else if (**line == COMMENT_CHAR || **line == ';')
			break ;
		else
			syntax_error(ass->begin_line, *line,
				ass->line_number, "INSTRUCTION");
	}
	return (1);
}
