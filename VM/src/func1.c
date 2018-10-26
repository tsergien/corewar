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
		map[(ind + i) % MEM_SIZE].byte = csrc[size - 1 - i];
}

void		from_map(void *dst, t_field *map, size_t size, unsigned ind)
{
	unsigned int	i;
	unsigned char	*cdst;

	i = -1;
	cdst = (unsigned char *)dst;
	while (++i < size)
		cdst[size - i - 1] = map[(ind + i) % MEM_SIZE].byte;
}

int			live(t_game *g, t_cursor *c)
{
	char	name;
	int		i;

	i = -1;
	name = g->map[c->index + 4].byte;
	c->alive = 1;
	if (!g->flags.v)
		ft_printf("A process shows that player %d %S is alive",
	c->parent_ind + 1, g->champ[(int)c->parent_ind].prog_name);
	while (++i < g->champs_num)
		if (15 - name == i)
		{
			g->champ[i].current_lives += 1;
			g->champ[i].last_live = g->cycle;
		}
	return (5);
}

int			ld(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	args = (unsigned int *)malloc(sizeof(unsigned int) * 2);
	cod = get_codage(g->map[c->index + 1].byte & 252);
	offset = get_args(g->map, c, args, 2);
	if (cod[1] == REG_CODE && (cod[0] == DIR_CODE || cod[0] == IND_CODE))
	{
		if (cod[0] == IND_CODE)
		{
			args[0] = args[0] % IDX_MOD;
			from_map(c->registr + args[1], g->map, 4, c->index + args[0]);
		}
		else if (cod[0] == DIR_CODE)
			c->registr[args[1]] = args[0];
	}
	c->carry = (c->registr[args[1]] == 0) ? 1 : 0;
	free(args);
	free(cod);
	return (offset + 2);
}

int			st(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	args = (unsigned int *)malloc(sizeof(unsigned int) * 2);
	cod = get_codage(g->map[c->index + 1].byte & 252);
	offset = get_args(g->map, c, args, 2);
	if (cod[1] == REG_CODE)
	{
		args[1]= g->map[c->index + 3].byte;
		c->registr[args[1]] = args[0];
	}
	else if (cod[1] == IND_CODE)
	{
		args[1] %= IDX_MOD;
		g->map[c->index + args[1]].byte = (char)args[0];
	}
	free(args);
	free(cod);
	return (offset + 2);
}
