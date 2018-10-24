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

char		*get_codage(unsigned int codage, char *cod)
{
	cod = (char *)malloc(sizeof(char) * 3);
	cod[0] = codage & 192;
	cod[1] = codage & 48;
	cod[1] = codage & 12;
	return (cod);
}

// # define REG_CODE				1 // 01
// # define DIR_CODE				2 // 10
// # define IND_CODE				3 // 11
void				get_args(char *cod, t_field *map, t_cursor *c, unsigned int *args)
{
	int		i;
	int		offset;
	int		c_index;

	i = -1;
	offset = 0;
	c_index = c->index + 2;// 02 90  arg1 arg2 arg3
	while (++i < 3)
	{
		if (cod[i] == REG_CODE)
		{
			args[i] = map[c_index + offset].byte;
			offset += 1;
		}
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
}

void		move_cursor(t_cursor *c, unsigned int shift)
{

}

void		and_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;

	if (!(cod = get_codage(g->map[c->index + 1].byte, cod)) ||
		cod[0] == 0 || cod[1] == 0 || cod[2] != 1)
		;//move cursor for calculated arguments
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	get_args(cod, g->map, c, args);
	c->registr[args[2]] = args[0] & args[1];
	c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
}

void		or_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;

	if (!(cod = get_codage(g->map[c->index + 1].byte, cod)) ||
		cod[0] == 0 || cod[1] == 0 || cod[2] != 1)
		;//move cursor for calculated arguments
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	get_args(cod, g->map, c, args);
	c->registr[args[2]] = args[0] | args[1];
	c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
}

void		xor_(t_game *g, t_cursor *c)
{
	unsigned int	*args;
	char			*cod;

	if (!(cod = get_codage(g->map[c->index + 1].byte, cod)) ||
		cod[0] == 0 || cod[1] == 0 || cod[2] != 1)
		;//move cursor for calculated arguments
	args = (unsigned int *)malloc(sizeof(unsigned int) * 3);
	get_args(cod, g->map, c, args);
	c->registr[args[2]] = args[0] ^ args[1];
	c->carry = (c->registr[args[2]] == 0) ? 1 : 0;
}
