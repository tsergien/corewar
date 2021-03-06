/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 12:42:22 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/02 12:42:24 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		consist(const char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}
