# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:45:57 by yuboktae          #+#    #+#              #
#    Updated: 2023/08/21 23:56:06 by yuliaboktae      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=		ft_isalpha.c \
	  			ft_isdigit.c \
	  			ft_isalnum.c \
	  			ft_isascii.c \
	  			ft_isprint.c \
	  			ft_strlen.c \
	  			ft_memset.c \
	  			ft_bzero.c \
	  			ft_memcpy.c \
	  			ft_memmove.c \
				ft_strcpy.c \
	  			ft_strlcpy.c \
	  			ft_strlcat.c \
	  			ft_toupper.c \
	  			ft_tolower.c \
	  			ft_strchr.c \
	  			ft_strrchr.c \
				ft_strcmp.c \
	  			ft_strncmp.c \
	  			ft_memchr.c \
	  			ft_memcmp.c \
	  			ft_strnstr.c \
	  			ft_atoi.c \
	  			ft_calloc.c \
	  			ft_strdup.c \
	  			ft_substr.c \
	  			ft_strjoin.c \
	  			ft_strtrim.c \
	  			ft_split.c \
	  			ft_itoa.c \
	  			ft_strmapi.c \
	  			ft_striteri.c \
	  			ft_putchar_fd.c \
	  			ft_putstr_fd.c \
				ft_putendl_fd.c \
	  			ft_putnbr_fd.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				printf/ft_printf.c \
				printf/ft_printbase.c \
				printf/ft_putstr.c \
				printf/ft_putchar.c \
				printf/ft_putnbr.c \
				printf/ft_unsign.c \
				printf/ft_upperhex.c \
				printf/ft_lowerhex.c \
				printf/ft_point.c \
				

SRC_BONUS	=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \


OBJ		=	${SRC:%.c=%.o}

OBJ_BONUS	=	${SRC_BONUS:%.c=%.o}

HEADER		=	libft.h

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

all:	$(NAME)

%.o: %.c $(HEADER)
		@$(CC) -c $(CFLAGS) -o $@ $<
		
$(NAME): $(OBJ) $(OBJ_BONUS)
		@ar rc $(NAME) $^

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re

