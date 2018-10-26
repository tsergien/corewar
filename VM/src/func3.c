/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:40:35 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/23 12:40:36 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

int				fork_(t_game *g, t_cursor *c)
{
	short int	t_dir;
	t_cursor	*temp;
	
	from_map(&t_dir, g->map, 2, c->index + 1);
	add_cursor(c->parent_ind, g);
	temp = g->cursor;
	while (temp->next)
		temp = temp->next;
	temp->carry = c->carry;
	temp->parent_ind = c->parent_ind;
	ft_memcpy(c->registr, temp->registr, 64);
	temp->alive = c->alive;
	temp->command = c->command;
	temp->cycles_to_exec = c->cycles_to_exec;
	temp->index = c->index + t_dir % IDX_MOD;
	return (3);
}

int				lld(t_game *g, t_cursor *c)
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
			from_map(c->registr + args[1], g->map, 4, c->index + args[0]);
		else if (cod[0] == DIR_CODE)
			c->registr[args[1]] = args[0];
	}
	c->carry = (c->registr[args[1]] == 0) ? 1 : 0;
	free(args);
	free(cod);
	return (offset + 2);
}
						
int				lldi(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	cod = get_codage(g->map[c->index + 1].byte & 252);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != 0 && (cod[1] == REG_CODE || cod[1] == DIR_CODE) && cod[2] == T_REG)
	{
		if (cod[0] == IND_CODE)
			from_map(&args[0], g->map, 4, args[0] % IDX_MOD + c->index); 
		from_map(c->registr + args[2], g->map, 4, (args[0] + args[1]) + c->index);
	}
	c->carry = (c->registr[args[1]] == 0) ? 1 : 0;
	free(args);
	free(cod);
	return (offset + 2);
}

int				lfork(t_game *g, t_cursor *c)
{
	short int	t_dir;
	t_cursor	*temp;
	
	from_map(&t_dir, g->map, 2, c->index + 1);
	add_cursor(c->parent_ind, g);
	temp = g->cursor;
	while (temp->next)
		temp = temp->next;
	temp->carry = c->carry;
	temp->parent_ind = c->parent_ind;
	ft_memcpy(c->registr, temp->registr, 64);
	temp->alive = c->alive;
	temp->command = c->command;
	temp->cycles_to_exec = c->cycles_to_exec;
	temp->index = c->index + t_dir;
	return (3);
}

int				aff(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	args = (unsigned int *)malloc(sizeof(unsigned int) * 1);
	cod = get_codage(g->map[c->index + 1].byte & 252);
	offset = get_args(g->map, c, args, 1);
	if (cod[0] == REG_CODE && g->flags.v == 0)
		ft_printf("%c", args[0] % 256);
	free(args);
	free(cod);
	return (offset + 2);
}
