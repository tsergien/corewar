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

#include <fcntl.h>
#include "../includes/vm_corewar.h"

void		ft_error(char *str)
{
	write(2, str, ft_strlen(str) + 1);
	exit(0);
}

static void	usage(void)
{
	ft_printf("usage: ./corewar player1.cor [player2.cor] \
[player3.cor] [player4.cor]\n");
	exit(0);
}

int			main(int argc, char **argv)
{
	int			i;
	int			fd;
	t_game		*g;

	if (argc < 2 || argc > 5)
		usage();
	g = (t_game *)malloc(sizeof(t_game));
	g->champs_num = 0;
	ft_printf("champs_num: %d\n", g->champs_num);
	i = 0;
	for (int i = 0; i < MEM_SIZE; i++)
	{
		g->map[i].champ = 0;
	}
	g->champs_num = argc - 1;
	while (++i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		get_champ(g, fd, i - 1);
		ft_printf("%s\n", g->champ[i - 1].comment);
		ft_printf("%s\n", g->champ[i - 1].prog_name);
		ft_printf("%u\n", g->champ[i - 1].prog_size);
	}
	show_field(g);
	return (0);
}
