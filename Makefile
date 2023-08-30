# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 14:08:18 by yuboktae          #+#    #+#              #
#    Updated: 2023/08/30 17:21:36 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR 	=	includes/
LIBFT_PATH	=	libft/
READLINE_LIB	=	-lreadline -lhistory -L/usr/local/lib

SRC_FILES	=	main/minishell.c main/main.c init/init_all.c lexer/get_env.c\
				lexer/check_line.c lexer/check_quotes.c lexer/count_tokens.c \
				lexer/create_tokens.c lexer/expand_token.c lexer/lex_analyse.c \
				parser/add_parse_node.c parser/build_parse.c parser/parse_analyse.c \
				execution/cmd_path.c execution/path_utils.c execution/one_cmd_exec.c \
				execution/ft_split_ignore_spaces.c builtins/echo.c builtins/cd.c \
				builtins/pwd.c builtins/export.c builtins/unset.c builtins/env.c \
				builtins/exit.c errors/ft_errors.c destructor/free_parsing.c \
				destructor/free_env.c utils/utils.c	utils/env_utils.c utils/parse_utils.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
DEP			=	$(OBJ:.o=.d)

CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3
CPPFLAGS	=	-I/usr/local/include -I$(LIBFT_PATH) -I$(INC_DIR) 
LIBFT		=	$(LIBFT_PATH)/libft.a

all:	 $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) all

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(READLINE_LIB) -o $@ $(OBJ) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -o $@ -c $<
	
-include $(DEP)

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME) $(LIBFT)

re: fclean all 

.PHONY: all clean fclean re