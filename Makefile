# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arodgers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 15:04:46 by arodgers          #+#    #+#              #
#    Updated: 2024/05/18 18:56:28 by arodgers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     = cc
CFLAGS = -Wall -Werror -Wextra

HDR    = philo.h
NAME   = philo
SRCS   = philo.c parse.c init.c clean_utils.c dinner.c getters_and_setters.c chrono_utils.c checks.c utils.c

OBJS   = $(SRCS:.c=.o)

RM     = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HDR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
