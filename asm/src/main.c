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


#include "../includes/op.h"

int main(int argc, char **argv)
{
    t_asm ass;

    ass.header.comment_exist = 0;
    ass.header.name_exist = 0;
    if (argc == 1)
        return 0;
    ass.fd = open(argv[argc - 1], O_RDONLY);
    parse_header(&ass);
    ft_printf("%s\n", ass.header.prog_name);
    ft_printf("%s", ass.header.comment);
    return 0;
}