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

void		add_cursor(t_cursor *head, int pos, int champ_ind, t_game *g)
{
	t_cursor *temp;

	if (!head)
	{
		head = (t_cursor *)malloc(sizeof(t_cursor));
		temp = head;
	}
	else
	{
		temp = head;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = (t_cursor *)malloc(sizeof(t_cursor));
		temp = temp->next;
	}
	temp->next = NULL;
	temp->index = pos;
	temp->alive = 1;
	temp->parent_ind = champ_ind;
	temp->carry = 0;
	temp->command = g->map[pos].byte;
	temp->cycles_to_exec = g_op_tab[g->map[pos].byte - 1].cycles;
	ft_bzero(temp->registr, sizeof(temp->registr));
}

static char	is_alives(t_cursor *c)
{
	t_cursor	*tmp;

	tmp = c;
	while (c)
	{
		if (c->alive)
			return (1);
		c = c->next;
	}
	return (0);
}

void		start_game(t_game *g)
{
	t_cursor	*cursor;
	int			i;

	i = -1;
	cursor = NULL;
	while (++i < g->champs_num)
		add_cursor(cursor, i * (MEM_SIZE / g->champs_num), i, g);
	while (is_alives(cursor) && g->cycles_to_die > 0)
	{
		//do stuff
	}
}
