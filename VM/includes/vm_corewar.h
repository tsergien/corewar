/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:36:45 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:36 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_COREWAR_H
#define VM_COREWAR_H

#include "op.h"

typedef struct		s_champ
{
	char			*name;
	int				size;
	char			*exec;
}					t_champ;

#endif
