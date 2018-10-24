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
char			is_alives(t_cursor *c);
void			add_cursor(int champ_ind, t_game *g);
void			to_map(t_field *map, void *src, size_t size, unsigned ind);
void			from_map(void *dst, t_field *map, size_t size, unsigned ind);


/*
** FUNCTIONS
*/
void			live(t_game *g, t_cursor *c);
void			ld(t_game *g, t_cursor *c);
void			st(t_game *g, t_cursor *c);
void			add(t_game *g, t_cursor *c);
void			sub(t_game *g, t_cursor *c);
void			and_(t_game *g, t_cursor *c);
void			or_(t_game *g, t_cursor *c);
void			xor_(t_game *g, t_cursor *c);
void			zjmp(t_game *g, t_cursor *c);
void			ldi(t_game *g, t_cursor *c);
void			sti(t_game *g, t_cursor *c);



#endif
