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
# define VM_COREWAR_H
# include "../../libft/libft.h"
# include "op.h"
# include <ncurses.h>

void			ft_error(char *str);
void			get_champ(t_game *g, int fd, int ind);
void			show_field(t_game *g);
void			ft_error(char *str);
void			usage(void);
void			print_panel(t_game *g, WINDOW *win);
void			start_game(t_game *g);

#endif
