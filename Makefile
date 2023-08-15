# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 14:08:18 by yuboktae          #+#    #+#              #
#    Updated: 2023/08/15 14:17:07 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR 	=	includes/
LIBFT_PATH	=	libft/
READLINE_LIB	=	-lreadline -lhistory -L/usr/local/lib


SRC_FILES	=	env/path.c parsing/check_line.c parsing/check_quotes.c parsing/split_quotes.c \
				parsing/build_parse.c parsing/create_tokens.c builtins/echo.c builtins/cd.c builtins/pwd.c\
				builtins/export.c builtins/unset.c builtins/env.c builtins/exit.c errors/ft_errors.c \
				main.c utils.c \
				

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
	$(MAKE) -C $(LIBFT_PATH)
	ar rcs $(LIBFT)

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