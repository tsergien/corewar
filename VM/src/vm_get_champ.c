/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:40:04 by tsergien          #+#    #+#             */
/*   Updated: 2018/10/18 15:42:27 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_corewar.h"

static unsigned int	rev(int fd)
{
	unsigned int	rev;
	unsigned int	magic;
	unsigned char	*rev_mag;
	unsigned char	*rev_int;

	read(fd, &magic, 4);
	rev_mag = (unsigned char *)&magic;
	rev_int = (unsigned char *)&rev;
	rev_int[3] = rev_mag[0];
	rev_int[2] = rev_mag[1];
	rev_int[1] = rev_mag[2];
	rev_int[0] = rev_mag[3];
	return (rev);
}

static void			get_exec(t_game *g, int fd, int ind)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	temp;

	j = -1;
	i = ind * (MEM_SIZE / g->champs_num);
	while (++j <= g->champ[ind].prog_size)
	{
		read(fd, &temp, 1);
		g->map[i + j].byte = temp;
		g->map[i + j].champ = ind + 1;
	}
}

static void			get_comment(t_game *g, int fd, int ind)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned int	temp;

	i = 0;
	ft_strclr(g->champ[ind].comment);
	while (i + 4 <= COMMENT_LENGTH)
	{
		read(fd, &temp, 4);
		str = (unsigned char *)&temp;
		ft_strncpy(g->champ[ind].comment + i, (const char *)str, 4);
		i += 4;
	}
	read(fd, &temp, 4);
}

void				get_champ(t_game *g, int fd, int ind)
{
	int				i;
	unsigned char	*str;
	unsigned int	temp;

	(g->champ[ind].filled) ? ft_error("Tut uzhe est' Tanya!\n") : 0;
	g->champ[ind].filled = 1;
	if (rev(fd) != COREWAR_EXEC_MAGIC)
		ft_error("No magic header!\n");
	ft_strclr(g->champ[ind].prog_name);
	g->champ[ind].current_lives = 0;
	g->champ[ind].last_live = 0;
	i = 0;
	while (i + 4 <= PROG_NAME_LENGTH)
	{
		read(fd, &temp, 4);
		str = (unsigned char *)&temp;
		ft_strncpy(g->champ[ind].prog_name + i, (const char *)str, 4);
		i += 4;
	}
	read(fd, &temp, 4);
	g->champ[ind].prog_size = rev(fd);
	if (g->champ[ind].prog_size > CHAMP_MAX_SIZE)
		ft_error("Too big exec\n");
	get_comment(g, fd, ind);
	get_exec(g, fd, ind);
}
