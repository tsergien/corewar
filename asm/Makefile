# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaslyan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 11:19:00 by tmaslyan          #+#    #+#              #
#    Updated: 2018/10/30 11:19:39 by tmaslyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = asm

SRC_FILES =  main.c op.c parse_header.c errors.c parse_commands.c count_all.c \
			some_functions_xd.c write_file.c bonus.c  check_functions.c \
			push_functions.c get_functions.c 

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

HEADER = includes/
LIB_DIR = ./libft/

WWW = -Wall -Wextra -Werror

RED = \x1b[38;5;196m
BLUE = \x1b[38;5;117m
RESET_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR)
	@gcc -lncurses  $(OBJ) -o $(NAME) -I $(HEADER) -L $(LIB_DIR) -lft
	@echo "$(BLUE)***		$(NAME) compiled		***$(RESET_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc -g $(WWW) -c -o $@ $<
	
clean:
	@make clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)***		obj cleaned		***$(RESET_COLOR)"

fclean: clean
	@make fclean -C $(LIB_DIR)
	@rm -f $(NAME)
	@echo "$(RED)***		$(NAME) deleted		***$(RESET_COLOR)"

norm:
	@norminette $(SRC) $(HEADER)*.h

re: fclean all
