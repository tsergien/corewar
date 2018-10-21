/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'# '
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	unsigned char	filled;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	last_live;
	unsigned int	current_lives;
}					t_header;

typedef struct		s_op
{
	char			*name;
	char			args_amount;
	int				args[3];
	char			opcode;
	int				cycles;
	char			*description;
	char			codage_octal;
	char			carry;
}					t_op;

typedef struct		s_field
{
	unsigned char	byte;
	unsigned char	champ;
}					t_field;

typedef struct		s_flags
{
	char			v;
	char			n;
	int				nbr_cycles;
}					t_flags;

typedef struct		s_game
{
	t_field			map[MEM_SIZE];
	unsigned char	champs_num;
	t_header		champ[4];
	unsigned char	pause;
	int				cycles_limit;
	unsigned long	processes;
	unsigned int	cycle;
	t_flags			flags;
}					t_game;

#endif
