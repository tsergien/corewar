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

void	flags(char **argv, t_asm *ass, int argc)
{
	ft_bzero(ass->header.comment, COMMENT_LENGTH);
	ft_bzero(ass->header.prog_name, PROG_NAME_LENGTH);
	ass->cmd_lst = NULL;
	ass->binary_name = ft_strdup(argv[argc - 1]);
	ass->header.comment_exist = 0;
	ass->header.name_exist = 0;
	ass->flags.flag_p = 0;
	ass->flags.flag_r = 0;
	while (*argv)
	{
		while (**argv)
		{
			if (ft_strequ(*argv, "-p"))
				ass->flags.flag_p = 1;
			else if (ft_strequ(*argv, "-r"))
				ass->flags.flag_r = 1;
			(*argv)++;
		}
		argv++;
	}
}

void	check_file(t_asm *ass, int argc)
{
	if (argc == 1)
	{
		ft_printf("Usage: ./asm [-pr] [file]\n");
		exit(0);
	}
	ass->fd = open(ass->binary_name, O_RDONLY);
	if (ass->fd < 0)
	{
		ft_printf("Can't read source file %s\n", ass->binary_name);
		exit(0);
	}
}

int		main(int argc, char **argv)
{
	t_asm ass;

	flags(argv, &ass, argc);
	check_file(&ass, argc);
	parse_header(&ass);
	parse_commands(&ass);
	close(ass.fd);
	count_size(&ass);
	if (ass.flags.flag_p)
		bonus_flag_info(&ass);
	else if (ass.flags.flag_r)
		ft_printf("reverse ept file nahui\n");
	else
	{
		write_file(&ass);
		ft_printf("Writing output program to %s\n", ass.binary_name);
	}
	return (0);
}
