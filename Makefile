# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arodgers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 14:30:18 by arodgers          #+#    #+#              #
#    Updated: 2024/04/21 17:22:12 by arodgers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     = cc
CFLAGS = -Wall -Werror -Wextra

HDR    = philo.h
NAME   = philo
SRCS   = philo.c philo_utils.c parse.c init_utils.c getters_and_setters.c synchro_utils.c chrono_utils.c write_utils.c dinner.c monitor.c clean_utils.c

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
