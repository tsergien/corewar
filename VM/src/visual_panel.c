/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_panel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:59:38 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/21 14:59:40 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

unsigned long	processes_sum(t_game *g)
{
	int				i;
	unsigned long	res;

	res = 0;
	i = -1;
	while (++i < g->champs_num)
		res += g->champ[i].processes;
	return (res);
}

static void		print_static_strs(WINDOW *win, int pos, t_game *g)
{
	mvwprintw(win, 2, 3, "             ");
	(g->pause) ? mvwprintw(win, 2, 3, "** PAUSED **") :
	mvwprintw(win, 2, 3, "** RUNNING **");
	mvwprintw(win, 4, 25, "    ");
	mvwprintw(win, 4, 3, "Cycles/second limit : %d", g->cycles_limit);
	mvwprintw(win, 7, 3, "Cycle : %d", g->cycle);
	mvwprintw(win, 9, 3, "Processes : %d", processes_sum(g));
	mvwprintw(win, pos, 3, "Live breakdown for current period :");
	mvwprintw(win, pos + 3, 3, "Live breakdown for last period :");
	wattron(win, COLOR_PAIR(7));
	mvwprintw(win, pos + 1, 3,
	"[--------------------------------------------------]");
	mvwprintw(win, pos + 4, 3,
	"[--------------------------------------------------]");
	wattroff(win, COLOR_PAIR(7));
	mvwprintw(win, pos + 6, 3, "CYCLE_TO_DIE : %d", g->cycles_to_die);
	mvwprintw(win, pos + 8, 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(win, pos + 10, 3, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(win, pos + 12, 3, "MAX_CHECKS : %d", MAX_CHECKS);
}

static void		diagram1(WINDOW *win, t_game *g, int pos)
{
	char			i;
	char			j;
	char			shift;
	unsigned int	sum;

	shift = 0;
	sum = 0;
	i = -1;
	while (++i < g->champs_num)
		sum += g->champ[(int)i].current_lives;
	i = -1;
	while (++i < g->champs_num)
	{
		j = -1;
		wattron(win, COLOR_PAIR(i + 1));
		while (sum > 0 && ++j < (50 * ((double)g->champ[(int)i].current_lives
				/ sum)) + 0.5 && shift + 4 + j < 54)
			mvwprintw(win, pos + 1, shift + 4 + j, "-");
		shift += j;
		wattroff(win, COLOR_PAIR(i + 1));
	}
}

static void		diagram2(WINDOW *win, t_game *g, int pos)
{
	char			i;
	char			j;
	char			shift;
	unsigned int	sum;

	i = -1;
	shift = 0;
	sum = 0;
	while (++i < g->champs_num)
		sum += g->champ[(int)i].last_live;
	i = -1;
	while (++i < g->champs_num)
	{
		j = -1;
		wattron(win, COLOR_PAIR(i + 1));
		while (sum > 0 && ++j < (50 * ((double)g->champ[(int)i].last_live
		/ sum)) + 0.5 && shift + 4 + j < 54)
			mvwprintw(win, pos + 1, shift + 4 + j, "-");
		shift += j;
		wattroff(win, COLOR_PAIR(i + 1));
	}
}

void			print_panel(t_game *g, WINDOW *win)
{
	char			i;
	char			pos;

	i = -1;
	pos = 11;
	wattron(win, A_BOLD);
	while (++i < g->champs_num)
	{
		mvwprintw(win, pos, 3, "Player -%d : ", i + 1);
		wattron(win, COLOR_PAIR(i + 1));
		mvwprintw(win, pos, 15, "%.41s", g->champ[(int)i].prog_name);
		wattroff(win, COLOR_PAIR(i + 1));
		mvwprintw(win, pos + 1, 3, "  Last live :%22d",
		g->champ[(int)i].last_live);
		mvwprintw(win, pos + 2, 3, "  Lives in current period :%8d",
		g->champ[(int)i].current_lives);
		pos += 4;
	}
	diagram1(win, g, pos);
	diagram2(win, g, pos);
	print_static_strs(win, pos, g);
	wattroff(win, A_BOLD);
}
