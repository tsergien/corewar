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
    ass.cmd_lst = NULL;
    if (argc == 1){ft_printf("no file idiot"); return 0;};
    ass.fd = open(argv[argc - 1], O_RDONLY);
    parse_header(&ass);
    parse_commands(&ass);
    ft_printf("%s\n", ass.header.prog_name);
    ft_printf("%s\n", ass.header.comment);
    t_labels *temp = ass.cmd_lst->label;
    while(temp)
    {
        ft_printf("%s\n", temp->label);
        temp = temp->next;
    }

    //system("leaks asm");
    return 0;
}