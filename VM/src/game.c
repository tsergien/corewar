/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:07:31 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/22 13:07:34 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

void		add_cursor(int champ_ind, t_game *g)
{
	t_cursor	*temp;
	int			pos;

	pos = champ_ind * (MEM_SIZE / g->champs_num);
	if (!g->cursor)
	{
		g->cursor = (t_cursor *)malloc(sizeof(t_cursor));
		temp = g->cursor;
	}
	else
	{
		temp = g->cursor;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = (t_cursor *)malloc(sizeof(t_cursor));
		temp = temp->next;
	}
	ft_bzero(temp, sizeof(t_cursor));
	temp->index = pos;
	temp->alive = 1;
	temp->parent_ind = champ_ind;
	temp->command = g->map[pos].byte;
	temp->cycles_to_exec = g_op_tab[g->map[pos].byte - 1].cycles;
}

char		is_alives(t_cursor *c)
{
	while (c)
	{
		if (c->alive)
			return (1);
		c = c->next;
	}
	return (0);
}

void		exec_comm(t_cursor *c, t_game *g, int (*f)(t_game *g, t_cursor *c))
{
	unsigned int		shift;

	if (c->cycles_to_exec == 0)
	{
		ft_printf("________________________\n");
		ft_printf("________________________\n");
		ft_printf("index before: %d\n", c->index);
		ft_printf("com: %s\n", g_op_tab[c->command - 1].name);
		shift = f(g, c);
		if (c->command - 1 != 8 || c->carry == 0)
			c->index = (shift + c->index) % MEM_SIZE;
		c->command = g->map[c->index].byte;
		c->cycles_to_exec = g_op_tab[c->command - 1].cycles;
		ft_printf("index after: %d\n", c->index);
	}
	else
		c->cycles_to_exec--;
}

void		do_step(t_game *g)
{
	t_cursor	*tmp;
	int			(*f[16])(t_game *g, t_cursor *c);

	f[0] = &live;
	f[1] = &ld;
	f[2] = &st;
	f[3] = &add;
	f[4] = &sub;
	f[5] = &and_;
	f[6] = &or_;
	f[7] = &xor_;
	f[8] = &zjmp;
	f[9] = &ldi;
	f[10] = &sti;
	f[11] = &fork_;
	f[12] = &lld;
	f[13] = &lldi;
	f[14] = &lfork;
	f[15] = &aff;
	tmp = g->cursor;
	while (tmp && !g->pause)
	{
		while (tmp->command == 1 || tmp->command > 16)
		{
			tmp->index = (tmp->index + 1) % MEM_SIZE;
			tmp->command = g->map[tmp->index].byte;
		}
		exec_comm(tmp, g, f[tmp->command - 1]);
		tmp = tmp->next;
	}
}
