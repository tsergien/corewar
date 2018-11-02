/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:37:44 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/10/30 12:37:47 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../includes/op.h"

int main(int argc, char **argv)
{
    t_asm ass;

    if (argc == 1)
        return 0;
    ass.fd = open(argv[argc - 1], O_RDONLY);
    parse_header(&ass);
    return 0;
}