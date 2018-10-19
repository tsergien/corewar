/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:26:38 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/19 16:26:41 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"
#include <time.h>

void		controller(char c)
{
	if (c == 27)
	{
		endwin();
		exit(0);
	}
}

void		print_map(t_game *g, WINDOW *win)
{
	int i;

	i = -1;
	init_pair(7, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	while (++i < MEM_SIZE)
	{
		if (!g->map[i].champ)
		{
			wattron(win, A_BOLD);
			wattron(win, COLOR_PAIR(7));
		}
		else
			wattron(win, COLOR_PAIR(g->map[i].champ));
		mvwprintw(win, i / 64 + 2, 3 * (i % 64) + 3, "%02x", g->map[i].byte);
		if (!g->map[i].champ)
		{
			wattroff(win, A_BOLD);
			wattroff(win, COLOR_PAIR(7));
		}
		wattroff(win, COLOR_PAIR(g->map[i].champ));
	}
}

void		show_field(t_game *g)
{
	WINDOW	*win1 = NULL;
	WINDOW	*win2 = NULL;

	(void)g;
	initscr();
	noecho();
	curs_set(0);
	win1 = newwin(68, 197, 0, 0);
	win2 = newwin(68, 58, 0, 196);
	keypad(win1, TRUE);
	keypad(win2, TRUE);
	mouseinterval(0);
	use_default_colors();
	start_color();
	init_color(COLOR_MAGENTA, 410, 410, 410);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	while (1)
	{
		usleep(290000);
		nodelay(win1, true);
		wattron(win1, COLOR_PAIR(5));
		wattron(win2, COLOR_PAIR(5));
		wborder(win1, 42, 42, 42, 42, 42, 42, 42, 42);
		wborder(win2, 42, 42, 42, 42, 42, 42, 42, 42);
		
		refresh();
		wrefresh(win1);
		wrefresh(win2);
		wattroff(win1, COLOR_PAIR(5));
		wattroff(win2, COLOR_PAIR(5));
		print_map(g, win1); 

		controller(wgetch(win1));
	}
}