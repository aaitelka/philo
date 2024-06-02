# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:05:56 by aaitelka          #+#    #+#              #
#    Updated: 2024/06/01 18:55:42 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
HEAD	:= include/philo.h

CC		:= cc -g2 -pthread
CFLAGS	:= #-Wall -Werror -Wextra

SRCS	:= main.c

OBJS	:= $(SRCS:%c=%o)

all		: $(NAME)

%o		: %c $(HEAD)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

clean	:
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re		: fclean all

.PHONY	: clean
