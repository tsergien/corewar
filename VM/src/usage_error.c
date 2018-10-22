/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:52:10 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/21 14:54:19 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

void		ft_error(char *str)
{
	write(2, str, ft_strlen(str) + 1);
	exit(0);
}

void		usage(void)
{
	ft_printf("usage: [-v] [-dump nbr_cycles] [-n player_number]\
	./corewar <player1.cor> <...>\n");
	exit(0);
}
