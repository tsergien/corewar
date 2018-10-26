/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:40:11 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/23 12:40:24 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

int			add(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] == REG_CODE && cod[1] == REG_CODE && cod[2] == REG_CODE)
	{
		c->registr[args[2]] = c->registr[args[0]] + c->registr[args[1]];
		c->carry = (!g->map[c->index + 3].byte) ? 1 : 0;
	}
	free(args);
	free(cod);
	return (offset + 2);
}

int			sub(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] == REG_CODE && cod[1] == REG_CODE && cod[2] == REG_CODE)
	{
		c->registr[args[2]] = c->registr[args[0]] - c->registr[args[1]];
		c->carry = (!g->map[c->index + 3].byte) ? 1 : 0;
	}
	free(args);
	free(cod);
	return (offset + 2);
}

int			zjmp(t_game *g, t_cursor *c)
{
	short int		t_dir;
	
	if (c->carry)
	{
		from_map(&t_dir, g->map, 2, c->index + 1);
		c->index += t_dir % IDX_MOD;
	}
	return (3);
}

int			ldi(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != 0 && cod[1] != IND_CODE && cod[1] != 0 && cod[2] == REG_CODE)
	{
		if (cod[0] == IND_CODE)
			from_map(&args[0], g->map, 4, args[0] % IDX_MOD + c->index); 
		from_map(c->registr + args[2], g->map, 4, (args[0] + args[1]) % IDX_MOD + c->index);
	}
	free(args);
	free(cod);
	return (offset + 2);
}

int			sti(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != REG_CODE && cod[1] != 0 && cod[2] == IND_CODE && cod[2] != 0)
	{
		if (cod[1] == IND_CODE)
			from_map(args + 1, g->map, 4, args[1] % IDX_MOD);
		g->map[c->index + (args[1] + args[2]) % IDX_MOD].byte = (char)args[0];
	}
	free(args);
	free(cod);
	return (offset + 2);
}