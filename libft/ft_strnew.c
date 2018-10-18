/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:26:35 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/31 17:16:38 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*c;

	i = 0;
	if (!(c = (char*)malloc(size + 1)))
		return (0);
	while (i <= size)
		c[i++] = '\0';
	return (c);
}
