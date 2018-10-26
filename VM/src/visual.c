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

static void		controller(char c, t_game *g)
{
	if (c == 27)
	{
		endwin();
		exit(0);
	}
	else if (c == 32)
		g->pause = !g->pause;
	else if (c == 113 && g->cycles_limit > 1)
	{
		if (g->cycles_limit - 10 < 1)
			g->cycles_limit = 1;
		else
			g->cycles_limit -= 10;
	}
	else if (c == 114 && g->cycles_limit < 1000)
	{
		if (g->cycles_limit + 10 > 1000)
			g->cycles_limit = 1000;
		else
			g->cycles_limit += 10;
	}
	else if (c == 119 && g->cycles_limit > 1)
		g->cycles_limit--;
	else if (c == 101 && g->cycles_limit < 1000)
		g->cycles_limit += 1;
	else if (c == 's')
		do_step(g);
}

static void		print_map(t_game *g, WINDOW *win)
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
			wattron(win, A_BOLD | COLOR_PAIR(7));
		else
			wattron(win, COLOR_PAIR(g->map[i].champ));
		mvwprintw(win, i / 64 + 2, 3 * (i % 64) + 3, "%02x", g->map[i].byte);
		if (!g->map[i].champ)
			wattroff(win, A_BOLD | COLOR_PAIR(7));
		else
			wattroff(win, COLOR_PAIR(g->map[i].champ));
	}
}

static void		cursors_output(t_game *g, WINDOW *win)
{
	t_cursor	*temp;

	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	temp = g->cursor;
	wattron(win, COLOR_PAIR(5));
	while (temp)
	{
		mvwprintw(win, temp->index / 64 + 2, 3 * (temp->index % 64) + 3, "%02x", g->map[temp->index].byte);
		temp = temp->next;
	}
	wattroff(win, COLOR_PAIR(5));
}

static void		do_while(WINDOW *win1, WINDOW *win2, t_game *g)
{
	clock_t		prev;

	prev = 0;
	while (is_alives(g->cursor) && g->cycles_to_die > 0)
	{
		while (clock() - prev <= 100000 / (unsigned long)g->cycles_limit)
			continue ;
		prev = clock();
		nodelay(win2, true);
		wattron(win1, COLOR_PAIR(5));
		wattron(win2, COLOR_PAIR(5));
		wborder(win1, 42, 42, 42, 42, 42, 42, 42, 42);
		wborder(win2, 42, 42, 42, 42, 42, 42, 42, 42);
		refresh();
		wrefresh(win1);
		wrefresh(win2);
		wattroff(win1, COLOR_PAIR(5));
		wattroff(win2, COLOR_PAIR(5));

		(!g->pause) ? do_step(g) : 0;

		print_map(g, win1);
		print_panel(g, win2);
		cursors_output(g, win1);
		controller(wgetch(win2), g);
	}
}

void			show_field(t_game *g)
{
	WINDOW	*win1;
	WINDOW	*win2;

	initscr();
	noecho();
	curs_set(0);
	win1 = newwin(68, 197, 0, 0);
	win2 = newwin(68, 58, 0, 196);
	keypad(win1, TRUE);
	keypad(win2, TRUE);
	start_color();
	init_color(COLOR_MAGENTA, 410, 410, 410);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	do_while(win1, win2, g);
}
