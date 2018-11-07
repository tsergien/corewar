/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

t_op    g_op_tab[16] =
{
	{"lfork", 1, {T_DIR}, 15, 0, 2},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},
	{"live", 1, {T_DIR}, 1, 0, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"fork", 1, {T_DIR}, 12, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 4},
	{"aff", 1, {T_REG}, 16, 1, 4},
};
