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

int check_line(char **line, int j)
{
    char *temp = *line;

    while (**line == '\t' || **line == '\r' || **line == ' ')
        (*line)++;
    if (**line == '\0' || **line == COMMENT_CHAR || **line == ';')
        return 0;
    else if (**line == '.')
        if (!ft_strncmp(*line, NAME_CMD_STRING, 5) || !ft_strncmp(*line, COMMENT_CMD_STRING, 8)) 
            return (1);
    if (**line == '"')
        syntax_error_string(temp, *line, j);
    else if (if_consist("±§!@$%^&*.()+_-=/\\][`{}'<>", **line))
        lexical_error(temp, *line, j);
    else if (**line == ',')
        syntax_error_separator(temp, *line, j);
    else if (**line == ':')
        syntax_error_indirect_label(temp, *line, j);
    else
        syntax_error_instruction(temp, *line, j);
    return 0;
}

void fillbuf(char *buf, t_asm *ass, char *line)
{
    int i = 0;
    while (i < PROG_NAME_LENGTH)
    {
        if (!*line)
        {
            if (get_next_line(ass->fd, &line) <= 0)
            {
                ft_printf("Syntax error at token [TOKEN] END \"(null)\"\n");
                exit(0);
            }
            buf[i++] = '\n';
            //free(line); 
        }
        if (*line == '\0')
            continue ;
        if (*line == '\"')
            break ;
        buf[i++] = *line++;
    }
    if (*line != '\"')
        ft_printf("[Error handled] Name is too big.\n");
}

void parse_dot(t_asm * ass, char *line, int j)
{
    char *temp = line;
    int i = 2;

    if (!ft_strncmp(line, NAME_CMD_STRING, 5))
    {
        line += 5;
        i = 1;
    }    
    else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
        line += 8;
    while(*line == '\t' || *line == '\r' || *line == ' ')
        line++;
    if (*line == '"')
    {
        if (i == 1)
            fillbuf(ass->header.prog_name, ass, line + 1);
        else 
            fillbuf(ass->header.comment, ass, line + 1);        
    }
    else
        syntax_error_instruction(temp, line, j);
}

void parse_header(t_asm * ass)
{
    char *line;
    char *to_free;
    //int i = 0;
    int j = 0;

    while (get_next_line(ass->fd, &to_free) > 0)
    {
        j++;
        line = to_free;
        if (*line == '\0')
            continue ;
        if (check_line(&line, j))
            parse_dot(ass, line, j);
        free(to_free);
    }
}