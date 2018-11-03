/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:41:29 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/10/30 16:44:54 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

// void parse_name1(t_asm * ass, char *line)
// {
//     char *buf = NULL;
//     char *tmp = NULL;
//     int i = 0;

//     buf = ft_strjoin(buf, line);
//     tmp = buf;
//     while (get_next_line(ass->fd, &line))
//     {
//         while (line[i] && line[i] != '"'){i++;};
//         if (!line[i])
//         {
//             ft_printf("%s", line[i]);
//             buf = ft_strjoin(tmp, line);
//             free(tmp);
//             tmp = buf;
//         }
//         else
//         {
//             line[i] = 0;
//             i++;
//             if (!line[i])
//             {
//                 buf = ft_strjoin(tmp, line);
//                 free(tmp);
//                 tmp = buf;
//             }
//             else
//             {
//                 while (line[i] == ' ' || line[i] == '\t') i++;
//                 if (line[i] && line[i] != '#')
//                     break;
//                 buf = ft_strjoin(tmp, line);
//                 free(tmp);
//                 tmp = buf;
//             }
//             if (ft_strlen(buf) > PROG_NAME_LENGTH)
//                 ft_printf("more than v buffer vlize, idiot");
//             else
//                 ft_strcpy(ass->header.prog_name, buf);
//             //free(buf);
//             return ;
//         }
//     }
//     //ft_printf("%s", buf);
//     ft_printf("1");
//     exit (0);
// }

// void parse_header1(t_asm * ass)
// {
//     char *line;
//     int i = 0;
//     int j = 0;
//     while (get_next_line(ass->fd, &line) > 0)
//     {
//         j++;
//         if (*line == '\0')
//             continue;
//         while (line[i])
//         {
//             while (line[i] == ' ' || line[i] == '\t') i++;
//             if (line[i] == '.')
//             {
//                 if (!ft_strncmp(line + i, NAME_CMD_STRING, 5))
//                 {
//                     i = i + 5;
//                     while (line[i] == ' ' || line[i] == '\t') i++;
//                     if (line[i++] == '"')
//                         parse_name(ass, line + i);
//                     else
//                     {
//                         ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE", j, i);
//                         exit (0);
//                     }
//                     return ;
//                 } 
//                 else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
//                 {

//                 }    
//                 else
//                 {
//                     ft_printf("3");
//                     exit (0);
//                 }
//             }
//             else if (line[i] == '#')
//             {

//             }
//             else
//             {
//                 ft_printf("1Tu sho dibil cuka ili sho?");
//                 return ;
//             }
//             i++;
//         }
//         free(line);
//     }
//     ft_printf("%s", line);
//     free(line);
// }

int check_line(char **line, int line_number)
{
    char *temp = *line;

    while (**line == '\t' || **line == ' ')
        (*line)++;
    if (**line == '\0' || **line == COMMENT_CHAR || **line == ';')
        return 0;
    else if (**line == '.')
        if (!ft_strncmp(*line, NAME_CMD_STRING, 5) || !ft_strncmp(*line, COMMENT_CMD_STRING, 8)) 
            return (1);
    if (**line == '"')
        syntax_error_string(temp, *line, line_number);
    else if (if_consist("±§!@$%^&*.()+_-=/\\][`{}'<>", **line))
        lexical_error(temp, *line, line_number);
    else if (**line == ',')
        syntax_error_separator(temp, *line, line_number);
    else if (**line == ':')
        syntax_error_indirect_label(temp, *line, line_number);
    else
        syntax_error_instruction(temp, *line, line_number);
    return 0;
}

int fillbuf(char *buf, t_asm *ass, char **line, int size)
{
    int i = 0;
    (*line)++;
    while (i < size)
    {
        if (!**line)
        {
            if (get_next_line(ass->fd, line) == 0)
                return 0;
            ass->line_number++;
            buf[i++] = '\n';
            //free(line); 
        }
        if (**line == '\0')
            continue ;
        if (**line == '\"')
        {
            while (**line)
            {
                (*line)++;
                if (**line == ' ' || **line == '\t')
                    continue;
                else if (**line == '#' || **line == ';')
                    break;
                else
                    return 1;
            }
            break ;
        }
        buf[i++] = *((*line)++);
    }
    if (i == size)
    {
        ft_printf("[Error handled] %s is too big.\n", size == PROG_NAME_LENGTH ? "Name" : "Comment");
        exit(0);
    }
    if (size == PROG_NAME_LENGTH)
        ass->header.name_exist = 1;
    else
        ass->header.comment_exist = 1;  
    return 0;
}

void parse_dot(t_asm * ass, char *line, char* begin_line)
{
    int i = 2;

    if (!ft_strncmp(line, NAME_CMD_STRING, 5))
    {
        line += 5;
        i = 1;
    }    
    else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
        line += 8;
    while(*line == '\t' || *line == ' ')
        line++;
    if (*line == '"')
    {
        if (i == 1)
        {
            if (ass->header.name_exist)
                syntax_error_double_command(PROG_NAME_LENGTH, begin_line, begin_line, ass->line_number);
            if (fillbuf(ass->header.prog_name, ass, &line, PROG_NAME_LENGTH))
                syntax_error_instruction(begin_line, line, ass->line_number);
        } 
        else
        {
            if (ass->header.comment_exist)
                syntax_error_double_command(COMMENT_LENGTH, begin_line, begin_line, ass->line_number);
            if (fillbuf(ass->header.comment, ass, &line, COMMENT_LENGTH))
                syntax_error_instruction(begin_line, line, ass->line_number);
        } 
                    
    }
    else
        syntax_error_instruction(begin_line, line, ass->line_number);
}

void parse_header(t_asm * ass)
{
    char *line;
    char *to_free;
    //int i = 0;
    ass->line_number = 0;
    while (get_next_line(ass->fd, &to_free) > 0)
    {
        ass->line_number++;
        line = to_free;
        if (*line == '\0')
            continue ;
        if (check_line(&line, ass->line_number))
            parse_dot(ass, line, to_free);
        free(to_free);
    }
}