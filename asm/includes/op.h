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

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#include <fcntl.h>
#include "../libft/include/libft.h"

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				name_exist;
	char				comment_exist;
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_labels
{
	char *label;
	struct s_labels *next;
}					t_labels;


typedef struct		s_op
{
	const char		*name;
	char			args_amount;
	int				args[3];
	char			opcode;
	char			codage;
	int				label_size;
}					t_op;

typedef struct		s_arg
{
	long long int	num_value;
	char			*str_value;
	int				size_of_arg;
}					t_arg;

typedef struct		s_command
{
	t_arg		args[3];
	char			opcode;
	int				size_to_this_command;
	int				size_of_this_command;
	struct s_labels	*label;
	struct s_command *next;
}					t_command;


typedef struct		s_asm
{
	t_header header;
	char *begin_line;
	int line_number;
	int fd;
	int last_line_size;
	struct s_command *cmd_lst;
}					t_asm;

extern t_op g_op_tab[16];

void parse_header(t_asm * ass);
void lexical_error(char *start, char *line, int line_number);
void syntax_error_separator(char *start, char *line, int line_number);
void syntax_error(char *start, char *line, int line_number, char *type);
void syntax_error_string(char *start, char *line, int line_number);
void syntax_error_double_command(int size, char *start, char *line, int line_number);
void parse_commands(t_asm *ass);