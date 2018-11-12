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

char *get_error_line_address(int i, int j, char **argv, char *line)
{
    int k;
    int l;
    int count;

    k = 0;
    count = 0;
    while (argv[k])
    {
        l = 0;
        while (argv[k][l])
        {
            if (k == i && j == l)
            {
               return  (line + count);
            }
            l++;
            count++;
        }
        k++;
        count++;
    }
    return  (line + count);
}

void push_command(t_asm *ass, t_command *c_temp, int index, char *line)
{
    char **args;
    int i;
    int j;
    c_temp->opcode = g_op_tab[index].opcode;


    i = 0;
    while (line[i])
    {
        if (line[i] == COMMENT_CHAR || line[i] == ';')
        {
            line[i] = 0;
            break;
        }
        i++;
    }
    check_valid_separator(ass, line, index);
    if (*line == COMMENT_CHAR || *line == ';')
    {
        *line = 0;
        syntax_error(ass->begin_line, line, ass->line_number, "ENDLINE");
    }
    //ft_printf("%s\n", line);
    args = ft_strsplit(line, SEPARATOR_CHAR);
    if (args[0][0] != ' ' && args[0][0] != '\t' && args[0][0] !=  '%')
        syntax_error(ass->begin_line, line, ass->line_number, "INSTRUCTION");
    i = 0;
    j = 0;
    while (args[i])
    {
        j = 0;
        while (args[i][j]) {
            while (args[i][j] == ' ' || args[i][j] == '\t')
                j++;
            if (args[i][j] != '%' && args[i][j] != '-' && !ft_isdigit(args[i][j]) && args[i][j] != 'r' && args[i][j] != ':')
                syntax_error(ass->begin_line, get_error_line_address(i, j, args, line), ass->line_number, "INSTRUCTION");
            if (g_op_tab[index].args[i] & T_REG)
            {
                if (args[i][j] == 'r') {
                    j++;
                    if (args[i][j] == '-' || ft_isdigit(args[i][j]))
                    {
                       c_temp->args[i].num_value = ft_atoi(args[i] + j);
                       c_temp->args[i].str_value = NULL;
                       c_temp->args[i].size_of_arg = 1;
                    }
                    else
                     syntax_error(ass->begin_line, get_error_line_address(i, j, args, line), ass->line_number, "INSTRUCTION");
                }
            }
            if (g_op_tab[index].args[i] & T_DIR)
            {
                if (args[i][j] == '%') {
                    j++;
                    if (args[i][j] == ':')
                    {
                        char *temp = ft_strdup(args[i] + j);
                        int k = 0;
                        while (temp[k] && temp[k] != ' ' && temp[k] != '\t')
                            k++;
                        temp[k] = 0;
                        c_temp->args[i].num_value = 0;
                        c_temp->args[i].str_value = ft_strdup(temp);
                        c_temp->args[i].size_of_arg = g_op_tab[index].label_size;
                        free(temp);
                    }
                    else if (args[i][j] == '-' || ft_isdigit(args[i][j]))
                    {
                        c_temp->args[i].num_value = ft_atoi(args[i] + j);
                        c_temp->args[i].size_of_arg = g_op_tab[index].label_size;
                        c_temp->args[i].str_value = NULL;
                    }
                    else
                        syntax_error(ass->begin_line, get_error_line_address(i, j, args, line), ass->line_number, "INSTRUCTION");
                }
            }
            if (g_op_tab[index].args[i] & T_IND)
            {
                if (args[i][j] == ':')
                {
                    char *temp = ft_strdup(args[i] + j);
                    int k = 0;
                    while (temp[k] && temp[k] != ' ' && temp[k] != '\t')
                        k++;
                    temp[k] = 0;
                    c_temp->args[i].num_value = 0;
                    c_temp->args[i].str_value = ft_strdup(temp);
                    c_temp->args[i].size_of_arg = g_op_tab[index].label_size;
                    free(temp);
                }
                else if (ft_isdigit(args[i][j]) || args[i][j] == '-') {
                    c_temp->args[i].num_value = ft_atoi(args[i] + j);
                    c_temp->args[i].size_of_arg = 2;
                    c_temp->args[i].str_value = NULL;
                }
                else
                    syntax_error(ass->begin_line, get_error_line_address(i, j, args, line), ass->line_number, "INSTRUCTION");
            }
            if (c_temp->args[i].str_value == NULL)
                j += len_int(c_temp->args[i].num_value);
            else
                j += ft_strlen(c_temp->args[i].str_value);
            while (args[i][j])
            {
                if (args[i][j] != ' ' && args[i][j] != '\t')
                    syntax_error(ass->begin_line, get_error_line_address(i, j, args, line), ass->line_number, "INSTRUCTION");
                j++;
            }
        }
        i++;
    }
    if (i != g_op_tab[index].args_amount)
    {
        ft_printf("[Error] Line: %d. Invalid number of arguments", ass->line_number);
        exit (0);
    }
}

void check_command(t_asm *ass, t_command *c_temp, char *line)
{
    char *temp;
    int i;

    if (!*line || *line == COMMENT_CHAR || *line == ';')
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
            return;
        }
        i++;
    }
    lexical_error(ass->begin_line, line, ass->line_number);
}

void push_lable(t_asm *ass, char *line)
{
    t_command *c_temp;
    t_labels *l_temp;

    c_temp = get_cmd_list(ass);
    l_temp = get_label_list(c_temp);
    l_temp->label = ft_strdup(line);
    //ft_printf("%d\n", (int)(*(line + ft_strlen(l_temp->label) + 1)));
    line = line + ft_strlen(l_temp->label) + 1;
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    if (*(line + ft_strlen(l_temp->label) + 1))
        check_command(ass, c_temp, line);
}

void check_lable(t_asm *ass, char *line)
{
    char *temp;

    if (!*line || *line == COMMENT_CHAR || *line == ';')
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

void check_last_line(int i, char *buf)
{
    i = 0;
    while (buf[i])
    {
        if (buf[i] == '\n') {
            ft_printf("it's ok");
            return;
        }
        i++;
    }
    i = 0;
    while (buf[i])
    {
        if (buf[i] == COMMENT_CHAR || buf[i] == ';')
            break;
        else if (buf[i] != '\t' && buf[i] != ' ') {
            ft_printf("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?");
            return;
        }
        i++;
    }
    ft_printf("it's ok");
}

void parse_commands(t_asm *ass)
{
    char *line;
    int i = 0;

    while (get_next_line(ass->fd, &ass->begin_line) > 0)
    {
        line = ass->begin_line;
        ass->last_line_size = ft_strlen(ass->begin_line);
        ass->line_number++;
        if (!*line)
            continue;
        while(*line == ' ' || *line == '\t')
            line++;
        check_lable(ass, line);
        free(ass->begin_line);
    }
    line = (char *)malloc(ass->last_line_size + 2);
    lseek(ass->fd, -ass->last_line_size, SEEK_CUR);
    ft_bzero(line, ass->last_line_size + 2);
    read(ass->fd, line, ass->last_line_size + 2);
    if (ass->last_line_size == 0)
        ass->line_number++;
    if(!ass->cmd_lst)
        syntax_error(line, line + ft_strlen(line), ass->line_number, "END");
    check_last_line(i, line);
    free(line);
}