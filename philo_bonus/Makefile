# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 19:07:44 by aaitelka          #+#    #+#              #
#    Updated: 2024/08/28 16:21:11 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := philo_bonus
INCLUDE  := include/
CC       := cc -pthread
CFLAGS   := -I$(INCLUDE) #-Wall -Werror -Wextra 

SRCS     := $(shell find . -type f -name "*_bonus.c")

OBJS_DIR = build/
OBJS     = $(patsubst %.c,$(OBJS_DIR)%.o,$(SRCS))

all: $(NAME)

$(OBJS_DIR)%.o: %.c $(INCLUDE)philo_bonus.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
