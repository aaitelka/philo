# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:05:56 by aaitelka          #+#    #+#              #
#    Updated: 2024/07/14 20:15:46 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
HEAD	:= include/philo.h

CC		:= cc -pthread -fsanitize=thread
CFLAGS	:= -g  #-Wall -Werror -Wextra 

SRCS	:= main.c

OBJS	:= $(SRCS:%c=%o)
.PHONY: all
all		: $(NAME)

%o		: %c $(HEAD)
		$(CC) $(CFLAGS) -c $< -o $@
.PHONY: $(NAME)
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

clean	:
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re		: fclean all

.PHONY	: clean
