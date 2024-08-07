# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:05:56 by aaitelka          #+#    #+#              #
#    Updated: 2024/08/07 11:04:17 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := philo
INCLUDE := include/
CC      := cc -pthread -fsanitize=thread
CFLAGS  := -g -I$(INCLUDE) -Wall -Werror -Wextra 

SRCS    := $(shell find . -type f -name "*.c")

OBJS_DIR        = build/
OBJS            = $(patsubst %.c,$(OBJS_DIR)%.o,$(SRCS))

all: $(NAME)

$(OBJS_DIR)%.o: %.c $(INCLUDE)philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
