/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:40:04 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/18 15:42:27 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"
#include "../../libft/libft.h"
#include <fcntl.h>

t_champ		*get(char *file)
{
    t_champ			*tanya;
    int				fd;
    unsigned char	buf[4];

    tanya = (t_champ *)malloc(sizeof(t_champ));
	fd = open(file, O_RDONLY);
	read(fd, buf, 4);
	if (ft_strcmp(buf, ))
	while (read(fd, buf, 4))
	{

	}
}
