# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 14:08:18 by yuboktae          #+#    #+#              #
#    Updated: 2023/07/21 18:44:19 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INC_DIR =	includes/

SRC_FILES	=	ft_split.c path.c parsing.c builtins.c main.c \
							

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
DEP			=	$(OBJ:.o=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -l readline
LIBFT_PATH	=	../libft
CPPFLAGS	=	-I $(INC_DIR) -I $(LIBFT_PATH)
LIBFT		=	$(LIBFT_PATH)/libft.a

all:	$(LIBFT) $(NAME) 

$(LIBFT):
	make -C $(LIBFT_PATH)
	ar rcs $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -o $@ -c $<
	
-include $(DEP)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re