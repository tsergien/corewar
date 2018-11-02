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

#include "../../libft/libft.h"
#include "../includes/op.h"



void parse_header(t_asm * ass)
{
    char *line;
    int i = 0;
    while (get_next_line(ass->fd, &line) > 0)
    {
        while (line[i])
        {
            if (line[i] == ' ' || line[i] == '\t')
            {
                i++;
                continue;
            }
            else if (line[i] == '.')
            {
                if (!ft_strncmp(line + i, NAME_CMD_STRING, 5))
                {
                    i = i + 5;
                    while (line[i] == ' ' || line[i] == '\t') i++;
                } 
                else if (!ft_strncmp(line + i, COMMENT_CMD_STRING, 8))
                {

                }    
                else
                    ft_printf("Tu sho dibil cuka ili sho?");
            }
            else if (line[i] == '#')
            {

            }
            else
            {
                ft_printf("Tu sho dibil cuka ili sho?");
                return ;
            }
            i++;
        }
        free(line);
    }
    ft_printf("%s", line);
    free(line);
}
