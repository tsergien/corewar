/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:40:40 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/23 12:40:41 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

char		*get_codage(unsigned int codage)
{
	char			*cod;

	cod = (char *)malloc(sizeof(char) * 3);
	cod[0] = codage & 192;
	cod[1] = codage & 48;
	cod[2] = codage & 12;
	return (cod);
}

int			get_args(t_field *map, t_cursor *c, unsigned int *args, int args_num)
{
	int		i;
	int		offset;
	int		c_index;
	char	*cod;

	i = -1;
	offset = 0;
	cod = get_codage(map[c->index + 1].byte);
	c_index = c->index + 2;// 02 90  arg1 arg2 arg3
	while (++i < args_num)
	{
		if (cod[i] == REG_CODE)
			args[i] = map[c_index + offset++].byte;
		else if (cod[i] == DIR_CODE)
		{
			from_map(&args[i], map, g_op_tab[c->command - 1].label, c_index + offset);
			offset += g_op_tab[c->command - 1].label;
		}
		else if (cod[i] == IND_CODE)
		{
			from_map(&args[i], map, 2, c_index + offset);
			offset += 2;
		}
	}
	return (offset);
}

int			and_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != 0 && cod[1] != 0 && cod[2] == 1)
	{
		c->registr[args[2]] = c->registr[args[0]] & c->registr[args[1]];
		c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
	}
	free(cod);
	free(args);
	return (offset);
}

int			or_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != 0 && cod[1] != 0 && cod[2] == 1)
	{
		c->registr[args[2]] = c->registr[args[0]] | c->registr[args[1]];
		c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
	}
	free(cod);
	free(args);
	return (offset);
}

int			xor_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;
	int				offset;

	cod = get_codage(g->map[c->index + 1].byte);
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	offset = get_args(g->map, c, args, 3);
	if (cod[0] != 0 && cod[1] != 0 && cod[2] == 1)
	{
		c->registr[args[2]] = c->registr[args[0]] ^ c->registr[args[1]];
		c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
	}
	free(cod);
	free(args);
	return (offset);
}
