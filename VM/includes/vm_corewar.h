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

char			*get_codage(unsigned int codage);
int				get_args(t_field *map, t_cursor *c, unsigned int *args, int args_num);

/*
** FUNCTIONS
*/
int				live(t_game *g, t_cursor *c);
int				ld(t_game *g, t_cursor *c);
int				st(t_game *g, t_cursor *c);
int				add(t_game *g, t_cursor *c);
int				sub(t_game *g, t_cursor *c);
int				and_(t_game *g, t_cursor *c);
int				or_(t_game *g, t_cursor *c);
int				xor_(t_game *g, t_cursor *c);
int				zjmp(t_game *g, t_cursor *c);
int				ldi(t_game *g, t_cursor *c);
int				sti(t_game *g, t_cursor *c);



#endif
