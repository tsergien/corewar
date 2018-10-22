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

int			count_players(int ac, char **av)
{
	int		i;
	int		players;

	i = 0;
	players = 0;
	while (++i < ac)
	{
		if (ft_strstr(av[i], ".cor"))
			players++;
	}
	return (players);
}

static void	get_player(t_game *g, int *i, char **av)
{
	int	n;

	n = ft_atoi(av[++(*i)]) - 1;
	(n < 0 || n > g->champs_num - 1) ? ft_error("Invalid index\n") : 0;
	g->champ[n].filled ? ft_error("Player is already assigned!\n") : 0;
	g->flags.n++;
	get_champ(g, open(av[++(*i)], O_RDONLY), n);
}

static void	get_flags(t_game *g, int ac, char **av)
{
	int				i;
	int				ind;

	i = 0;
	ind = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-v"))
			g->flags.v = 1;
		else if (!ft_strcmp(av[i], "-dump"))
			g->flags.nbr_cycles = ft_atoi(av[++i]);
		else if (!ft_strcmp(av[i], "-n"))
			get_player(g, &i, av);
		else
		{
			while (ind < 4 && g->champ[ind].filled)
				++ind;
			get_champ(g, open(av[i], O_RDONLY), ind);
			g->flags.n++;
		}
	}
	if (g->flags.n != g->champs_num)
		ft_error("Invalid players order\n");
}

static void	init(t_game *g, int ac, char **av)
{
	int		i;

	g->champs_num = 0;
	g->pause = 1;
	g->cycles_limit = 50;
	g->cycle = 0;
	g->champs_num = count_players(ac, av);
	g->flags.n = 0;
	g->flags.v = 0;
	g->flags.nbr_cycles = 0;
	g->cycles_to_die = CYCLE_TO_DIE;
	if (g->champs_num < 1 || g->champs_num > 4)
		usage();
	i = -1;
	while (++i < 4)
		g->champ[i].filled = 0;
	i = -1;
	while (++i < MEM_SIZE)
		g->map[i].champ = 0;
	get_flags(g, ac, av);
}

int			main(int argc, char **argv)
{
	t_game		*g;
	int			i;

	g = (t_game *)malloc(sizeof(t_game));
	init(g, argc, argv);
	i = -1;
	if (g->flags.v)
		show_field(g);
	else
	{
		ft_printf("Introducing contestants...\n");
		while (++i < g->champs_num)
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !)\n",
		i + 1, g->champ[i].prog_size, g->champ[i].prog_name,
		g->champ[i].comment);
		start_game(g);
	}
	return (0);
}
