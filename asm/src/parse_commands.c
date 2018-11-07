/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:54:04 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/11/06 16:54:04 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

t_command *get_cmd_list(t_asm *ass)
{
    t_command *c_temp;

    if (!ass->cmd_lst)
    {
        ass->cmd_lst = (t_command *)malloc(sizeof(t_command));
        ass->cmd_lst->opcode = 0;
        ass->cmd_lst->label = NULL;
        ass->cmd_lst->next = NULL;
        c_temp = ass->cmd_lst;
    }
    else
    {
        c_temp = ass->cmd_lst;
        while (c_temp->next)
            c_temp = c_temp->next;
    }
    if (c_temp->opcode)
    {
        c_temp->next = (t_command *)malloc(sizeof(t_command));
        c_temp = c_temp->next;
        c_temp->opcode = 0;
        c_temp->label = NULL;
        c_temp->next = NULL;
    }
    return (c_temp);
}


t_labels *get_label_list(t_command *c_temp)
{
    t_labels *l_temp;

    if (!c_temp->label)
    {
        c_temp->label = (t_labels *)malloc(sizeof(t_labels));
        l_temp = c_temp->label;
    }
    else
    {
        l_temp = c_temp->label;
        while (l_temp->next)
            l_temp = l_temp->next;
        l_temp->next = (t_labels *)malloc(sizeof(t_labels));
        l_temp = l_temp->next;
    }
    l_temp->next = NULL;
    l_temp->label = NULL;
    return (l_temp);
}

void check_valid_separator(t_asm *ass, char *line, int index)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == SEPARATOR_CHAR)
        {
            i++;
            if (line[i] == SEPARATOR_CHAR)
            {
                line[i + 1] = 0;
                syntax_error(ass->begin_line, line + i, ass->line_number, "SEPARATOR");
            }
            count++;
        }
        i++;
    }
    if (g_op_tab[index].args_amount != count + 1)
    {
        ft_printf("[Error] Line: %d. Invalid number separators.\n", ass->line_number);
        exit(0);
    }
}

void push_command(t_asm *ass, t_command *c_temp, int index, char *line)
{
    char **args;
    int i;
    int j;
    c_temp->opcode = g_op_tab[index].opcode;

    check_valid_separator(ass, line, index);
    if (*line == COMMENT_CHAR)
    {
        *line = 0;
        syntax_error(ass->begin_line, line, ass->line_number, "ENDLINE");
    }
    args = ft_strsplit(line, SEPARATOR_CHAR);
    i = 0;
    while (i < g_op_tab[index].args_amount)
    {
        j = 0;
        c_temp->args[i].num_value = j + 6;
        i++;
        j++;
    }
}

void check_command(t_asm *ass, t_command *c_temp, char *line)
{
    char *temp;
    int i;

    if (!*line || *line == '#')
        return ;
    while(*line == ' ' || *line == '\t')
        line++;
    temp = line;
    i = 0;
    while (i < 16)
    {
        if (ft_strnequ(line, g_op_tab[i].name, ft_strlen(g_op_tab[i].name)))
        {
            push_command(ass, c_temp, i, line + ft_strlen(g_op_tab[i].name));
            break;
        }
        i++;
    }

}

void push_lable(t_asm *ass, char *line)
{
    t_command *c_temp;
    t_labels *l_temp;

    c_temp = get_cmd_list(ass);
    l_temp = get_label_list(c_temp);
    l_temp->label = ft_strdup(line);
    ft_printf("%d\n", (int)(*(line + ft_strlen(l_temp->label) + 1)));
    if (*(line + ft_strlen(l_temp->label) + 1))
        check_command(ass, c_temp, line + ft_strlen(l_temp->label) + 1);
}

void check_lable(t_asm *ass, char *line)
{
    char *temp;

    while(*line == ' ' || *line == '\t')
        line++;
    if (!*line || *line == '#')
        return ;
    temp = line;
    while (consist(LABEL_CHARS, *line))
        line++;
    if (*line == LABEL_CHAR)
    {
        *line++ = 0;
        push_lable(ass, temp);
    }
    else
        check_command(ass, get_cmd_list(ass), temp);
}

void parse_commands(t_asm *ass)
{
    char *line;

    while (get_next_line(ass->fd, &ass->begin_line))
    {
        line = ass->begin_line;
        ass->line_number++;
        if (*line == '\0')
            continue;
        check_lable(ass, line);
    }
}