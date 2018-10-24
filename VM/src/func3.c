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

//void		from_map(void *dst, t_field *map, size_t size, unsigned ind)
void		zjmp(t_game *g, t_cursor *c)
{
	short int		t_dir;

	if (c->carry)
	{
		from_map(&t_dir, g->map, 2, c->index + 1);
		c->index = t_dir % IDX_MOD;
	} 
}

void		ldi(t_game *g, t_cursor *c)
{
	unsigned int	num;

	num = g->map[c->index + 1].byte;
	if ()
}

void		sti(t_game *g, t_cursor *c)
{

}