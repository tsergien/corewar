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
	t_cursor	*new_elem;
	int			pos;

	pos = champ_ind * (MEM_SIZE / g->champs_num);
	new_elem = (t_cursor *)malloc(sizeof(t_cursor));
	ft_bzero(new_elem, sizeof(t_cursor));
	new_elem->index = pos;
	new_elem->alive = 1;
	new_elem->parent_ind = champ_ind;
	new_elem->command = g->map[pos].byte;
	new_elem->cycles_to_exec = g_op_tab[g->map[pos].byte - 1].cycles;
	new_elem->registr[1] = -(champ_ind + 1);
	new_elem->next = g->cursor;
	g->cursor = new_elem;
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

	if (c->cycles_to_exec == 1)
	{
		// ft_printf("________________________\n");
		// ft_printf("________________________\n");
		// ft_printf("index before: %d\ncom: %s\n", c->index, g_op_tab[c->command - 1].name);
		shift = f(g, c);
		if (c->command - 1 != 8 || c->carry == 0)
			c->index = (shift + c->index) % MEM_SIZE;
		// ft_printf("index after: %d\n", c->index);
		c->command = g->map[c->index].byte;
		c->cycles_to_exec = g_op_tab[c->command - 1].cycles;
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
	while (tmp)
	{
		while (tmp->command == 0 || tmp->command > 15)
		{
			tmp->index = (tmp->index + 1) % MEM_SIZE;
			tmp->command = g->map[tmp->index].byte;
		}
		exec_comm(tmp, g, f[tmp->command - 1]);
		tmp = tmp->next;
	}
	g->cycle++;
}
