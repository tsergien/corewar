/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:40:06 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/23 12:40:08 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

void		to_map(t_field *map, void *src, size_t size, unsigned ind)
{
	unsigned int	i;
	unsigned char	*csrc;

	i = -1;
	csrc = (unsigned char *)src;
	while (++i < size)
		map[(ind + i) % MEM_SIZE].byte = csrc[i];
}

void		from_map(void *dst, t_field *map, size_t size, unsigned ind)
{
	unsigned int	i;
	unsigned char	*csrc;

	i = -1;
	csrc = (unsigned char *)dst;
	while (++i < size && i < MEM_SIZE)
		csrc[i] = map[ind + i].byte;
}

void		live(t_game *g, t_cursor *c)
{
	char	name;
	int		i;

	i = -1;
	name = g->map[c->index + 4].byte;
	c->alive = 1;
	if (!g->flags.v)
		ft_printf("A process shows that player %d %S is alive",
	c->parent_ind + 1, g->champ[c->parent_ind].prog_name);
	while (++i < g->champs_num)
		if (15 - name == i)
		{
			g->champ[i].current_lives += 1;
			g->champ[i].last_live = g->cycle;
		}
}

void		ld(t_game *g, t_cursor *c)
{
	unsigned char	num;
	unsigned int	t_arg;
	unsigned char	t_reg;

	num = g->map[c->index + 1].byte;
	t_reg = g->map[c->index + 6].byte;
	from_map(&t_arg, g->map, 4, c->index + 2);
	if (num == 208)//T_IND
	{
		to_map(g->map, &t_arg, 4, c->index + 2);
		t_arg = t_arg % IDX_MOD;
		from_map(c->registr + t_reg, g->map, 4, c->index + t_arg);

	}
	else if (num == 144)//T_DIR
		ft_memcpy(c->registr + t_reg, &t_arg, 4);
	c->carry = (!t_arg) ? 1 : 0;
}

void		st(t_game *g, t_cursor *c)
{
	unsigned char	num;
	unsigned char	t_reg;
	unsigned int	arg2;

	num = g->map[c->index + 1].byte;
	t_reg = g->map[c->index + 2].byte;
	if (num == 80)
	{
		arg2 = g->map[c->index + 3].byte;
		c->registr[arg2] = t_reg;
	}
	else if (num == 112)
	{
		arg2 %= IDX_MOD;
		g->map[c->index +arg2].byte = t_reg;
	}
}
