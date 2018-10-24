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

void		add(t_game *g, t_cursor *c)
{
	c->registr[g->map[c->index + 3].byte] = g->map[c->index + 1].byte + g->map[c->index + 2].byte;
	if (!g->map[c->index + 3].byte)
		c->carry = 1;
	else
		c->carry = 0;
}

void		sub(t_game *g, t_cursor *c)
{
	c->registr[g->map[c->index + 3].byte] = g->map[c->index + 1].byte - g->map[c->index + 2].byte;
	if (!g->map[c->index + 3].byte)
		c->carry = 1;
	else
		c->carry = 0;
}
